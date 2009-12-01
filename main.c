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
		// Move around
		set_motor_directions(1, 1);
		delay_ms(1000);
		set_motor_directions(-1, -1);
		delay_ms(1000);
		set_motor_directions(1, -1);
		delay_ms(1000);
		set_motor_directions(-1, 1);
		delay_ms(1000);

		/*printf("DIs %u %u %u %u ",
			PORTA, PORTB, PORTC, PORTD);
		printf("AIs %u %u %u %u %u %u %u %u\n",
			analog_inputs[0],
			analog_inputs[1],
			analog_inputs[2],
			analog_inputs[3],
			analog_inputs[4],
			analog_inputs[5],
			analog_inputs[6],
			analog_inputs[7]);
		delay_ms(500);*/
	}
	
	close_connection();
	
	printf("Exiting RoboSumoClient\nGoodbye");
	
	return 0;
}
