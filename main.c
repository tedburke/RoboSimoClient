// main.c - RoboSimoClient example program - written by Ted Burke - last updated 1-12-2009

#include <stdio.h>

#include "RoboSimoClient.h"

int main()
{
	// Welcome message
	printf("Welcome to RoboSimoClient\n\n");

	// Ask user for server IP address, then connect to it
	int a, b, c, d, port;
	printf("Please enter server IP address: ");
	scanf("%d.%d.%d.%d", &a, &b, &c, &d);
	printf("Please enter port number: ");
	scanf("%d", &port);	
	connect_to_server(a, b, c, d, port);

	// Main loop
	while(1)
	{
		// Set motor speeds
		set_motor_speeds(50, 50); // max speed is 255
		
		// Move around
		set_motor_directions(1, 1); // forwards
		delay_ms(1000);
		set_motor_directions(-1, -1); // backwards
		delay_ms(1000);
		set_motor_directions(1, -1); // turn right
		delay_ms(1000);
		set_motor_directions(-1, 1); // turn left
		delay_ms(1000);
	}
	
	return 0;
}
