//
// main.c - RoboSimoClient example program - written by Ted Burke - last updated 7-12-2009
//

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
		set_motor_speeds(100, 100); // max speed is 255
		
		// Go forwards to white line, pause, then reverse forever		
		while(read_analog_channel(0) < 120 && read_analog_channel(1) < 120)
		{
			set_motor_directions(1, 1); // motors forwards
		}
		set_motor_directions(0, 0); // stop motors

		// pause
		delay_ms(2000);
		
		// reverse full speed
		set_motor_speeds(255, 255); // max speed is 255
		set_motor_directions(-1, -1); // reverse
		
		// program gets trapped in this loop forever
		while(1)
		{
		}
	}
	
	return 0;
}
