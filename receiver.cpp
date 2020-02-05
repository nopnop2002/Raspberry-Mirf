#include <cstdlib>
#include <iostream>
#include "Mirf.h"

union MYDATA_t {
  uint8_t value[4];
  unsigned long now_time;
};


MYDATA_t mydata;

void delay(int ms) {
  usleep(ms*1000); //convert to microseconds
  return;
}


int main(int argc, char** argv)
{
	Nrf24l Mirf = Nrf24l("/dev/spidev0.1", 4000000);
	Mirf.cePin=25; // GPIO25
	Mirf.csnPin=8; // GPIO8
	Mirf.init();
	Mirf.setRADDR((uint8_t *)"FGHIJ");
	Mirf.payload = sizeof(mydata.value);
	Mirf.channel = 90;              //Set the used channel
	Mirf.config();
	printf("Listening...\n"); //Start listening to received data

	while(1) {
		if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
			Mirf.getData(mydata.value);
			printf("Got now_time:%lu\n", mydata.now_time);
		}
	}
}

