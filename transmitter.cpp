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
// Raspberry pi
#if 1
	Nrf24l Mirf = Nrf24l("/dev/spidev0.1", 4000000);
	Mirf.cePin=25; // GPIO25
	Mirf.csnPin=8; // GPIO8
#endif

//OrangePi PC
#if 0
	Nrf24l Mirf = Nrf24l("/dev/spidev0.0", 4000000);
	Mirf.cePin=2;	// GPIO2
	Mirf.csnPin=67; // GPIO67
#endif

	Mirf.init();
	Mirf.setRADDR((uint8_t *)"ABCDE");
	Mirf.payload = sizeof(mydata.value);
	Mirf.channel = 90;
	Mirf.config();
	printf("setup done.\n\r");

	while(1) {
		Mirf.setTADDR((uint8_t *)"FGHIJ");		//Set Destination address
		mydata.now_time = __millis();
		Mirf.send(mydata.value);				//Send instructions
		printf("Wait for sending.....\n");
		//Test you send successfully
		if (Mirf.isSend()) {
			printf("Send success:%lu\n", mydata.now_time);
		} else {
			printf("Send fail:\n");
		}
		delay(1000);
	}
}

