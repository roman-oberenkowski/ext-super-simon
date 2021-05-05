/*
 * storage.c
 *
 *  Created on: 17 Aug 2019
 *      Author: unknown
 */
#include <avr/eeprom.h>
#include "led.h"
#include <util/delay.h>
void storageWriteMessage(char * message, uint8_t length){
	for (uint8_t i=0;i<length;i++){
		ledSet(2,1);
		eeprom_write_byte((uint8_t *)(9+i), message[i]);
		_delay_ms(50);
		ledSet(2,0);
	}
	eeprom_write_byte((uint8_t *) 8,length);
}
void storageReadMessage(char * message, uint8_t * length){
	*length=eeprom_read_byte((uint8_t *) 8);
	if(*length>64)*length=5;
	for (uint8_t i=0;i<*length;i++){
		 message[i]=eeprom_read_byte((uint8_t *)9+i);
	}
	message[*length]=0;
}
uint16_t storageReadSeed(){
	return eeprom_read_word((uint16_t *) 1);
}
void storageWriteSeed(uint16_t seed){
	eeprom_write_word( (uint16_t *) 1, seed );
}
uint8_t storageOk(){
	if(eeprom_read_byte((uint8_t *) 0)==255){
		return 0;
	}
	return 1;
}
void flagOk(){
	eeprom_write_byte((uint8_t *) 0, 1);
}

