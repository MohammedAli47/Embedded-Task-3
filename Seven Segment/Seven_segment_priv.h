/*
 * Seven_segment_priv.h
 *
 *  Created on: Sep 9, 2021
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef SEVEN_SEGMENT_PRIV_H_
#define SEVEN_SEGMENT_PRIV_H_

#define COMMON_ANODE		5
#define COMMON_CATHODE		19

#define NOT_CONNECTED		20

u8 SEG_Au8NumDisplay []= {  0x3f, 0x06, 0x5B,
							0x4F, 0x66, 0x6D,
							0x7D, 0x07, 0x7F,
							0x6F};

#endif /* SEVEN_SEGMENT_PRIV_H_ */
