/*
 * Seven_Segment_prog.c
 *
 *  Created on: Sep 9, 2021
 *      Author: Ahmed El-Gaafrawy
 */
#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_int.h"

#include "Seven_segment_config.h"
#include "Seven_segment_priv.h"

ES_t Seven_Segment_enuInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	u32 Local_u32Check=0;
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_APORT, SEG_APIN , DIO_u8OUTPUT) << 0);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_BPORT, SEG_BPIN , DIO_u8OUTPUT) << 2);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_CPORT, SEG_CPIN , DIO_u8OUTPUT) << 4);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_DPORT, SEG_DPIN , DIO_u8OUTPUT) << 6);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_EPORT, SEG_EPIN , DIO_u8OUTPUT) << 8);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_FPORT, SEG_FPIN , DIO_u8OUTPUT) << 10);
	Local_u32Check |= (DIO_enuSetPinDirection(SEG_GPORT, SEG_GPIN , DIO_u8OUTPUT) << 12);

#if SEG_CMN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
	DIO_enuSetPinDirection(SEG_CMN_PORT, SEG_CMN , DIO_u8OUTPUT);
#elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error"your Common Pin has a wrong selection"
#endif

#if SEG_DOT <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
	DIO_enuSetPinDirection(SEG_DOT_PORT, SEG_DOT , DIO_u8OUTPUT);
#elif SEG_DOT == NOT_CONNECTED || SEG_DOT_PORT == NOT_CONNECTED

#else
#error"your DOT Pin has a wrong selection"
#endif

	*((u8*)0x43) = 0;
	*((u8*)0x5c) = 0;
	*((u8*)0x4a) = 0;

	*((u8*)0x43) = (u8)Local_u32Check;
	*((u8*)0x5c) = (u8)(Local_u32Check>>8);
	*((u8*)0x4a) = (u8)(Local_u32Check>>16);


	u8 Local_u8Iter = 0;
	for(Local_u8Iter=0; Local_u8Iter < 12 ; Local_u8Iter += 2)
	{
		if  ( ( ( (Local_u32Check)>>Local_u8Iter)&3 ) != ES_OK)
		{
			return Local_enuErrorState;
		}
	}
	Local_enuErrorState =ES_OK;

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisplayNum(u8 Copy_u8Num)
{
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_u8Num < 10)
	{
#if SEG_TYPE == COMMON_CATHODE
		DIO_enuSetPinValue(SEG_APORT , SEG_APIN , ((SEG_Au8NumDisplay[Copy_u8Num]>>0)&1) );
		DIO_enuSetPinValue(SEG_BPORT , SEG_BPIN , ((SEG_Au8NumDisplay[Copy_u8Num]>>1)&1) );
		DIO_enuSetPinValue(SEG_CPORT , SEG_CPIN , ((SEG_Au8NumDisplay[Copy_u8Num]>>2)&1) );
		DIO_enuSetPinValue(SEG_DPORT , SEG_DPIN , ((SEG_Au8NumDisplay[Copy_u8Num]>>3)&1) );
		DIO_enuSetPinValue(SEG_EPORT , SEG_EPIN , ((SEG_Au8NumDisplay[Copy_u8Num]>>4)&1) );
		DIO_enuSetPinValue(SEG_FPORT , SEG_FPIN , ((SEG_Au8NumDisplay[Copy_u8Num]>>5)&1) );
		DIO_enuSetPinValue(SEG_GPORT , SEG_GPIN , ((SEG_Au8NumDisplay[Copy_u8Num]>>6)&1) );
#elif SEG_TYPE == COMMON_ANODE
		DIO_enuSetPinValue(SEG_APORT , SEG_APIN , !((SEG_Au8NumDisplay[Copy_u8Num]>>0)&1) );
		DIO_enuSetPinValue(SEG_BPORT , SEG_BPIN , !((SEG_Au8NumDisplay[Copy_u8Num]>>1)&1) );
		DIO_enuSetPinValue(SEG_CPORT , SEG_CPIN , !((SEG_Au8NumDisplay[Copy_u8Num]>>2)&1) );
		DIO_enuSetPinValue(SEG_DPORT , SEG_DPIN , !((SEG_Au8NumDisplay[Copy_u8Num]>>3)&1) );
		DIO_enuSetPinValue(SEG_EPORT , SEG_EPIN , !((SEG_Au8NumDisplay[Copy_u8Num]>>4)&1) );
		DIO_enuSetPinValue(SEG_FPORT , SEG_FPIN , !((SEG_Au8NumDisplay[Copy_u8Num]>>5)&1) );
		DIO_enuSetPinValue(SEG_GPORT , SEG_GPIN , !((SEG_Au8NumDisplay[Copy_u8Num]>>6)&1) );
#else
#error "SEG type has a wrong selection"
#endif
	}
	else
	{
		Local_enuErrorState =ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

ES_t Seven_Segment_enuEnableCommon(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_CMN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8LOW);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8HIGH);
	#else
	#error "SEG type has a wrong selection"
	#endif
#elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error"your Common Pin has a wrong selection"
#endif

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisableCommon(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_CMN <= DIO_u8PIN7 && SEG_CMN_PORT <= DIO_u8PORTD
	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8HIGH);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8LOW);
	#else
	#error "SEG type has a wrong selection"
	#endif
#elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error"your Common Pin has a wrong selection"
#endif

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuEnableDot(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_DOT <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8HIGH);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8LOW);
	#else
	#error "SEG type has a wrong selection"
	#endif
#elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error"your DOT Pin has a wrong selection"
#endif

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuDisableDot(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_DOT <= DIO_u8PIN7 && SEG_DOT_PORT <= DIO_u8PORTD
	#if SEG_TYPE == COMMON_CATHODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8LOW);
	#elif SEG_TYPE == COMMON_ANODE
	Local_enuErrorState = DIO_enuSetPinValue(SEG_CMN_PORT,SEG_CMN , DIO_u8HIGH);
	#else
	#error "SEG type has a wrong selection"
	#endif
#elif SEG_CMN == NOT_CONNECTED || SEG_CMN_PORT == NOT_CONNECTED

#else
#error"your DOT Pin has a wrong selection"
#endif

	return Local_enuErrorState;
}

ES_t Seven_Segment_enuClearDisplay(void)
{
	ES_t Local_enuErrorState = ES_NOK;

#if SEG_TYPE == COMMON_CATHODE
		DIO_enuSetPinValue(SEG_APORT , SEG_APIN , DIO_u8LOW );
		DIO_enuSetPinValue(SEG_BPORT , SEG_BPIN , DIO_u8LOW );
		DIO_enuSetPinValue(SEG_CPORT , SEG_CPIN , DIO_u8LOW );
		DIO_enuSetPinValue(SEG_DPORT , SEG_DPIN , DIO_u8LOW );
		DIO_enuSetPinValue(SEG_EPORT , SEG_EPIN , DIO_u8LOW );
		DIO_enuSetPinValue(SEG_FPORT , SEG_FPIN , DIO_u8LOW );
		DIO_enuSetPinValue(SEG_GPORT , SEG_GPIN , DIO_u8LOW );
#elif SEG_TYPE == COMMON_ANODE
		DIO_enuSetPinValue(SEG_APORT , SEG_APIN , DIO_u8HIGH );
		DIO_enuSetPinValue(SEG_BPORT , SEG_BPIN , DIO_u8HIGH );
		DIO_enuSetPinValue(SEG_CPORT , SEG_CPIN , DIO_u8HIGH );
		DIO_enuSetPinValue(SEG_DPORT , SEG_DPIN , DIO_u8HIGH );
		DIO_enuSetPinValue(SEG_EPORT , SEG_EPIN , DIO_u8HIGH );
		DIO_enuSetPinValue(SEG_FPORT , SEG_FPIN , DIO_u8HIGH );
		DIO_enuSetPinValue(SEG_GPORT , SEG_GPIN , DIO_u8HIGH );
#else
#error "SEG type has a wrong selection"
#endif

	return Local_enuErrorState;
}
