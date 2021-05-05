/*
 * simon.c
 *
 *  Created on: 18 Aug 2019
 *      Author: unknown
 */
#include <avr/io.h>
#include "macros.h"
#include "simon.h"
#include <util/delay.h>
#include "led.h"
#include "segment.h"
#include "main.h"
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "storage.h"

uint16_t ctx;
uint16_t seed;
uint8_t lvl;
uint8_t maxLvl;
uint8_t lastKey;
volatile uint16_t time;

char message[64];
uint8_t MessageLength;

void initRNG(){
	TCCR1B|= (1<<CS10);
}
void sleepNow() {
  //PORTB = 0b00000000; // disable all pull-up resistors
  cli(); // disable all interrupts
  //WDTCR = 0; // turn off the Watchdog timer
  segmentDisplayOff();
  ledOff();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}
uint16_t getSeed(){
	cli();
	uint16_t seed=TCNT1;
	sei();
	TCCR1B &= ~(1<<CS10);
	TCNT1=0;
	return seed;
}
void smuteczek(){

}

ISR(TIMER2_OVF_vect){
		time++;
	}
void enableWatchdog(){
	//using timer 2;
	TCCR2 |= (1<<CS22) | (1<<CS21) | (1<<CS20); //prescaller/1024
	TIMSK |= (1<<TOIE2);
	//TCCR1B |= (1<<CS10)|(1<<CS12); //prescaller/1024
	//TCCR1B |= (1<<WGM12); //ctc mode;
	//TIMSK |=(1<<OCIE1A);
	//OCR1A=1000;
}
void resetCtx() {
  ctx = seed;
}

void gameOver(){
	segmentDisplayText("koniec gry",500);
	segmentDisplayOff();
	smuteczek();
	sleepNow();
}

uint8_t simple_random4() {
  // ctx = ctx * 1103515245 + 12345; // too big for ATtiny13
  ctx = 2053 * ctx + 13849;
  uint8_t temp = ctx ^ (ctx >> 8); // XOR two bytes
  temp ^= (temp >> 4); // XOR two nibbles
  return (temp ^ (temp >> 2)) & 0b00000011; // XOR two pairs of bits and return remainder after division by 4
}

void simon(){
	uint8_t finished=0;
	storageReadMessage(message,&MessageLength);
	//segmentDisplayText(message,500);
	ledBlinkAll();
	segmentDisplayText("super simon",250);
	segmentDisplayOff();
	segmentDisplayDotOn();


	while(  !(ledButton(0) || ledButton(1) || ledButton(2) || ledButton(3))  );
	if(ledButton(3)){
		//yellow pressed
		textEdit();
	}
	segmentDisplayWriteAsterisk();
	segmentDisplayDotOff();
	//segmentDisplayOff();
	seed=getSeed();
	_delay_ms(1000);
	ledLvlUp();
	enableWatchdog();
	_delay_ms(500);
	while (1) { //simon loop
	    resetCtx();
	    for (uint8_t cnt = 0; cnt <= lvl; cnt++) { // never ends if lvl == 255
	    	_delay_ms(320);
	      _delay_loop_2(500000 / (8 + lvl));
	      ledBeep(simple_random4());
	    }
	    time = 0;
	    lastKey = 5;
	    resetCtx();
	    for (uint8_t cnt = 0; cnt <= lvl; cnt++) {
	      uint8_t pressed = 0;
	      while (!pressed) {
	        for (uint8_t i = 0; i < 4; i++) {
	          if (ledButton(i)) {
	            if (1) {
	              ledBeep(i);
	              segmentDisplayWriteAsterisk();
	              pressed = 1;
	              uint8_t correct = simple_random4();
	              if (i != correct) {
	                for (uint8_t j = 0; j < 4; j++) {
	                  _delay_ms(200);
	                  ledBeepTime(correct,400);
	                }
	                _delay_ms(1000);
	                gameOver();
	              }
	              time = 0;
	              _delay_ms(200);
	              lastKey = i;

	              break;

	            }
	            time = 0;
	            _delay_ms(200);
	          }
	        }
	        if (time > 1800) {
	          sleepNow();
	        }
	      }
	    }
	    if (lvl < MessageLength){
			segmentDisplayLetter(message[lvl]);
			_delay_ms(1500);
	    }
	    else if (!finished){
	    	finished=1;
	    	for(int i=0;i<3;i++){
				ledLvlUp();
			}
	    	segmentDisplayText(message,720);
	    }
	    segmentDisplayWriteAsterisk();
	    if (lvl < 254) {
	    	lvl++;
	    	//if(lvl>maxLvl && lvl<MessageLength)maxLvl=lvl;
	    	ledLvlUp(); // animation for completed level
	    	_delay_ms(500);
	    }
	    else { // special animation for highest allowable (255th) level
	      ledLvlUp();
	      gameOver(); // then turn off
	    }
	  }
}
void textEdit(){
	_delay_ms(300);
	uint8_t previous_length=0;
	uint8_t length=0;
	//storageReadMessage(message, &previous_length);
	message[0]='a';
	segmentDisplayLetter(message[length]);
	uint8_t exit=0;
	while(!exit){
		if (!(PIN(BUTTON_BLUEPORT) & BUTTON_BLUE)){ //up
			message[length]+=1;
			if(message[length]>'z'+1)message[length]='a';
			segmentDisplayLetter(message[length]);
			_delay_ms(BUTTON_DEBOUNCE_TIME);
		}
		if (!(PIN(BUTTON_YELLOWPORT) & BUTTON_YELLOW)){ //down
			message[length]-=1;
			if(message[length]<'a')message[length]='z'+1;
			segmentDisplayLetter(message[length]);
			_delay_ms(BUTTON_DEBOUNCE_TIME);
		}
		if (!(PIN(BUTTON_REDPORT) & BUTTON_RED)){ //backspace
			if(length!=0)length-=1;
			segmentDisplayLetter(message[length]);
			_delay_ms(BUTTON_DEBOUNCE_TIME);
		}
		if (!(PIN(BUTTON_GREENPORT) & BUTTON_GREEN)){ //next
			if ( (length>0) && (message[length]=='z'+1 || length==MAX_TEXT_LENGTH-2))
			{
				exit=1;
				message[length+1]=0;
			}
			else{ //all ok
				if(message[0]!='z'+1){
					length+=1;
					if(length>previous_length){
						message[length]='z'+1;
						previous_length=length;
					}
					if (message[length]==0){
						message[length]='a';
					}
					segmentDisplayLetter(message[length]);
				}
			}
			_delay_ms(500);
		}
	}
	message[length]=0; //set last char to be nothing - end of the message
	storageWriteMessage(message, length);
	MessageLength=length;
	segmentDisplayText(message, 700); //show choosen text
}
