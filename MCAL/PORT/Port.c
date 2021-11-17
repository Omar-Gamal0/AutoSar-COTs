/*
 * Port.c
 *
 *  Created on: Jul 15, 2021
 *      Author: Omar Gamal
 */


#include "BIT_MATH.h"
#include "Port.h"
#include "Dio_Private.h"
#include "Dio.h"


//	ready to be used in DIO MODE


u16 PortA_DIO_OutputPins = 0;
u16 PortB_DIO_OutputPins = 0;
u16 PortC_DIO_OutputPins = 0;

u16 PortA_DIO_InputPins = 0;
u16 PortB_DIO_InputPins = 0;
u16 PortC_DIO_InputPins = 0;

#define PORT_PIN_IN_PORTA(PIN_ID)	((PIN_ID/16) == 0)
#define PORT_PIN_IN_PORTB(PIN_ID)	((PIN_ID/16) == 1)
#define PORT_PIN_IN_PORTC(PIN_ID)	((PIN_ID/16) == 2)

void Port_Init(const Port_ConfigType* ConfigPtr)
{
	/* Resetting GPIO register values */
	MGPIO_PORTA->CRH = 0;
	MGPIO_PORTA->CRL = 0;
	MGPIO_PORTA->ODR = 0;
	/**********************************/

	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	// remember to test if Pin_ID 0 would be defaultly configured because of un-configured pins
	for (u8 PinCounter = 0; PinCounter < PortNumberOfPortPins; PinCounter++)
	{
		switch(ConfigPtr[PinCounter].Port_PinInitialMode)
		{
		case PORT_PIN_MODE_DIO:
			switch(ConfigPtr[PinCounter].Port_PinInitialDirection)
			{

			case PORT_PIN_OUT:
				if(PORT_PIN_IN_PORTA(PinCounter))
				{
					SET_BIT(PortA_DIO_OutputPins,PinCounter);
				}else if(PORT_PIN_IN_PORTB(PinCounter))
				{
					SET_BIT(PortB_DIO_OutputPins,PinCounter);
				}else if(PORT_PIN_IN_PORTC(PinCounter))
				{
					SET_BIT(PortC_DIO_OutputPins,PinCounter);
				}

				switch(ConfigPtr[PinCounter].Port_PinOutputMode)
				{
				case PORT_PIN_OPEN_DRAIN:

					/* Handling PortA */
					if(PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTA->CRL |= ((0b01)<< ((PinCounter * 4) + 2));
					}else if(PORT_PIN_IN_PORTA(PinCounter))
					{
						MGPIO_PORTA->CRH |= ((0b01)<< ((PinCounter * 4) + 2));
					}
					/* Handling PortB */
					else if(PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTB->CRL |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
					}else if(PORT_PIN_IN_PORTB(PinCounter))
					{
						MGPIO_PORTB->CRH |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
					}
					/* Handling PortC */
					else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTC->CRL |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
					}else if(PORT_PIN_IN_PORTC(PinCounter))
					{
						MGPIO_PORTC->CRH |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
					}
					break;		/* End of PORT_PIN_OPEN_DRAIN case of switch(ConfigPtr[PinCounter].Port_PinOutputMode) */

					/* default output mode is push-pull */
				default:

					break;		/* End of default case of switch(ConfigPtr[PinCounter].Port_PinOutputMode) */
				}				/* End of switch...case of switch(ConfigPtr[PinCounter].Port_PinOutputMode) */


				switch(ConfigPtr[PinCounter].Port_PinSlewRate)
				{
				case PORT_PIN_SLEW_RATE_10MHZ:

					/* Handling PortA */
					if(PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTA->CRL |= ((0b01)<< (PinCounter * 4));
					}else if(PORT_PIN_IN_PORTA(PinCounter))
					{
						MGPIO_PORTA->CRH |= ((0b01)<< (PinCounter * 4));
					}
					/* Handling PortB */
					else if(PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTB->CRL |= ((0b01)<< ((PinCounter % 16) * 4));
					}else if(PORT_PIN_IN_PORTB(PinCounter))
					{
						MGPIO_PORTB->CRH |= ((0b01)<< ((PinCounter % 16) * 4));
					}
					/* Handling PortC */
					else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTC->CRL |= ((0b01)<< ((PinCounter % 16) * 4));
					}else if(PORT_PIN_IN_PORTC(PinCounter))
					{
						MGPIO_PORTC->CRH |= ((0b01)<< ((PinCounter % 16) * 4));
					}

					break;			/* End of PORT_PIN_SLEW_RATE_10MHZ */
				case PORT_PIN_SLEW_RATE_50MHZ:

					/* Handling PortA */
					if(PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTA->CRL |= ((0b11)<< (PinCounter * 4));
					}else if(PORT_PIN_IN_PORTA(PinCounter))
					{
						MGPIO_PORTA->CRH |= ((0b11)<< (PinCounter * 4));
					}
					/* Handling PortB */
					else if(PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTB->CRL |= ((0b11)<< ((PinCounter % 16) * 4));
					}else if(PORT_PIN_IN_PORTB(PinCounter))
					{
						MGPIO_PORTB->CRH |= ((0b11)<< ((PinCounter % 16) * 4));
					}
					/* Handling PortC */
					else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTC->CRL |= ((0b11)<< ((PinCounter % 16) * 4));
					}else if(PORT_PIN_IN_PORTC(PinCounter))
					{
						MGPIO_PORTC->CRH |= ((0b11)<< ((PinCounter % 16) * 4));
					}

					break;		/* End of PORT_PIN_SLEW_RATE_50MHZ */

					/* default slew-rate is 2MHZ */
				default:		/* start of default case of switch(ConfigPtr[PinCounter].Port_PinSlewRate) */

					/* Handling PortA */
					if(PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTA->CRL |= ((0b10)<< (PinCounter * 4));
					}else if(PORT_PIN_IN_PORTA(PinCounter))
					{
						MGPIO_PORTA->CRH |= ((0b10)<< (PinCounter * 4));
					}
					/* Handling PortB */
					else if(PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTB->CRL |= ((0b10)<< ((PinCounter % 16) * 4));
					}else if(PORT_PIN_IN_PORTB(PinCounter))
					{
						MGPIO_PORTB->CRH |= ((0b10)<< ((PinCounter % 16) * 4));
					}
					/* Handling PortC */
					else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
					{
						MGPIO_PORTC->CRL |= ((0b10)<< ((PinCounter % 16) * 4));
					}else if(PORT_PIN_IN_PORTC(PinCounter))
					{
						MGPIO_PORTC->CRH |= ((0b10)<< ((PinCounter % 16) * 4));
					}


					break;		/* End of default case of switch(ConfigPtr[PinCounter].Port_PinSlewRate) */
				}				/* End of switch...case of switch(ConfigPtr[PinCounter].Port_PinSlewRate) */


				switch(ConfigPtr[PinCounter].Port_PinInitialLevel)
				{
				case STD_HIGH:

					switch(PinCounter/16)
					{
					case DIO_PORTA:
						MGPIO_PORTA->BSRR = (1<<(PinCounter%16));		break;
					case DIO_PORTB:
						MGPIO_PORTB->BSRR = (1<<(PinCounter%16));		break;
					case DIO_PORTC:
						MGPIO_PORTC->BSRR = (1<<(PinCounter%16)); 		break;
					default:
						break;
					}

					break;

					/* default initial level is STD_LOW */
				default:

					break;		/* End of default case of switch(ConfigPtr[PinCounter].Port_PinInitialLevel) */
				}				/* End of switch...case of switch(ConfigPtr[PinCounter].Port_PinInitialLevel) */


				break;		/* End of PORT_PIN_OUT */
				/* default value is Input */
			default:		/* start of default case of switch(ConfigPtr[PinCounter].Port_PinInitialDirection) */
				if(PORT_PIN_IN_PORTA(PinCounter))
				{
					SET_BIT(PortA_DIO_InputPins,PinCounter);
				}else if(PORT_PIN_IN_PORTB(PinCounter))
				{
					SET_BIT(PortB_DIO_InputPins,PinCounter);
				}else if(PORT_PIN_IN_PORTC(PinCounter))
				{
					SET_BIT(PortC_DIO_InputPins,PinCounter);
				}
			switch(ConfigPtr[PinCounter].Port_PinPullUp_Down)
			{
			case PORT_PIN_NO_PULL_UP_DOWN:
				/* Handling PortA */
				if(PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTA->CRL |= ((0b01)<< ((PinCounter * 4) + 2));
				}else if(PORT_PIN_IN_PORTA(PinCounter))
				{
					MGPIO_PORTA->CRH |= ((0b01)<< ((PinCounter * 4) + 2));
				}
				/* Handling PortB */
				else if(PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTB->CRL |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
				}else if(PORT_PIN_IN_PORTB(PinCounter))
				{
					MGPIO_PORTB->CRH |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
				}
				/* Handling PortC */
				else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTC->CRL |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
				}else if(PORT_PIN_IN_PORTC(PinCounter))
				{
					MGPIO_PORTC->CRH |= ((0b01)<< (((PinCounter % 16) * 4) + 2));
				}

				break;		/* End of case PORT_PIN_NO_PULL_UP_DOWN */

			case PORT_PIN_WITH_PULL_UP:
				/* Handling PortA */
				if(PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTA->CRL |= ((0b10) << ((PinCounter * 4) + 2));
				}else if(PORT_PIN_IN_PORTA(PinCounter))
				{
					MGPIO_PORTA->CRH |= ((0b10)<< ((PinCounter * 4) + 2));
				}

				/* Handling PortB */

				else if(PORT_PIN_IN_PORTB(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTB->CRL |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}else if(PORT_PIN_IN_PORTA(PinCounter))
				{
					MGPIO_PORTB->CRH |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}


				/* Handling PortC */

				else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTC->CRL |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}else if(PORT_PIN_IN_PORTA(PinCounter))
				{
					MGPIO_PORTC->CRH |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}

				/* Enabling internal Pull up resistor */

				switch(PinCounter/16)
				{
				case DIO_PORTA:
					MGPIO_PORTA->BSRR = (1<<(PinCounter%16));		break;
				case DIO_PORTB:
					MGPIO_PORTB->BSRR = (1<<(PinCounter%16));		break;
				case DIO_PORTC:
					MGPIO_PORTC->BSRR = (1<<(PinCounter%16)); 		break;
				default:
					break;
				}

				break;		/* End of case PORT_PIN_WITH_PULL_UP*/

			default:		/* start of default case of switch(ConfigPtr[PinCounter].Port_PinPullUp_Down) */

				/* Handling PortA */
				if(PORT_PIN_IN_PORTA(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTA->CRL |= ((0b10)<< ((PinCounter * 4) + 2));
				}else if(PORT_PIN_IN_PORTA(PinCounter))
				{
					MGPIO_PORTA->CRH |= ((0b10)<< ((PinCounter * 4) + 2));
				}

				/* Handling PortB */

				else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTB->CRL |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}else if(PORT_PIN_IN_PORTA(PinCounter))
				{
					MGPIO_PORTB->CRH |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}


				/* Handling PortC */

				else if(PORT_PIN_IN_PORTC(PinCounter) && ((PinCounter % 16) < 8))
				{
					MGPIO_PORTC->CRL |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}else if(PORT_PIN_IN_PORTA(PinCounter))
				{
					MGPIO_PORTC->CRH |= ((0b10)<< (((PinCounter % 16) * 4) + 2));
				}

				break;		/* End of default case of switch(ConfigPtr[PinCounter].Port_PinPullUp_Down) */
			}				/* End of switch...case of switch(ConfigPtr[PinCounter].Port_PinPullUp_Down) */

				break;		/* End of default case of switch(ConfigPtr[PinCounter].Port_PinInitialDirection) */
			}				/* End of switch...case of switch(ConfigPtr[PinCounter].Port_PinInitialDirection) */
			break;			/* End of case PORT_PIN_MODE_DIO */

		}
	}
}
