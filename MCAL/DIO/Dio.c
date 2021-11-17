/*
 * Dio.c
 *
 *  Created on: Jul 8, 2021
 *      Author: Omar Gamal
 */

#include "BIT_MATH.h"
#include "Dio.h"
#include "Dio_Private.h"

extern u16 PortA_DIO_OutputPins;
extern u16 PortB_DIO_OutputPins;
extern u16 PortC_DIO_OutputPins;

extern u16 PortA_DIO_InputPins;
extern u16 PortB_DIO_InputPins;
extern u16 PortC_DIO_InputPins;

/*
 * Service name: Dio_ReadChannel
 * Parameters (in): ChannelId -> ID of DIO channel
 * Return value:	Dio_LevelType -> STD_HIGH: The physical level of the corresponding Pin is STD_HIGH
 * 									 STD_LOW: The physical level of the corresponding Pin is STD_LOW
 * Description: Returns the value of the specified DIO channel.
 */
Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId )
{
	switch(ChannelId/16)
	{
	case DIO_PORTA:
		return GET_BIT(((MGPIO_PORTA->IDR) & (PortA_DIO_InputPins | PortA_DIO_OutputPins) ),(ChannelId%16));
		break;
	case DIO_PORTB:
		return GET_BIT((MGPIO_PORTB->IDR & (PortB_DIO_InputPins | PortB_DIO_OutputPins) ),(ChannelId%16));
		break;
	case DIO_PORTC:
		if((ChannelId%16)>12){
			return GET_BIT((MGPIO_PORTC->IDR & (PortC_DIO_InputPins | PortC_DIO_OutputPins) ),(ChannelId%16));
		}
		else{
			/* call DET with error code DIO_E_PARAM_INVALID_CHANNEL_ID */
			return 0;
		}
		break;
	default: /* call DET with error code DIO_E_PARAM_INVALID_CHANNEL_ID */
		return 0;
		break;
	}
}

/*
 * Service name: Dio_WriteChannel
 * Parameters (in): ChannelId 	-> ID of DIO channel
 * 					Level 		-> Value to be written
 * Return value: None
 * Description: Service to set a level of a channel.
 */
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level )
{
	switch(ChannelId/16)
	{
		case DIO_PORTA:
			switch(Level)
			{
			case STD_LOW: MGPIO_PORTA->BRR = ((1<<(ChannelId%16)) & (PortA_DIO_OutputPins) );	break;
			default: MGPIO_PORTA->BSRR = ((1<<(ChannelId%16)) & (PortA_DIO_OutputPins) ); break;
			}
			break;
		case DIO_PORTB:
			switch(Level)
			{
			case STD_LOW: MGPIO_PORTB->BRR = ((1<<(ChannelId%16)) & (PortB_DIO_OutputPins) );	break;
			default: MGPIO_PORTB->BSRR = ((1<<(ChannelId%16)) & (PortB_DIO_OutputPins) ); break;
			}
			break;
		case DIO_PORTC:
			if((ChannelId%16)>12){
				switch(Level)
				{
				case STD_LOW: MGPIO_PORTC->BRR = ((1<<(ChannelId%16)) & (PortC_DIO_OutputPins) );	break;
				default: MGPIO_PORTC->BSRR = ((1<<(ChannelId%16)) & (PortC_DIO_OutputPins) ); break;
				}
			}
			else{
				/* call DET with error code DIO_E_PARAM_INVALID_CHANNEL_ID */
			}
			break;
		default: /* call DET with error code DIO_E_PARAM_INVALID_CHANNEL_ID */
			break;
	}
}

/*
 * Service name: Dio_ReadPort
 * Parameters (in): PortId -> ID of DIO Port
 * Return value: Dio_PortLevelType -> Level of all channels of that port
 * Description: Returns the level of all channels of that port.
 */
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
{
	switch(PortId)
	{
	case DIO_PORTA:
		return (0xFFFF & ((MGPIO_PORTA->IDR) & (PortA_DIO_InputPins | PortA_DIO_OutputPins) ));
		break;
	case DIO_PORTB:
		return (0xFFFF & ((MGPIO_PORTB->IDR) & (PortB_DIO_InputPins | PortB_DIO_OutputPins) ));
		break;
	case DIO_PORTC:
		return (0xE000 & ((MGPIO_PORTC->IDR) & (PortC_DIO_InputPins | PortC_DIO_OutputPins) ));
		break;
	default: /* call DET with error code DIO_E_PARAM_INVALID_PORT_ID */
		return 0;
		break;
	}
}

/*
 * Service name: Dio_WritePort
 * Parameters (in): PortId -> ID of DIO Port
 * 					Level -> Value to be written
 * Description: Service to set a value of the port.
 */
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
	switch(PortId)
	{
	case DIO_PORTA:
		MGPIO_PORTA->ODR = (Level & (PortA_DIO_OutputPins) );
		break;
	case DIO_PORTB:
		MGPIO_PORTB->ODR = (Level & (PortB_DIO_OutputPins) );
		break;
	case DIO_PORTC:
		MGPIO_PORTC->ODR = (0xE000 & (Level & (PortC_DIO_OutputPins) ));
		break;
	default: /* call DET with error code DIO_E_PARAM_INVALID_PORT_ID */
		break;
	}
}

/*
 * Service name: Dio_ReadChannelGroup
 * Parameters (in): ChannelGroupIdPtr -> Pointer to ChannelGroup
 * Return value: Dio_PortLevelType -> Level of a subset of the adjoining bits of a port
 * Description: This Service reads a subset of the adjoining bits of a port.
 */
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
	Dio_PortLevelType TempPortVal = 0;
	switch(ChannelGroupIdPtr->port)
	{
	case DIO_PORTA:
		TempPortVal = ChannelGroupIdPtr->mask & ((MGPIO_PORTA->IDR) & (PortA_DIO_InputPins | PortA_DIO_OutputPins));
		break;
	case DIO_PORTB:
		TempPortVal = ChannelGroupIdPtr->mask & ((MGPIO_PORTB->IDR) & (PortB_DIO_InputPins | PortB_DIO_OutputPins));
		break;
	case DIO_PORTC:
		if(ChannelGroupIdPtr->mask >= 0xE000){
			TempPortVal = ChannelGroupIdPtr->mask & ((MGPIO_PORTC->IDR) & (PortC_DIO_InputPins | PortC_DIO_OutputPins));
		}
		else
		{
			 /* call DET with error code DIO_E_PARAM_INVALID_GROUP */
		}
		break;
	default: /* call DET with error code DIO_E_PARAM_INVALID_GROUP */
		break;
	}
	TempPortVal = TempPortVal >> ChannelGroupIdPtr->offset;
	return TempPortVal;

}

/*
 * Service name: Dio_WriteChannelGroup
 * Parameters (in): ChannelGroupIdPtr -> Pointer to ChannelGroup
 * 					Level -> Value to be written
 * Return value: None
 * Description: Service to set a subset of the adjoining bits of a port to a specified level.
 */
void Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level )
{
	Level &= ChannelGroupIdPtr->mask;
	switch(ChannelGroupIdPtr->port)
	{
	case DIO_PORTA:
		MGPIO_PORTA->BRR = ChannelGroupIdPtr->mask;
		MGPIO_PORTA->BSRR = ( Level & (PortA_DIO_OutputPins) );
		break;
	case DIO_PORTB:
		MGPIO_PORTB->BRR = ChannelGroupIdPtr->mask;
		MGPIO_PORTB->BSRR = ( Level & (PortB_DIO_OutputPins) );
		break;
	case DIO_PORTC:
			MGPIO_PORTC->BRR = ((ChannelGroupIdPtr->mask) & 0xE000);
			MGPIO_PORTC->BSRR = (( Level & (PortC_DIO_OutputPins) ) & 0xE000);

		break;
	default: /* call DET with error code DIO_E_PARAM_INVALID_GROUP */
		break;
	}
}

/*
 * Service name: Dio_GetVersionInfo
 * Parameters (out): VersionInfo -> Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Service to get the version information of this module.
 */
void Dio_GetVersionInfo( Std_VersionInfoType* VersionInfo )
{
	VersionInfo->moduleID = DIO_MODULE_ID;
	VersionInfo->vendorID = DIO_VENDOR_ID;
	VersionInfo->sw_major_version = DIO_SW_MAJOR_VERSION;
	VersionInfo->sw_minor_version = DIO_SW_MINOR_VERSION;
	VersionInfo->sw_patch_version = DIO_SW_PATCH_VERSION;
}

/*
 * Service name: Dio_FlipChannel
 * Parameters (in): ChannelId -> ID of DIO channel
 * Return value: Dio_LevelType -> STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
 * 								  STD_LOW: The physical level of the corresponding Pin is STD_LOW.
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return the level of the channel after flip.
 */
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId )
{
	Dio_LevelType TempPinState = Dio_ReadChannel(ChannelId);
	Dio_WriteChannel(ChannelId,(0x01^TempPinState));
	return Dio_ReadChannel(ChannelId);
}

/*
 * Service name: Dio_MaskedWritePort
 * Parameters (in): PortId -> ID of DIO Port
 * 					Level -> Value to be written
 * 					Mask -> Channels to be masked in the port
 * Return value: None
 * Description: Service to set the value of a given port with required mask.
 */
void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask )
{
	Level &= Mask;
	switch(PortId)
	{
	case DIO_PORTA:
		MGPIO_PORTA->BRR = Mask;
		MGPIO_PORTA->BSRR = ( Level & (PortA_DIO_OutputPins) );
		break;
	case DIO_PORTB:
		MGPIO_PORTB->BRR = Mask;
		MGPIO_PORTB->BSRR = ( Level & (PortB_DIO_OutputPins) );
		break;
	case DIO_PORTC:
		MGPIO_PORTC->BRR = (Mask & 0xE000);
		MGPIO_PORTC->BSRR = (( Level & (PortC_DIO_OutputPins) ) & 0xE000);
		break;
	default: /* call DET with error code DIO_E_PARAM_INVALID_GROUP */
		break;
	}
}


