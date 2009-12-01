RoboSimoClient.exe: main.c RoboSimoClient.c RoboSimoClient.h
	gcc -o RoboSimoClient.exe main.c RoboSimoClient.c -lwsock32 -lWs2_32
