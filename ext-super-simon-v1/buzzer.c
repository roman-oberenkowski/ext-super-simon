/*
 * buzzer.c
 *
 *  Created on: 12 Aug 2019
 *      Author: unknown
 *      USING TIMER0 for buzzer
 */
#include "buzzer.h"
#include <avr/interrupt.h>
#include <util/delay.h>

const uint8_t tones[] = {140, 160, 180, 200};
volatile uint8_t timerTime=0;

void buzzerInit(){
	DDR(BUZZERPORT)|=BUZZER; //buzzer pin output
	//PORT(BUZZERPORT)|=BUZZER;
	TIMSK|=(1<<TOIE0);		//enable timer0 interrupt
	sei();					//globally enable iterruts
}
void buzzerOff(){
	TCCR0 &= ~((1<<CS01)|(1<<CS00)|(1<<CS02)); //stop timer (no clock source)
	//PORT(BUZZERPORT) &= ~BUZZER;	//buzzerport low - not needed when using capacitor in series
}
void buzzerTest(){
	for( int i=0;i<250;i++){
		buzzerPlayBackground(i);
		_delay_ms(10);
	}
	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			buzzerPlayBackground(tones[j]);
			_delay_ms(140);
		}
		//buzzerPlayBackground();
		//_delay_ms(140);
		buzzerOff();
		_delay_ms(1000);
	}
	buzzerOff();
}
void buzzerPlayBackground(uint8_t i){
	TCCR0|= (1<<CS01)|(1<<CS00); //prescaller /64
	timerTime=i;
}
void buzzerPlay(uint8_t i, uint16_t time){
	TCCR0|= (1<<CS01)|(1<<CS00); //prescaller /64
	timerTime=i;
	_delay_loop_2(time);
	buzzerOff();
}

ISR(TIMER0_OVF_vect){
	TCNT0=timerTime;
	PORT(BUZZERPORT) ^= BUZZER;
}

