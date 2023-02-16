#include "stdTypes.h"
#include "errorStates.h"

#include "DIO_int.h"
#include "LED_config.h"
#include "LED_priv.h"

LED_t LED_AstrLedConfig [LED_NUM] =
{
		{DIO_u8PORTA, DIO_u8PIN5, LED_SINK, LED_OFF},
		{DIO_u8PORTB, DIO_u8PIN2, LED_SOURCE, LED_ON},
		{DIO_u8PORTC, DIO_u8PIN1, LED_SOURCE, LED_OFF}
};

