/*
 * led.c
 *
 *  Created on: 17 Aug 2019
 *      Author: unknown
 *      good sequence: blue yellow red red green blue yellow
 */
#include "led.h"
#include "macros.h"
#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"
void ledInit(){
	DDR(BUTTON_REDPORT) &= ~BUTTON_RED;
	DDR(BUTTON_GREENPORT) &= ~BUTTON_GREEN;
	DDR(BUTTON_BLUEPORT) &= ~BUTTON_BLUE;
	DDR(BUTTON_YELLOWPORT) &= ~BUTTON_YELLOW;
	PORT(BUTTON_REDPORT) &= ~BUTTON_RED;
	PORT(BUTTON_GREENPORT) &= ~BUTTON_GREEN;
	PORT(BUTTON_BLUEPORT) &= ~BUTTON_BLUE;
	PORT(BUTTON_YELLOWPORT) &= ~BUTTON_YELLOW;
}
void ledSet(uint8_t led,uint8_t state){
	switch (led){
	case 0:
		if (state){
			DDR(BUTTON_REDPORT) |= BUTTON_RED;
		}
		else{
			DDR(BUTTON_REDPORT) &= ~BUTTON_RED;
		}
		break;
	case 1:
			if (state){
				DDR(BUTTON_GREENPORT) |= BUTTON_GREEN;
			}
			else{
				DDR(BUTTON_GREENPORT) &= ~BUTTON_GREEN;
			}
			break;
	case 2:
		if (state) DDR(BUTTON_BLUEPORT) |= BUTTON_BLUE;
		else DDR(BUTTON_BLUEPORT) &= ~BUTTON_BLUE;
		break;
	case 3:
		if (state)DDR(BUTTON_YELLOWPORT) |= BUTTON_YELLOW;
		else DDR(BUTTON_YELLOWPORT) &= ~BUTTON_YELLOW;
	}
}
void ledOff(){
	ledSet(0,0);
	ledSet(1,0);
	ledSet(2,0);
	ledSet(3,0);
}
void ledBlink(uint8_t ledNumber,uint8_t count){
	for(uint8_t i=0;i<count;i++){
		ledSet(ledNumber,1);
		_delay_ms(300);
		ledSet(ledNumber,0);
		_delay_ms(700);
	}
}
#define LED_TIME 150
void ledBlinkAll(){
	DDR(BUTTON_REDPORT) |= BUTTON_RED;
	buzzerPlayBackground(140);
	_delay_ms(LED_TIME);
	DDR(BUTTON_GREENPORT) |= BUTTON_GREEN;
	buzzerPlayBackground(160);
	_delay_ms(LED_TIME);
	DDR(BUTTON_BLUEPORT) |= BUTTON_BLUE;
	buzzerPlayBackground(180);
	_delay_ms(LED_TIME);
	DDR(BUTTON_YELLOWPORT) |= BUTTON_YELLOW;
	buzzerPlayBackground(200);
	_delay_ms(LED_TIME);
	buzzerOff();
	DDR(BUTTON_REDPORT) &= ~BUTTON_RED;
	_delay_ms(LED_TIME);
	buzzerPlayBackground(130);
	DDR(BUTTON_GREENPORT) &= ~BUTTON_GREEN;
	_delay_ms(LED_TIME);
	DDR(BUTTON_BLUEPORT) &= ~BUTTON_BLUE;
	_delay_ms(LED_TIME);
	DDR(BUTTON_YELLOWPORT) &= ~BUTTON_YELLOW;
	buzzerPlayBackground(190);
	_delay_ms(LED_TIME);
	buzzerOff();
}
const uint8_t tones2[4] = {	  210, 179, 143, 139};
const uint8_t tones3[4] = {140, 160, 180, 200};
void ledLvlUp(){
	for (int i=0;i<4;i++){
		ledSet(i,1);
		buzzerPlayBackground(tones3[i]);
		_delay_ms(120);
		ledSet(i,0);
		buzzerOff();
		_delay_ms(15);
	}
	buzzerOff();
}
void ledBeep(uint8_t i){
	ledSet(i,1);
	buzzerPlayBackground(tones3[i]);
	_delay_ms(250);
	ledSet(i,0);
	buzzerOff();
	_delay_ms(15);
}
void ledBeepTime(uint8_t i,uint16_t time){
	ledSet(i,1);
	buzzerPlayBackground(tones3[i]);
	for(uint16_t i=0;i<time/25;i++){
		_delay_ms(25);
	}
	ledSet(i,0);
	buzzerOff();
	_delay_ms(50);
}
uint8_t ledButton(uint8_t button){
	switch (button){
	case 0:
		if (!(PIN(BUTTON_REDPORT) & BUTTON_RED))return 1;
		else return 0;
	case 1:
		if (!(PIN(BUTTON_GREENPORT) & BUTTON_GREEN))return 1;
		else return 0;
	case 2:
		if (!(PIN(BUTTON_BLUEPORT) & BUTTON_BLUE))return 1;
		else return 0;
	case 3:
		if (!(PIN(BUTTON_YELLOWPORT) & BUTTON_YELLOW))return 1;
		else return 0;
	}
	return 0;
}
