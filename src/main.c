/*
 * 		 Project: F3_ADC
 * 		 Board: STM32F3 - discovery
 * 		 data: 15.12.2013
 *       Autor: Michał Kielan
 *       notes: pomiar ADC - pin PC1, VDC = 3V
 */

#include "main.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
TIM_OCInitTypeDef TIM_OCTInitStruct;
GPIO_InitTypeDef GPIO_InitStruct;

ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStructure;

__IO uint16_t ADC1_ConvertedValue;
__IO uint16_t ADC1_ConvertedVoltage;
__IO uint16_t calibration_value;

int main(void)
{
	Clock_Init();
	GPIO_conf();
	ADC_conf();
	LED_init();

	while (1) {

		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

		ADC1_ConvertedValue = ADC_GetConversionValue(ADC1);
		ADC1_ConvertedVoltage = (ADC1_ConvertedValue * 3300) / 0xFFF;

		GPIO_Write(LED_PORT, ADC1_ConvertedValue);	//ADC max 0x0f00
				_delay_ms(10);
	}

	return 0;
}

void Clock_Init(void)	{

	uint32_t ii;	//systick timer

	SysTick_Config(72);		//1us if f_clk = 72Mhz

	SystemCoreClockUpdate();
	ii = SystemCoreClock;		//read the system clock
}


void ADC_conf(void)	{
	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div2);		//configure ADC clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);		//enable ADC1 clock

				//przerwanie co 1 us
	if(SysTick_Config(SystemCoreClock / 1000000))	{
		//error
		while(1)	{
			//petla pusta
		}
	}

	GPIO_conf();		//ADC pins

	ADC_StructInit(&ADC_InitStruct);

	//procedura kalibracji
	ADC_VoltageRegulatorCmd(ADC1, ENABLE);
	_delay_ms(10);

	ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC1);

	while (ADC_GetCalibrationStatus(ADC1) != RESET)	;

	calibration_value = ADC_GetCalibrationStatus(ADC1);

//=-=-=-=-= ADC_CommonInitStructure -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	ADC_CommonInitStructure.ADC_Mode = ADC_IndependentMode;	//tryb independent
	ADC_CommonInitStructure.ADC_Clock = ADC_AsynClkMode;//clock asynchroniczny
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;
	ADC_CommonInit(ADC1, &ADC_CommonInitStructure);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//=-=-=-=-=  ADC_InitStructure  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	 ADC_InitStruct.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	 ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	 ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConv_Event0;
	 ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigConvEdge_None;
	 ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	 ADC_InitStruct.ADC_OverunMode = ADC_OverunMode_Disable;
	 ADC_InitStruct.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	 ADC_InitStruct.ADC_NbrOfRegChannel = 1;
	 ADC_Init(ADC1, &ADC_InitStruct);
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


	 ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_7Cycles5); //ADC1 regulator channel7 config

	 ADC_Cmd(ADC1, ENABLE);	//enable ADC1

	 while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY));		//wait for ADRDY

	 ADC_StartConversion(ADC1);			//start konwersji

}

void GPIO_conf(void)	{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;		//analog mode
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	//bez podciagania

	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void LED_init(void)	{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);		//GPIO Periph clock enable
															//config zegara od portu E

		GPIO_InitStruct.GPIO_Pin = L3 | L4 | L5 | L6 | L7 | L8 | L9 | L10;	//piny
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;				//OUT
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;				//push-pull
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;			//f 50Mhz
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			//bez podciagania
		GPIO_Init(LED_PORT, &GPIO_InitStruct);					//wywołanie GPIOE
}

