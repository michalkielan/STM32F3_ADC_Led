/*
 * main.h
 *
 *  Created on: 14 gru 2013
 *      Author: michal
 *      Projec: F3_ADC
 */

#ifndef MAIN_H_
#define MAIN_H_


void Clock_Init(void);

#define L3 GPIO_Pin_9		//ledy na porcie E
#define L4 GPIO_Pin_8
#define L5 GPIO_Pin_10
#define L6 GPIO_Pin_15
#define L7 GPIO_Pin_11
#define L8 GPIO_Pin_14
#define L9 GPIO_Pin_12
#define L10 GPIO_Pin_13
#define LED_PORT GPIOE



#define DELAY	(1000)

#include "stm32f3_discovery.h"
#include "stm32f30x.h"
#include "stm32f30x_gpio.h"		//GPIO init
#include "stm32f30x_rcc.h"		//Zegar RCC
#include "stm32f30x_adc.h"		//ADC
#include "stm32f30x_tim.h"		//timery
#include "common.h"				//to samo co stm32fxx_it.h

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void GPIO_conf(void);		//adc_gpio config
void ADC_conf(void);		//tryby adc
void LED_init(void);


/*

#include "stm32f30x_adc.h"
#include "stm32f30x_can.h"
#include "stm32f30x_comp.h"
#include "stm32f30x_crc.h"
#include "stm32f30x_dac.h"
#include "stm32f30x_dbgmcu.h"
#include "stm32f30x_dma.h"
#include "stm32f30x_exti.h"
#include "stm32f30x_flash.h"
#include "stm32f30x_i2c.h"
#include "stm32f30x_iwdg.h"
#include "stm32f30x_misc.h"
#include "stm32f30x_opamp.h"
#include "stm32f30x_pwr.h"
#include "stm32f30x_rtc.h"
#include "stm32f30x_spi.h"
#include "stm32f30x_syscfg.h"
#include "stm32f30x_usart.h"
#include "stm32f30x_wwdg.h"
*/




#endif /* MAIN_H_ */
