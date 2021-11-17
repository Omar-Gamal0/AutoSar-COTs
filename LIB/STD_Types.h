#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef short int s16;
typedef unsigned long int u32;
typedef signed long int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef float f32;



typedef u8 Std_ReturnType;

typedef struct{
	u16 vendorID;
	u16 moduleID;
	u8 sw_major_version;
	u8 sw_minor_version;
	u8 sw_patch_version;
}Std_VersionInfoType;


#define STD_HIGH		0x01
#define STD_LOW			0x00










#endif
