/*p
 * main.c
 *
 *  Created on: 11 Aug 2019
 *      Author: unknown
 *  -----------------------------
 *  |   Connector on the back	|
 *  | 			oooooxo			|
 *	|mosi miso sck rst gnd x nc |
 *  -----------------------------
 *	TIMER0 for buzzer
 *
 *
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "main.h"
#include "macros.h"
#include "led.h"
#include "segment.h"
#include "buzzer.h"
#include "storage.h"
#include "simon.h"
char default_text[]="test";
char text1[]="abc";
char text2[]="text2";


int main(void)
{
	if (!(PIN(BUTTON_REDPORT) & BUTTON_RED)){ //red sleep
		ledBlink(3,3); //blink yellow 3 times
	   	sleepNow();
	}
	if (!(PIN(BUTTON_YELLOWPORT) & BUTTON_YELLOW)){ //yellow program text1 to eeprom
	    	storageWriteMessage(text1,3);
	}
	if (!(PIN(BUTTON_BLUEPORT) & BUTTON_BLUE)){ //blue program text2 to eeprom
		    storageWriteMessage(text2,5);
	}
	segmentDisplayInit();
	ledInit();
	buzzerInit();
	initRNG();
	//empty EEPROM -> program default text
	if(!storageOk()){
		ledBlink(0,5);
		storageWriteMessage(default_text,4);
		flagOk();
		_delay_ms(500);
	}
	simon();
}
