/*
 * Port_Lcfg.c
 *
 *  Created on: Jul 15, 2021
 *      Author: Omar Gamal
 */


#include "Port.h"
#include "Dio_Private.h"



Port_ConfigType Port_PinsConfig[PortNumberOfPortPins]={
		[LED0_PIN] = {
				.Port_PinInitialMode = PORT_PIN_MODE_DIO,
				.Port_PinInitialDirection = PORT_PIN_OUT,
				.Port_PinDirectionChangeableRuntime = STD_LOW,
				.Port_PinInitialLevel = STD_LOW,
				.Port_PinSlewRate = PORT_PIN_SLEW_RATE_2MHZ,
				.Port_PinOutputMode = PORT_PIN_PUSH_PULL
		},
		[SWITCH1_PIN] = {
				.Port_PinInitialMode = PORT_PIN_MODE_DIO,
				.Port_PinInitialDirection = PORT_PIN_IN,
				.Port_PinDirectionChangeableRuntime = STD_LOW,
				.Port_PinInitialLevel = STD_LOW,
				.Port_PinPullUp_Down = PORT_PIN_WITH_PULL_UP
		}
};
