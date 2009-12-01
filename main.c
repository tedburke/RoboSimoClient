#include <stdio.h>

#include "RoboSimoClient.h"

int main()
{
	printf("Welcome to RoboSimoClient\n\n");
	
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
	
	close_connection();
	
	printf("Exiting RoboSumoClient\nGoodbye");
	
	return 0;
}
