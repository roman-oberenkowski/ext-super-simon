/*
 * macros.h
 *
 *  Created on: 12 Aug 2019
 *      Author: unknown
 */

#ifndef MACROS_H_
#define MACROS_H_
//Pomocnicze
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)


#endif /* MACROS_H_ */
