/*
 * ADC_Cfg.h
 *
 *  Created on: Nov 7, 2019
 *      Author: Mohammed Nassar
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_



#include "std_types.h"

/* REFERENCE SELECTION */
#define INTERNAL   2
#define AVCC       1
#define AREF       0

/* ADJUST RESULT   */
#define LEFT_ADJUST           1
#define RIGHT_ADJUST          0

/* AUTO_TRIGGER_EN  */
#define AUTO_TRIGGER_EN       1
#define AUTO_TRIGGER_DIS      0

/*  TRIGGER SOURCE   */
#define TIMER1_ICU           7
#define TIMER1B_OVF          6
#define TIMER1B_CMP          5
#define TIMER0_OVF           4
#define TIMER0_CMP           3
#define EX_INTERRUPT         2
#define ANALOG_COMPARATOR    1
#define FREE_RUNNING         0

/* INTERRUPT */
#define INTERRUPT     1
#define POOLING       0

/*  ADC PRESCALER   */
#define ADPS_128       7
#define ADPS_64        6
#define ADPS_32        5
#define ADPS_16        4
#define ADPS_8         3
#define ADPS_4         2
#define ADPS_2         1

/************** ANALOG CHANNEL *********************/

#define CH_ADC7    7
#define CH_ADC6    6
#define CH_ADC5    5
#define CH_ADC4    4
#define CH_ADC3    3
#define CH_ADC2    2
#define CH_ADC1    1
#define CH_ADC0    0

/*  DIFF INPUT  */
#define DIFF_GND          31
#define DIFF_VBG          30

#define ADC5_ADC2_1X      29
#define ADC4_ADC2_1X      28
#define ADC3_ADC2_1X      27
#define ADC2_ADC2_1X      26
#define ADC1_ADC2_1X      25
#define ADC0_ADC2_1X      24
#define ADC7_ADC1_1X      23
#define ADC6_ADC1_1X      22
#define ADC5_ADC1_1X      21
#define ADC4_ADC1_1X      20
#define ADC3_ADC1_1X      19
#define ADC2_ADC1_1X      18
#define ADC1_ADC1_1X      17
#define ADC0_ADC1_1X      16

#define ADC3_ADC2_200X    15
#define ADC2_ADC2_200X    14
#define ADC3_ADC2_10X     13
#define ADC2_ADC2_10X     12
#define ADC1_ADC0_200X    11
#define ADC0_ADC0_200X    10
#define ADC1_ADC0_10X     9
#define ADC0_ADC0_10X     8



#endif /* ADC_CFG_H_ */
