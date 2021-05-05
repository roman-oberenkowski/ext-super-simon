/*
 * led.h
 *
 *  Created on: 17 Aug 2019
 *      Author: unknown
 */
#include <avr/io.h>
#ifndef LED_H_
#define LED_H_

#define BUTTON_REDPORT D
#define BUTTON_RED (1<<0)
#define BUTTON_GREENPORT D
#define BUTTON_GREEN (1<<7)
#define BUTTON_BLUEPORT B
#define BUTTON_BLUE (1<<1)
#define BUTTON_YELLOWPORT B
#define BUTTON_YELLOW (1<<2)

void ledInit();
void ledAnimationStart();
void ledBlinkAll();
void ledSet(uint8_t led, uint8_t state);
void ledOff();
void ledBlink(uint8_t,uint8_t);
uint8_t ledButton(uint8_t button);
void ledLvlUp();
void ledBeep(uint8_t i);
void ledBeepTime(uint8_t i,uint16_t time);
#endif /* LED_H_ */
