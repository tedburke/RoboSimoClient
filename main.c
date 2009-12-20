//
// main.c - RoboSimoClient example program - written by Ted Burke - last updated 20-12-2009
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
	//connect_to_server(192, 168, 1, 2, 4009);

	// Main loop
	set_motor_speeds(255, 255); // max speed is 255
	while(1)
	{		
		// Go forwards to white line		
		set_motor_directions(1, 1); // motors forwards
		while(read_analog_channel(0) < 120 && read_analog_channel(1) < 120);

		// pause
		set_motor_directions(0, 0); // stop motors
		delay_ms(500);
		
		// Go backwards to white line
		set_motor_directions(-1, -1); // motors forwards
		while(read_analog_channel(2) < 120 && read_analog_channel(3) < 120);

		// pause
		set_motor_directions(0, 0); // stop motors
		delay_ms(500);
	}
	
	return 0;
}
