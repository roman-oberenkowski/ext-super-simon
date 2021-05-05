/*
 * storage.h
 *
 *  Created on: 17 Aug 2019
 *      Author: unknown
 */

#ifndef STORAGE_H_
#define STORAGE_H_

void storageReadMessage(char * message, uint8_t * length);
void storageWriteMessage(char * message, uint8_t length);
uint8_t storageOk();
void flagOk();

#endif /* STORAGE_H_ */
