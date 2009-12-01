// RoboSimoClient.h - written by Ted Burke - last modified 30-11-2009

// Define LATA
union lata_union
{
	unsigned char byte;
	struct
	{
		unsigned int LATA0 : 1;
		unsigned int LATA1 : 1;
		unsigned int LATA2 : 1;
		unsigned int LATA3 : 1;
		unsigned int LATA4 : 1;
		unsigned int LATA5 : 1;
		unsigned int LATA6 : 1;
		unsigned int LATA7 : 1;
	} bits;
};
extern union lata_union lata;
#define LATAbits lata.bits
#define LATA lata.byte

// Define LATB
union latb_union
{
	unsigned char byte;
	struct
	{
		unsigned int LATB0 : 1;
		unsigned int LATB1 : 1;
		unsigned int LATB2 : 1;
		unsigned int LATB3 : 1;
		unsigned int LATB4 : 1;
		unsigned int LATB5 : 1;
		unsigned int LATB6 : 1;
		unsigned int LATB7 : 1;
	} bits;
};
extern union latb_union latb;
#define LATBbits latb.bits
#define LATB latb.byte

// Define LATC
union latc_union
{
	unsigned char byte;
	struct
	{
		unsigned int LATC0 : 1;
		unsigned int LATC1 : 1;
		unsigned int LATC2 : 1;
		unsigned int LATC3 : 1;
		unsigned int LATC4 : 1;
		unsigned int LATC5 : 1;
		unsigned int LATC6 : 1;
		unsigned int LATC7 : 1;
	} bits;
};
extern union latc_union latc;
#define LATCbits latc.bits
#define LATC latc.byte

// Define LATD
union latd_union
{
	unsigned char byte;
	struct
	{
		unsigned int LATD0 : 1;
		unsigned int LATD1 : 1;
		unsigned int LATD2 : 1;
		unsigned int LATD3 : 1;
		unsigned int LATD4 : 1;
		unsigned int LATD5 : 1;
		unsigned int LATD6 : 1;
		unsigned int LATD7 : 1;
	} bits;
};
extern union latd_union latd;
#define LATDbits latd.bits
#define LATD latd.byte

// Define PORTA
union porta_union
{
	unsigned char byte;
	struct
	{
		unsigned int RA0 : 1;
		unsigned int RA1 : 1;
		unsigned int RA2 : 1;
		unsigned int RA3 : 1;
		unsigned int RA4 : 1;
		unsigned int RA5 : 1;
		unsigned int RA6 : 1;
		unsigned int RA7 : 1;
	} bits;
};
extern union porta_union porta;
#define PORTAbits porta.bits
#define PORTA porta.byte

// Define PORTB
union portb_union
{
	unsigned char byte;
	struct
	{
		unsigned int RB0 : 1;
		unsigned int RB1 : 1;
		unsigned int RB2 : 1;
		unsigned int RB3 : 1;
		unsigned int RB4 : 1;
		unsigned int RB5 : 1;
		unsigned int RB6 : 1;
		unsigned int RB7 : 1;
	} bits;
};
extern union portb_union portb;
#define PORTBbits portb.bits
#define PORTB portb.byte

// Define PORTC
union portc_union
{
	unsigned char byte;
	struct
	{
		unsigned int RC0 : 1;
		unsigned int RC1 : 1;
		unsigned int RC2 : 1;
		unsigned int RC3 : 1;
		unsigned int RC4 : 1;
		unsigned int RC5 : 1;
		unsigned int RC6 : 1;
		unsigned int RC7 : 1;
	} bits;
};
extern union portc_union portc;
#define PORTCbits portc.bits
#define PORTC portc.byte

// Define PORTD
union portd_union
{
	unsigned char byte;
	struct
	{
		unsigned int RD0 : 1;
		unsigned int RD1 : 1;
		unsigned int RD2 : 1;
		unsigned int RD3 : 1;
		unsigned int RD4 : 1;
		unsigned int RD5 : 1;
		unsigned int RD6 : 1;
		unsigned int RD7 : 1;
	} bits;
};
extern union portd_union portd;
#define PORTDbits portd.bits
#define PORTD portd.byte

// Analog inputs
extern unsigned char analog_inputs[8];
extern unsigned int read_analog_channel(unsigned int channel);

// Other registers
extern unsigned char CCPR1L; // PWM channel 1 duty cycle register
extern unsigned char CCPR2L; // PWM channel 2 duty cycle register

// Robot control functions
extern void set_motor_directions(int left, int right);
extern void set_motor_speeds(int left, int right);

// Millisecond delay function
extern void delay_ms(unsigned long milliseconds);

// Server connection functions
extern int connect_to_server(int a, int b, int c, int d, int port);
extern void close_connection();
