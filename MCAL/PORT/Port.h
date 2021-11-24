/*
 * Port.h
 *
 *  Created on: Jul 15, 2021
 *      Author: Omar Gamal
 */

#ifndef PORT_H_
#define PORT_H_

#include "../../LIB/stm32f103C8.h"
#include "Port_Cfg.h"

////////////////////////////////////////////////////////////////////////////////////////////
/* Defining module types */
typedef u8 Port_PinType;
typedef enum PinDirectionType
{
	PORT_PIN_IN = 255,
	PORT_PIN_OUT = 254
} Port_PinDirectionType;

typedef enum PinModeType
{

	PORT_PIN_MODE_DIO = 255,
	PORT_PIN_MODE_ADC = 254,
	PORT_PIN_MODE_SPI = 253,
	PORT_PIN_MODE_CAN = 252,
	PORT_PIN_MODE_UART = 251,
	PORT_PIN_MODE_I2C = 250,
	PORT_PIN_MODE_TIMER = 249

} Port_PinModeType;

typedef enum PinSlewRateType
{
	PORT_PIN_SLEW_RATE_2MHZ = 255,
	PORT_PIN_SLEW_RATE_10MHZ = 254,
	PORT_PIN_SLEW_RATE_50MHZ = 253
} Port_PinSlewRateType;

typedef enum PinOutputModeType
{
	PORT_PIN_PUSH_PULL = 255,
	PORT_PIN_OPEN_DRAIN = 254
} Port_PinOutputModeType;

typedef enum PinPullUp_DownType
{
	PORT_PIN_NO_PULL_UP_DOWN = 255,
	PORT_PIN_WITH_PULL_UP = 254,
	PORT_PIN_WITH_PULL_DOWN = 253
} Port_PinPullUp_DownType;

typedef struct
{
	Port_PinModeType Port_PinInitialMode;
	Port_PinDirectionType Port_PinInitialDirection; /* default value is Input*/
	u8 Port_PinInitialLevel;
	u8 Port_PinDirectionChangeableRuntime;		 /* decides whether the direction is changeable during runtime or not */
	Port_PinSlewRateType Port_PinSlewRate;		 /* default value is 2MHZ */
	Port_PinPullUp_DownType Port_PinPullUp_Down; /* default value is pull-down enabled */
	Port_PinOutputModeType Port_PinOutputMode;	 /* default value is push-pull */
} Port_ConfigType;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Functions prototypes */
/*
 * Port_Init
 *
 *
 *
 *
 *
 *
 */
void Port_Init(const Port_ConfigType *ConfigPtr);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* PORT_H_ */
