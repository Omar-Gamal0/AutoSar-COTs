/*
 * Dio.h
 *
 *  Created on: Jul 8, 2021
 *      Author: Omar Gamal
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/* Defining GPIO_PORT type */
typedef struct{
	volatile	u32 			CRL;
	volatile	u32 			CRH;
	volatile	u32 			IDR;
	volatile	u32 			ODR;
	volatile	u32 			BSRR;
	volatile	u32 			BRR;
	volatile	u32 			LCKR;
}GPIO_Port_t;
/***************************/

/* Defining Ports Macros */
#define MGPIO_PORTA			((volatile GPIO_Port_t*)0x40010800)
#define MGPIO_PORTB			((volatile GPIO_Port_t*)0x40010C00)
#define MGPIO_PORTC			((volatile GPIO_Port_t*)0x40011000)
/*************************/



#endif /* DIO_PRIVATE_H_ */
