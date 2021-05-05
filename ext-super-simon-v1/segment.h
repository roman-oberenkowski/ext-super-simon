/*
 * 16segment.h
 *
 *  Created on: 12 Aug 2019
 *      Author: unknown
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

//16SEGMENT pinout
#define SEGMENT_APORT C
#define SEGMENT_A (1<<4)
#define SEGMENT_BPORT C
#define SEGMENT_B (1<<5)
#define SEGMENT_CPORT D
#define SEGMENT_C (1<<2)
#define SEGMENT_DPORT B
#define SEGMENT_D (1<<6)
#define SEGMENT_EPORT B
#define SEGMENT_E (1<<3)
#define SEGMENT_FPORT B
#define SEGMENT_F (1<<4)
#define SEGMENT_GPORT C
#define SEGMENT_G (1<<0)
#define SEGMENT_HPORT C
#define SEGMENT_H (1<<1)
#define SEGMENT_KPORT C
#define SEGMENT_K (1<<2)
#define SEGMENT_MPORT C
#define SEGMENT_M (1<<3)
#define SEGMENT_NPORT D
#define SEGMENT_N (1<<1)
#define SEGMENT_PPORT D
#define SEGMENT_P (1<<3)
#define SEGMENT_RPORT B
#define SEGMENT_R (1<<7)
#define SEGMENT_SPORT D
#define SEGMENT_S (1<<5)
#define SEGMENT_TPORT B
#define SEGMENT_T (1<<5)
#define SEGMENT_UPORT D
#define SEGMENT_U (1<<4)
#define SEGMENT_DPPORT D
#define SEGMENT_DP (1<<6)

void segmentDisplayWrite(uint16_t data);
void segmentDisplayInit();
void segmentDisplayLetter(char literka);
void segmentDisplayOff();
void segmentDisplayText(char * tab, uint16_t letterTime);
void segmentDisplayDotOff();
void segmentDisplayDotOn();
void segmentDisplayDigit(uint8_t number);
void segmentDisplayNumber(uint16_t number);
void segmentDisplayWriteAsterisk();
#endif /* SEGMENT_H_ */
