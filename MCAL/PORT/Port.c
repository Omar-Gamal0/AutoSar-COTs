/*
 * Port.c
 *
 *  Created on: Jul 15, 2021
 *      Author: Omar Gamal
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/stm32f103C8.h"
#include "Port.h"
#include "../DIO/DIO.h"

//	ready to be used in DIO MODE

u16 PortA_DIO_OutputPins = 0;
u16 PortB_DIO_OutputPins = 0;
u16 PortC_DIO_OutputPins = 0;
u16 PortA_DIO_InputPins = 0;
u16 PortB_DIO_InputPins = 0;
u16 PortC_DIO_InputPins = 0;

#define PORT_PIN_IN_PORTA(PIN_ID) ((PIN_ID / 16) == 0)
#define PORT_PIN_IN_PORTB(PIN_ID) ((PIN_ID / 16) == 1)
#define PORT_PIN_IN_PORTC(PIN_ID) ((PIN_ID / 16) == 2)
void LOC_voidDeclearOutputPins(u8 PinCounter);
void LOC_voidOpenDrainInit(u8 PinCounter);
void LOC_voidSlewRateInit(u8 PinCounter, u8 Copy_u8MHZ);
void LOC_voidSetInialValueHigh(u8 PinCounter);
void LOC_voidDeclaerInputPins(u8 PinCounter);
void LOC_voidPullUpDownInit(u8 PinCounter, u8 Copy_u8PullUpDawnState);
void LOC_voidEnablingInternalPullUpResistor(u8 PinCounter);

void Port_Init(const Port_ConfigType *ConfigPtr)
{
	/* Resetting GPIO register values */
	GPIOA->CRH = 0;
	GPIOA->CRL = 0;
	GPIOA->ODR = 0;
	/**********************************/
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	for (u8 PinCounter = 0; PinCounter < PortNumberOfPortPins; PinCounter++)
	{
		switch (ConfigPtr[PinCounter].Port_PinInitialMode)
		{
		case PORT_PIN_MODE_DIO:
			switch (ConfigPtr[PinCounter].Port_PinInitialDirection)
			{
			case PORT_PIN_OUT:
				LOC_voidDeclearOutputPins(PinCounter);
				// PORT_PIN_OPEN_DRAIN
				switch (ConfigPtr[PinCounter].Port_PinOutputMode)
				{
				case PORT_PIN_OPEN_DRAIN:
					LOC_voidOpenDrainInit(PinCounter);
					break;
				default:
					/* default output mode is push-pull */
					break;
				}
				//SLEW_RATE
				switch (ConfigPtr[PinCounter].Port_PinSlewRate)
				{
				case PORT_PIN_SLEW_RATE_10MHZ:
					LOC_voidSlewRateInit(PinCounter, 0b01);
					break;
				case PORT_PIN_SLEW_RATE_50MHZ:
					LOC_voidSlewRateInit(PinCounter, 0b11);
					break;
				default:
					/* default slew-rate is 2MHZ */
					LOC_voidSlewRateInit(PinCounter, 0b10);
					break;
				}

				//Initial Level
				switch (ConfigPtr[PinCounter].Port_PinInitialLevel)
				{
				case STD_HIGH:
					LOC_voidSetInialValueHigh(PinCounter);
				default:
					/* default initial level is STD_LOW */
					break;
				}
				break;

			default: /* start of default case of switch(ConfigPtr[PinCounter].Port_PinInitialDirection) */
					 /* default value is Input */
				LOC_voidDeclaerInputPins(PinCounter);
				switch (ConfigPtr[PinCounter].Port_PinPullUp_Down)
				{
				case PORT_PIN_NO_PULL_UP_DOWN:
					LOC_voidPullUpDownInit(PinCounter, 0b01);
					break;
				case PORT_PIN_WITH_PULL_UP:
					LOC_voidPullUpDownInit(PinCounter, 0b10);
					LOC_voidEnablingInternalPullUpResistor(PinCounter);
					break;
				default:
					LOC_voidPullUpDownInit(PinCounter, 0b10);
					break;
				}
				break;
			}
			break; /* End of case PORT_PIN_MODE_DIO */
		}
	}
}
void LOC_voidDeclearOutputPins(u8 PinCounter)
{
	if (PORT_PIN_IN_PORTA(PinCounter))
	{
		SET_BIT(PortA_DIO_OutputPins, PinCounter);
	}
	else if (PORT_PIN_IN_PORTB(PinCounter))
	{
		SET_BIT(PortB_DIO_OutputPins, PinCounter);
	}
	else if (PORT_PIN_IN_PORTC(PinCounter))
	{
		SET_BIT(PortC_DIO_OutputPins, PinCounter);
	}
}
void LOC_voidOpenDrainInit(u8 PinCounter)
{
	/* Handling PortA */
	if (PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOA->CRL |= ((0b01) << ((PinCounter * 4) + 2));
	}
	else if (PORT_PIN_IN_PORTA(PinCounter))
	{
		GPIOA->CRH |= ((0b01) << ((PinCounter * 4) + 2));
	}
	/* Handling PortB */
	else if (PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOB->CRL |= ((0b01) << (((PinCounter % 16) * 4) + 2));
	}
	else if (PORT_PIN_IN_PORTB(PinCounter))
	{
		GPIOB->CRH |= ((0b01) << (((PinCounter % 16) * 4) + 2));
	}
	/* Handling PortC */
	else if (PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOC->CRL |= ((0b01) << (((PinCounter % 16) * 4) + 2));
	}
	else if (PORT_PIN_IN_PORTC(PinCounter))
	{
		GPIOC->CRH |= ((0b01) << (((PinCounter % 16) * 4) + 2));
	}
}

void LOC_voidSlewRateInit(u8 PinCounter, u8 Copy_u8MHZ)
{
	/* Handling PortA */
	if (PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOA->CRL |= ((Copy_u8MHZ) << (PinCounter * 4));
	}
	else if (PORT_PIN_IN_PORTA(PinCounter))
	{
		GPIOA->CRH |= ((Copy_u8MHZ) << (PinCounter * 4));
	}
	/* Handling PortB */
	else if (PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOB->CRL |= ((Copy_u8MHZ) << ((PinCounter % 16) * 4));
	}
	else if (PORT_PIN_IN_PORTB(PinCounter))
	{
		GPIOB->CRH |= ((Copy_u8MHZ) << ((PinCounter % 16) * 4));
	}
	/* Handling PortC */
	else if (PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOC->CRL |= ((Copy_u8MHZ) << ((PinCounter % 16) * 4));
	}
	else if (PORT_PIN_IN_PORTC(PinCounter))
	{
		GPIOC->CRH |= ((Copy_u8MHZ) << ((PinCounter % 16) * 4));
	}
}
void LOC_voidSetInialValueHigh(u8 PinCounter)
{
	switch (PinCounter / 16)
	{
	case DIO_PORTA:
		GPIOA->BSRR = (1 << (PinCounter % 16));
		break;
	case DIO_PORTB:
		GPIOB->BSRR = (1 << (PinCounter % 16));
		break;
	case DIO_PORTC:
		GPIOC->BSRR = (1 << (PinCounter % 16));
		break;
	default:
		break;
	}
}

void LOC_voidDeclaerInputPins(u8 PinCounter)
{
	if (PORT_PIN_IN_PORTA(PinCounter))
	{
		SET_BIT(PortA_DIO_InputPins, PinCounter);
	}
	else if (PORT_PIN_IN_PORTB(PinCounter))
	{
		SET_BIT(PortB_DIO_InputPins, PinCounter);
	}
	else if (PORT_PIN_IN_PORTC(PinCounter))
	{
		SET_BIT(PortC_DIO_InputPins, PinCounter);
	}
}
void LOC_voidPullUpDownInit(u8 PinCounter, u8 Copy_u8PullUpDawnState)
{ /* Handling PortA */
	if (PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOA->CRL |= ((Copy_u8PullUpDawnState) << ((PinCounter * 4) + 2));
	}
	else if (PORT_PIN_IN_PORTA(PinCounter))
	{
		GPIOA->CRH |= ((Copy_u8PullUpDawnState) << ((PinCounter * 4) + 2));
	}
	/* Handling PortB */
	else if (PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOB->CRL |= ((Copy_u8PullUpDawnState) << (((PinCounter % 16) * 4) + 2));
	}
	else if (PORT_PIN_IN_PORTB(PinCounter))
	{
		GPIOB->CRH |= ((Copy_u8PullUpDawnState) << (((PinCounter % 16) * 4) + 2));
	}
	/* Handling PortC */
	else if (PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
	{
		GPIOC->CRL |= ((Copy_u8PullUpDawnState) << (((PinCounter % 16) * 4) + 2));
	}
	else if (PORT_PIN_IN_PORTC(PinCounter))
	{
		GPIOC->CRH |= ((Copy_u8PullUpDawnState) << (((PinCounter % 16) * 4) + 2));
	}
}
void LOC_voidEnablingInternalPullUpResistor(u8 PinCounter)
{
	switch (PinCounter / 16)
	{
	case DIO_PORTA:
		GPIOA->BSRR = (1 << (PinCounter % 16));
		break;
	case DIO_PORTB:
		GPIOB->BSRR = (1 << (PinCounter % 16));
		break;
	case DIO_PORTC:
		GPIOC->BSRR = (1 << (PinCounter % 16));
		break;
	default:
		break;
	}
}