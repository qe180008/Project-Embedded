/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MKE16Z4_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE16Z4.h"
#include "fsl_debug_console.h"
#include "fsl_pdb.h"
#include "fsl_ftm.h"

#define SYST_CSR *((uint32_t*)0xE000E010)
#define SYST_RVR *((uint32_t*)0xE000E014)
#define SYST_CVR *((uint32_t*)0xE000E018)

void delay1msPDB(void);
void delay1ms(void);
void delay1s(void);

/* Define the init structure for the output pin*/
gpio_pin_config_t pin_config_out = {
	kGPIO_DigitalOutput,
	0,
};

/* Define the init structure for the input pin*/
gpio_pin_config_t pin_config_in = {
	kGPIO_DigitalInput,
	1,
};
 uint8_t olddirection = 0;

void delay1msPDB(void)
{
	uint32_t flags;

	PDB_DoSoftwareTrigger(PDB0);
	do
	{
	    flags = PDB_GetStatusFlags(PDB0);
	}while(flags == 0);
	PDB_ClearStatusFlags(PDB0, kPDB_DelayEventFlag);
}

void delay1ms(void)
{
	SYST_CSR = 0; /* Reset and disable */
	SYST_RVR = 47999; /* Value to count */
	SYST_CSR = 5; /* Select source clock, Enable */
	while((SYST_CSR & 0x10000) != 0x10000); /* Wait flag */
	SYST_CSR = 0; /* Reset and disable */
}

void delay1s(void)
{
	uint32_t count;

	for (count = 0; count < 1000; count++)
	{
		/*delay1ms();*/
		delay1msPDB();
	}
}

void initGPIO(void) {
	/* Init Pin to control motor +DC */
	GPIO_PinInit(GPIOA, 2, &pin_config_out);
	GPIO_PinInit(GPIOA, 3, &pin_config_out);
	/* Init Pin to control LED */
	GPIO_PinInit(GPIOB, 4, &pin_config_out);
	GPIO_PinInit(GPIOB, 5, &pin_config_out);
	GPIO_PinInit(GPIOD, 1, &pin_config_out);

	/* All LED will be turned off */
	GPIO_PinWrite(GPIOB, 4, 1);
	GPIO_PinWrite(GPIOB, 5, 1);
	GPIO_PinWrite(GPIOD, 1, 1);
}

void motorDCGoForward(void) {
	GPIO_PinWrite(GPIOA, 2, 0);
	GPIO_PinWrite(GPIOA, 3, 1);
}

void motorDCGoBackward(void) {
	GPIO_PinWrite(GPIOA, 2, 1);
	GPIO_PinWrite(GPIOA, 3, 0);
}

void motorDCStop(void) {
	GPIO_PinWrite(GPIOA, 2, 0);
	GPIO_PinWrite(GPIOA, 3, 0);
}

void initPDB(void) {
	pdb_config_t pdbConfigStruct;

	PDB_GetDefaultConfig(&pdbConfigStruct);
	PDB_Init(PDB0, &pdbConfigStruct);

	/* Configure the delay value */
	PDB_SetModulusValue(PDB0, 47999);
	PDB_SetCounterDelayValue(PDB0, 47999);
	PDB_DoLoadValues(PDB0);
}

void initFTM(void) {
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParamMotor[2];

	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = FTM_CalculateCounterClkDiv(FTM0, 50, 48000000);
	FTM_Init(FTM0, &ftmInfo);
	/* DC motor Configure ftm params with frequency 50HZ */
	ftmParamMotor[0].chnlNumber            = kFTM_Chnl_2;
	ftmParamMotor[0].level                 = kFTM_HighTrue;
	ftmParamMotor[0].dutyCyclePercent      = 12; /* 50% */
	ftmParamMotor[0].firstEdgeDelayPercent = 0U;
	ftmParamMotor[0].enableComplementary   = false;
	ftmParamMotor[0].enableDeadtime        = false;
	/* Servo motor Configure ftm params with frequency 50HZ */
	ftmParamMotor[1].chnlNumber            = kFTM_Chnl_0;
	ftmParamMotor[1].level                 = kFTM_HighTrue;
	ftmParamMotor[1].dutyCyclePercent      = 5; /* 5% */
	ftmParamMotor[1].firstEdgeDelayPercent = 0U;
	ftmParamMotor[1].enableComplementary   = false;
	ftmParamMotor[1].enableDeadtime        = false;
	if (kStatus_Success !=
		FTM_SetupPwm(FTM0, ftmParamMotor, 2U, kFTM_CenterAlignedPwm, 50, 48000000))
	{
		while(1)
		{
			GPIO_PinWrite(GPIOB, 4, 1);
			GPIO_PinWrite(GPIOB, 5, 1);
			GPIO_PinWrite(GPIOD, 1, 1);
			delay1s();
			GPIO_PinWrite(GPIOB, 4, 1);
			GPIO_PinWrite(GPIOB, 5, 0);
			GPIO_PinWrite(GPIOD, 1, 1);
			delay1s();
		}
	}
}

int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    /* Init GPIO */
    initGPIO();
    /* Stop DC Motor */
    motorDCStop();

    /* Init PDB */
    initPDB();

    /* Init FTM */
    initFTM();

	FTM_StartTimer(FTM0, kFTM_SystemClock);
	FTM_SetSoftwareTrigger(FTM0, true);


	/* DC motor run forward */
	motorDCGoForward();

	void runDirection(void){
		uint8_t value = 0;

		value = GPIO_PinRead(GPIOE,8 ) << 1;/*<<1 dich sang trai 1 bit*/
		value = (value | GPIO_PinRead(GPIOE, 0)) << 1;
		value = (value | GPIO_PinRead(GPIOE, 1)) << 1;
		value = (value | GPIO_PinRead(GPIOE, 2)) << 1;
		value = (value | GPIO_PinRead(GPIOD, 7)) << 1;

		if(value != oldDirection){
			value = oldDirection;
			switch(value)
			{
				case ob00011111: /*Stop DC motor*/
					motoDCstop();
				break;

				case ob00011011: /*khong lech*/
					FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0 , kFTM_CenterAlignedCombinedPwm, 7);
					FTM_SetSoftwareTrigger(FTM0, true);
				break;

				case ob00011001: /*lech phai 1*/
					FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0 , kFTM_CenterAlignedCombinedPwm, 6);
					FTM_SetSoftwareTrigger(FTM0, true);
				break;


				case ob00011001: /*lech phai 1*/
					FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0 , kFTM_CenterAlignedCombinedPwm, 6);
					FTM_SetSoftwareTrigger(FTM0, true);
				break;
			}

		}
	}
	while(1)
	{
		for (int i = 5; i <= 10; i++)
		{
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_CenterAlignedPwm, i);
			FTM_SetSoftwareTrigger(FTM0, true);
			delay1s();
		}
		for (int i = 10; i >= 5; i--)
		{
			FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_CenterAlignedPwm, i);
			FTM_SetSoftwareTrigger(FTM0, true);
			delay1s();
		}
	}

    return 0 ;
}
