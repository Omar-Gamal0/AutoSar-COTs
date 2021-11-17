/*
 * Dio.h
 *
 *  Created on: Jul 8, 2021
 *      Author: Omar Gamal
 */

#ifndef DIO_H_
#define DIO_H_

#include "Dio_Cfg.h"
#include "STD_Types.h"

/* Id for the company in the AUTOSAR for example 1999 */
#define DIO_VENDOR_ID    (1999U)

/* Dio Module Id */
#define DIO_MODULE_ID    (120U)


/* Module Version 1.0.0  */
#define DIO_SW_MAJOR_VERSION           	(1U)
#define DIO_SW_MINOR_VERSION           	(0U)
#define DIO_SW_PATCH_VERSION           	(0U)

/* AUTOSAR Version 2.5.0 */
#define DIO_AR_RELEASE_MAJOR_VERSION   	(4U)
#define DIO_AR_RELEASE_MINOR_VERSION   	(4U)
#define DIO_AR_RELEASE_PATCH_VERSION   	(0U)


#define DIO_PORTA					   	((Dio_PortType)0)
#define DIO_PORTB					   	((Dio_PortType)1)
#define DIO_PORTC					   	((Dio_PortType)2)

typedef u8 Dio_ChannelType;		/* Numeric ID of a DIO channel. */
typedef u8 Dio_PortType;		/* Numeric ID of a DIO port. */
typedef u8 Dio_LevelType;		/* These are the possible levels a DIO channel can have (input or output) [STD_LOW -> Physical state 0V, STD_HIGH -> Physical state 5V or 3.3V] */
typedef u16 Dio_PortLevelType;	/* type for the value of a DIO port. (Here: 0x0000...0xFFFF)*/


typedef struct{					/* Type for the definition of a channel group, which consists of several adjoining channels within a port. */
	u16 mask;
	u8 offset;
	Dio_PortType port;
}Dio_ChannelGroupType;


/* Ganeral Values macros */

#define DIO_INPUT		1
#define DIO_OUTPUT		0



/* Dio APIs */

/*
 * Service name: Dio_ReadChannel
 * Parameters (in): ChannelId -> ID of DIO channel
 * Return value:	Dio_LevelType -> STD_HIGH: The physical level of the corresponding Pin is STD_HIGH
 * 									 STD_LOW: The physical level of the corresponding Pin is STD_LOW
 * Description: Returns the value of the specified DIO channel.
 */
Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );

/*
 * Service name: Dio_WriteChannel
 * Parameters (in): ChannelId 	-> ID of DIO channel
 * 					Level 		-> Value to be written
 * Return value: None
 * Description: Service to set a level of a channel.
 */
void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level );

/*
 * Service name: Dio_ReadPort
 * Parameters (in): PortId -> ID of DIO Port
 * Return value: Dio_PortLevelType -> Level of all channels of that port
 * Description: Returns the level of all channels of that port.
 */
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId );

/*
 * Service name: Dio_WritePort
 * Parameters (in): PortId -> ID of DIO Port
 * 					Level -> Value to be written
 * Description: Service to set a value of the port.
 */
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level );

/*
 * Service name: Dio_ReadChannelGroup
 * Parameters (in): ChannelGroupIdPtr -> Pointer to ChannelGroup
 * Return value: Dio_PortLevelType -> Level of a subset of the adjoining bits of a port
 * Description: This Service reads a subset of the adjoining bits of a port.
 */
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr );

/*
 * Service name: Dio_WriteChannelGroup
 * Parameters (in): ChannelGroupIdPtr -> Pointer to ChannelGroup
 * 					Level -> Value to be written
 * Return value: None
 * Description: Service to set a subset of the adjoining bits of a port to a specified level.
 */
void Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level );

/*
 * Service name: Dio_GetVersionInfo
 * Parameters (out): VersionInfo -> Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Service to get the version information of this module.
 */
void Dio_GetVersionInfo( Std_VersionInfoType* VersionInfo );

/*
 * Service name: Dio_FlipChannel
 * Parameters (in): ChannelId -> ID of DIO channel
 * Return value: Dio_LevelType -> STD_HIGH: The physical level of the corresponding Pin is STD_HIGH.
 * 								  STD_LOW: The physical level of the corresponding Pin is STD_LOW.
 * Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return the level of the channel after flip.
 */
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId );

/*
 * Service name: Dio_MaskedWritePort
 * Parameters (in): PortId -> ID of DIO Port
 * 					Level -> Value to be written
 * 					Mask -> Channels to be masked in the port
 * Return value: None
 * Description: Service to set the value of a given port with required mask.
 */
void Dio_MaskedWritePort( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask );





#endif /* DIO_H_ */
