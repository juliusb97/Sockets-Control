#include "rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){

	int socket = -1;
	int status = -1;

	if(argc == 3){
		printf("Send Signal %s to Socket No. %d\n", (atoi(argv[2])?"ON":"OFF"), atoi(argv[1]));
		socket = atoi(argv[1]);
		status = atoi(argv[2]);
	} else if(argc == 2){
		if(strcmp(argv[1], "-on")==0){
			printf("Turning all Sockets on.\n");
		} else if(strcmp(argv[1], "-off")==0){
			printf("Turning all Sockets off.\n");
		}
	} else {
		printf("Usage: SocketControl <socketNo> <0|1> | SocketControl <-on|-off>\n");
		exit(-1);
	}

	if(wiringPiSetup() == -1){
		printf("WiringPi error\n");
		return -1;
	}

	RCSwitch mySwitch = RCSwitch();

	mySwitch.enableTransmit(0);

	if(strcmp(argv[1], "-on")==0){
		mySwitch.send(83029, 24);
		mySwitch.send(86101, 24);
		mySwitch.send(70741, 24);
		mySwitch.send(21589, 24);
		exit(0);
	} else if(strcmp(argv[1], "-off")==0){
		mySwitch.send(83028, 24);
		mySwitch.send(86100, 24);
		mySwitch.send(70740, 24);
		mySwitch.send(21588, 24);
		exit(0);
	}

	int i;
	for(i = 0; i < 3; i++){
	switch(socket){
		case 0:
			if(status)
				mySwitch.send(83029, 24);
			else
				mySwitch.send(83028, 24);
			printf("Sent Signal to Socket No. 0\n");
			break;
		case 1:
			if(status)
				mySwitch.send(86101, 24);
			else
				mySwitch.send(86100, 24);
			printf("Sent Signal to Socket No. 1\n");
			break;
		case 2:
			if(status)
				mySwitch.send(70741, 24);
			else
				mySwitch.send(70740, 24);
			printf("Sent Signal to Socket No. 2\n");
			break;
		case 3:
			if(status)
				mySwitch.send(21589, 24);
			else
				mySwitch.send(21588, 24);
			printf("Sent Signal to Socket No. 3\n");
			break;
	}
	delay(100);
	}

	return 0;
}
