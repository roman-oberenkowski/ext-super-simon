/*
 * buzzer.h
 *
 *  Created on: 12 Aug 2019
 *      Author: unknown
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "macros.h"
#include <avr/io.h>
#include <util/delay.h>
//Buzzer PINs
#define BUZZERPORT B
#define BUZZER (1<<0)

//volatile uint8_t timerTime;

void buzzerInit();
void buzzerPlayBackground(uint8_t i);
void buzzerPlay(uint8_t i, uint16_t time);
void buzzerOff();
void buzzerTest();

#endif /* BUZZER_H_ */
