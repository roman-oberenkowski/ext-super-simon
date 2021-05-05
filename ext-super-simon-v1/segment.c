/*
 * 14segment_pomocnicze.c
 *
 *  Created on: 11 Aug 2019
 *      Author: unknown
 */

#include <avr/io.h>
#include "segment.h"
#include "macros.h"
#include <util/delay.h>
void segmentDisplayInit(){
	DDR(SEGMENT_APORT) |= SEGMENT_A;
	DDR(SEGMENT_BPORT) |= SEGMENT_B;
	DDR(SEGMENT_CPORT) |= SEGMENT_C;
	DDR(SEGMENT_DPORT) |= SEGMENT_D;
	DDR(SEGMENT_EPORT) |= SEGMENT_E;
	DDR(SEGMENT_FPORT) |= SEGMENT_F;
	DDR(SEGMENT_GPORT) |= SEGMENT_G;
	DDR(SEGMENT_HPORT) |= SEGMENT_H;
	DDR(SEGMENT_KPORT) |= SEGMENT_K;
	DDR(SEGMENT_MPORT) |= SEGMENT_M;
	DDR(SEGMENT_NPORT) |= SEGMENT_N;
	DDR(SEGMENT_PPORT) |= SEGMENT_P;
	DDR(SEGMENT_RPORT) |= SEGMENT_R;
	DDR(SEGMENT_SPORT) |= SEGMENT_S;
	DDR(SEGMENT_TPORT) |= SEGMENT_T;
	DDR(SEGMENT_UPORT) |= SEGMENT_U;
	DDR(SEGMENT_DPPORT) |= SEGMENT_DP;
	segmentDisplayOff();
}
void segmentDisplayWrite(uint16_t data){
	data=~data;
	if( data&(1<<0) ) { PORT(SEGMENT_APORT) |= SEGMENT_A; }
	 else { PORT(SEGMENT_APORT) &= ~SEGMENT_A; }
	if( data&(1<<1) ) { PORT(SEGMENT_BPORT) |= SEGMENT_B; }
	 else { PORT(SEGMENT_BPORT) &= ~SEGMENT_B; }
	if( data&(1<<2) ) { PORT(SEGMENT_CPORT) |= SEGMENT_C; }
	 else { PORT(SEGMENT_CPORT) &= ~SEGMENT_C; }
	if( data&(1<<3) ) { PORT(SEGMENT_DPORT) |= SEGMENT_D; }
	 else { PORT(SEGMENT_DPORT) &= ~SEGMENT_D; }
	if( data&(1<<4) ) { PORT(SEGMENT_EPORT) |= SEGMENT_E; }
	 else { PORT(SEGMENT_EPORT) &= ~SEGMENT_E; }
	if( data&(1<<5) ) { PORT(SEGMENT_FPORT) |= SEGMENT_F; }
	 else { PORT(SEGMENT_FPORT) &= ~SEGMENT_F; }
	if( data&(1<<6) ) { PORT(SEGMENT_GPORT) |= SEGMENT_G; }
	 else { PORT(SEGMENT_GPORT) &= ~SEGMENT_G; }
	if( data&(1<<7) ) { PORT(SEGMENT_HPORT) |= SEGMENT_H; }
	 else { PORT(SEGMENT_HPORT) &= ~SEGMENT_H; }
	if( data&(1<<8) ) { PORT(SEGMENT_KPORT) |= SEGMENT_K; }
	 else { PORT(SEGMENT_KPORT) &= ~SEGMENT_K; }
	if( data&(1<<9) ) { PORT(SEGMENT_MPORT) |= SEGMENT_M; }
	 else { PORT(SEGMENT_MPORT) &= ~SEGMENT_M; }
	if( data&(1<<10) ) { PORT(SEGMENT_NPORT) |= SEGMENT_N; }
	 else { PORT(SEGMENT_NPORT) &= ~SEGMENT_N; }
	if( data&(1<<11) ) { PORT(SEGMENT_PPORT) |= SEGMENT_P; }
	 else { PORT(SEGMENT_PPORT) &= ~SEGMENT_P; }
	if( data&(1<<12) ) { PORT(SEGMENT_RPORT) |= SEGMENT_R; }
	 else { PORT(SEGMENT_RPORT) &= ~SEGMENT_R; }
	if( data&(1<<13) ) { PORT(SEGMENT_SPORT) |= SEGMENT_S; }
	 else { PORT(SEGMENT_SPORT) &= ~SEGMENT_S; }
	if( data&(1<<14) ) { PORT(SEGMENT_TPORT) |= SEGMENT_T; }
	 else { PORT(SEGMENT_TPORT) &= ~SEGMENT_T; }
	if( data&(1<<15) ) { PORT(SEGMENT_UPORT) |= SEGMENT_U; }
	 else { PORT(SEGMENT_UPORT) &= ~SEGMENT_U; }
}
static uint16_t patterns[]={
		0b1000100011001111,
		0b0010101000111111,
		0b0000000011110011,
		0b0010001000111111, //d
		0b1000100011110011,
		0b1000100011000011,
		0b0000100011111011, //g
		0b1000100011001100,
		0b0010001000110011, //i
		0b0000000001111100,
		0b1001010011000000, //k
		0b0000000011110000, //l
		0b0000010111001100, //m
		0b0001000111001100, //n
		0b0000000011111111,
		0b1000100011000111, //p
		0b0001000011111111, //q
		0b1001100011000111, //r
		0b1000100010111011, //s
		0b0010001000000011, //t
		0b0000000011111100, //u
		0b0001000100001100, //v
		0b0101000011001100, //w
		0b0101010100000000, //x
		0b0010010100000000, //y
		0b0100010000110011, //z
};
static uint16_t digits[]={
		0b0000000011111111,
		0b0000000000001100,
		0b1000100001110111,
		0b1000100000111111,
		0b1000100010001100,
		0b1000100010111011,
		0b1000100011111011,
		0b0100010000000011,
		0b1000101011111111,
		0b1000100010111111,
};

uint16_t letter2Data(char literka){
	if(literka==' ')return 0;
	literka |= 0x20; //to lower
	return patterns[literka-'a'];
}
uint16_t letter2DataEdit(char literka){
	if(literka==' ')return 0b0000000000110000; //_ probably;
	literka |= 0x20; //to lower
	return patterns[literka-'a'];
}
void segmentDisplayDigit(uint8_t cyfra){
	if(cyfra<=9){
		segmentDisplayWrite(digits[cyfra]);
	}
}
void segmentDisplayNumber(uint16_t number){
	uint16_t digit;
	uint16_t pow=1;
	if (number==0){
		segmentDisplayDigit(0);
	}
	else{
		while(pow<=number/10){
			pow*=10;
		}
		while(pow>0){
			digit=number/pow;
			number=number%pow;
			pow/=10;
			segmentDisplayDigit(digit);
			_delay_ms(750);
			segmentDisplayOff();
			_delay_ms(100);
		}
	}
}
void segmentDisplayLetter(char literka){
	if(literka=='.'||literka=='z'+1){
		segmentDisplayWrite(0b1111111111111111);
		segmentDisplayDotOn();
	}
	else {
		segmentDisplayDotOff();
		segmentDisplayWrite(letter2Data(literka));
	}
}
void segmentDisplayOff(){
	segmentDisplayWrite(0);
	segmentDisplayDotOff();
}
void segmentDisplayText(char * tab, uint16_t letterTime){
	int i=0;
	while(tab[i]!=0){
		segmentDisplayLetter(tab[i]);
		for(uint16_t i=0;i<letterTime/100;i++){
			_delay_ms(100);
		}
		i++;
	}
}
void segmentDisplayDotOn(){
	PORT(SEGMENT_DPPORT) &= ~SEGMENT_DP;
}
void segmentDisplayDotOff(){
	PORT(SEGMENT_DPPORT) |= SEGMENT_DP;
}
void segmentDisplayWriteAsterisk(){
	segmentDisplayWrite(~0b0000000011111111);
}
