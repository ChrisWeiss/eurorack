#ifdef EXTERNAL_IDE

#include <Arduino.h>
#include <EEPROM.h>

int main(void) {
  init();
  setup();
  while(true) {
    loop();
  }
}

#endif

#include <portManipulations.h>
#include <lfoExtended.h>

#include "trinityRackCV_HW.h"


extern trinityRackCV_HW hardware;
lfoExtended LFO;


uint32_t _time;
uint16_t testTime=0;

void dummy() {
}


void setup() {
	hardware.init(&dummy);
	LFO.init();
	LFO.setBastlCyclesPerPeriod(800);
	LFO.setWaveform(TRIANGLE);
	_time=hardware.getElapsedBastlCyclesLong();
}



void loop() {

	if(hardware.getElapsedBastlCyclesLong()!=_time){
		_time=hardware.getElapsedBastlCyclesLong();
		testTime++;
		uint8_t out=LFO.getValue(testTime);
		hardware.setDAC(0,out);
		hardware.isr_updateDAC();
	}

}

