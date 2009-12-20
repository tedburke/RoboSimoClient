// RoboSimoClient.c - written by Ted Burke - last modified 30-11-2009

// Define windows version for sockets functions, e.g. getaddrinfo
#define WINVER 0x0501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "RoboSimoClient.h"

union lata_union lata;
union latb_union latb;
union latc_union latc;
union latd_union latd;
union porta_union porta;
union portb_union portb;
union portc_union portc;
union portd_union portd;
unsigned char analog_inputs[8];

unsigned char CCPR1L = 255; // PWM channel 1 duty cycle register
unsigned char CCPR2L = 255; // PWM channel 2 duty cycle register

// Analog input function
unsigned int read_analog_channel(unsigned int channel)
{
	delay_ms(1);
	return analog_inputs[channel];
}

// Robot control functions
void set_motor_directions(int left, int right)
{
	// Left motor forwards, backwards or stop
	if (left > 0)
	{
		LATDbits.LATD0 = 0;
		LATDbits.LATD1 = 1;
	}
	else if (left < 0)
	{
		LATDbits.LATD0 = 1;
		LATDbits.LATD1 = 0;
	}
	else
	{
		LATDbits.LATD0 = 0;
		LATDbits.LATD1 = 0;
	}

	// Right motor forwards, backwards or stop
	if (right > 0)
	{
		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 1;
	}
	else if (right < 0)
	{
		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 0;
	}
	else
	{
		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;
	}
	delay_ms(1);
}

void set_motor_speeds(int left, int right)
{
	if (left > 255) left = 255;
	if (left < 0) left = 0;
	if (right > 255) right = 255;
	if (right < 0) right = 0;
	CCPR1L = left;
	CCPR2L = right;
	delay_ms(1);
}

// Delay function
void delay_ms(unsigned long milliseconds)
{
	Sleep(milliseconds);
}

// Server connection functions
int stay_connected = 0;
LPDWORD lpThreadId = NULL;
HANDLE hNetworkThread = NULL;

// Server address strings
char server_address[16];
char server_port[10];

// Network thread function
DWORD WINAPI network_thread_function(LPVOID lpParam)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	unsigned char sendbuf[6];
	unsigned char recvbuf[12];
	int iResult;
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(server_address, server_port, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for(ptr=result ; ptr != NULL ; ptr=ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		exit(1);
		return 1;
	}

	while(stay_connected)
	{
		// Send robot state
		sendbuf[0] = LATA;
		sendbuf[1] = LATB;
		sendbuf[2] = LATC;
		sendbuf[3] = LATD;
		sendbuf[4] = CCPR1L;
		sendbuf[5] = CCPR2L;
		iResult = send(ConnectSocket, sendbuf, 6, 0);
		if (iResult == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		
		// Receive sensor readings
		iResult = recv(ConnectSocket, recvbuf, 12, 0);
		if (iResult <= 0)
		{
			printf("Connection closed\n");
			exit(1);
			break;
		}
		PORTA = recvbuf[0];
		PORTB = recvbuf[1];
		PORTC = recvbuf[2];
		PORTD = recvbuf[3];
		analog_inputs[0] = recvbuf[4];
		analog_inputs[1] = recvbuf[5];
		analog_inputs[2] = recvbuf[6];
		analog_inputs[3] = recvbuf[7];
		analog_inputs[4] = recvbuf[8];
		analog_inputs[5] = recvbuf[9];
		analog_inputs[6] = recvbuf[10];
		analog_inputs[7] = recvbuf[11];
		
		// Short pause
		Sleep(1);
	}
	
	// Exit thread
	closesocket(ConnectSocket);
	WSACleanup();
}

int connect_to_server(int a, int b, int c, int d, int port)
{
	// Specify global server properties before launching network thread
	sprintf(server_address, "%d.%d.%d.%d", a, b, c, d);
	sprintf(server_port, "%d", port);
	stay_connected = 1; // Will be reset to 0 when thread should exit
	hNetworkThread = CreateThread(NULL, 0, network_thread_function, NULL, 0, lpThreadId);
}

void close_connection()
{
	stay_connected = 0;
	WaitForSingleObject(hNetworkThread, 1000); // Wait up to 1000ms for network thread to exit
}
