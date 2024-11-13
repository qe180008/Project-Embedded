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

#define DCPWM      85
#define RIGHTDC    kFTM_Chnl_0
#define LEFTDC     kFTM_Chnl_2

void delay1msPDB(void);
void delay1ms(void);
void delayms(uint32_t n);
void initGPIO(void);
void RmotorDCGoForward(void);
void RmotorDCGoBackward(void);
void RmotorDCStop(void);
void LmotorDCGoForward(void);
void LmotorDCGoBackward(void);
void LmotorDCStop(void);
void initPDB(void);
void initFTM(void);
uint8_t readSensor(void);
void runDirection(void);

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

/* Used to save old direction */
uint8_t oldDirection = 0;

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

void delayms(uint32_t n)
{
	uint32_t count;

	for (count = 0; count < n; count++)
	{
		delay1ms();
		/*delay1msPDB();*/
	}
}

void initGPIO(void)
{
	/* Init Pin to control motor DCR */
	GPIO_PinInit(GPIOA, 2, &pin_config_out);
	GPIO_PinInit(GPIOA, 3, &pin_config_out);
	/* Init Pin to control motor DCL */
	GPIO_PinInit(GPIOA, 6, &pin_config_out);
	GPIO_PinInit(GPIOA, 7, &pin_config_out);
	/* Init Pin to control LED */
	GPIO_PinInit(GPIOB, 4, &pin_config_out);
	GPIO_PinInit(GPIOB, 5, &pin_config_out);
	GPIO_PinInit(GPIOD, 1, &pin_config_out);
	/* Init Pin for sensor */
	GPIO_PinInit(GPIOE, 8, &pin_config_in); /* Sensor 5 */
	GPIO_PinInit(GPIOE, 0, &pin_config_in); /* Sensor 4 */
	GPIO_PinInit(GPIOE, 1, &pin_config_in); /* Sensor 3 */
	GPIO_PinInit(GPIOE, 2, &pin_config_in); /* Sensor 2 */
	GPIO_PinInit(GPIOD, 7, &pin_config_in); /* Sensor 1 */
	/* Init for check button */
	GPIO_PinInit(GPIOD, 2, &pin_config_in);
	GPIO_PinInit(GPIOD, 3, &pin_config_in);
	/* All LED will be turned off */
	GPIO_PinWrite(GPIOB, 4, 1);
	GPIO_PinWrite(GPIOB, 5, 1);
	GPIO_PinWrite(GPIOD, 1, 1);
}

void RmotorDCGoForward(void)
{
	GPIO_PinWrite(GPIOA, 2, 0);
	GPIO_PinWrite(GPIOA, 3, 1);
}

void RmotorDCGoBackward(void)
{
	GPIO_PinWrite(GPIOA, 2, 1);
	GPIO_PinWrite(GPIOA, 3, 0);
}

void RmotorDCStop(void)
{
	GPIO_PinWrite(GPIOA, 2, 0);
	GPIO_PinWrite(GPIOA, 3, 0);
}

void LmotorDCGoForward(void)
{
	GPIO_PinWrite(GPIOA, 6, 1);
	GPIO_PinWrite(GPIOA, 7, 0);
}

void LmotorDCGoBackward(void)
{
	GPIO_PinWrite(GPIOA, 6, 0);
	GPIO_PinWrite(GPIOA, 7, 1);
}

void LmotorDCStop(void)
{
	GPIO_PinWrite(GPIOA, 6, 0);
	GPIO_PinWrite(GPIOA, 7, 0);
}

void initPDB(void)
{
	pdb_config_t pdbConfigStruct;

	PDB_GetDefaultConfig(&pdbConfigStruct);
	PDB_Init(PDB0, &pdbConfigStruct);

	/* Configure the delay value */
	PDB_SetModulusValue(PDB0, 47999);
	PDB_SetCounterDelayValue(PDB0, 47999);
	PDB_DoLoadValues(PDB0);
}

void initFTM(void)
{
	ftm_config_t ftmInfo;
	ftm_chnl_pwm_signal_param_t ftmParamMotor[2];

	FTM_GetDefaultConfig(&ftmInfo);
	ftmInfo.prescale = FTM_CalculateCounterClkDiv(FTM0, 10000, 48000000);
	FTM_Init(FTM0, &ftmInfo);
	/* LDC motor Configure ftm params with frequency 10KHZ */
	ftmParamMotor[0].chnlNumber            = LEFTDC;
	ftmParamMotor[0].level                 = kFTM_HighTrue;
	ftmParamMotor[0].dutyCyclePercent      = DCPWM; /* DCPWM% */
	ftmParamMotor[0].firstEdgeDelayPercent = 0U;
	ftmParamMotor[0].enableComplementary   = false;
	ftmParamMotor[0].enableDeadtime        = false;
	/* RDC motor Configure ftm params with frequency 10KHZ */
	ftmParamMotor[1].chnlNumber            = RIGHTDC;
	ftmParamMotor[1].level                 = kFTM_HighTrue;
	ftmParamMotor[1].dutyCyclePercent      = DCPWM; /* DCPWM% */
	ftmParamMotor[1].firstEdgeDelayPercent = 0U;
	ftmParamMotor[1].enableComplementary   = false;
	ftmParamMotor[1].enableDeadtime        = false;
	if (kStatus_Success !=
		FTM_SetupPwm(FTM0, ftmParamMotor, 2U, kFTM_CenterAlignedPwm, 10000, 48000000))
	{
		while(1)
		{
			GPIO_PinWrite(GPIOB, 4, 1);
			GPIO_PinWrite(GPIOB, 5, 1);
			GPIO_PinWrite(GPIOD, 1, 1);
			delayms(1000);
			GPIO_PinWrite(GPIOB, 4, 1);
			GPIO_PinWrite(GPIOB, 5, 0);
			GPIO_PinWrite(GPIOD, 1, 1);
			delayms(1000);
		}
	}
}

uint8_t readSensor(void)
{
	uint8_t value = 0;

	value = GPIO_PinRead(GPIOE, 8) << 1;           /* Read sensor 5 */
	value = (value | GPIO_PinRead(GPIOE, 0)) << 1; /* Read sensor 4 */
	value = (value | GPIO_PinRead(GPIOE, 1)) << 1; /* Read sensor 3 */
	value = (value | GPIO_PinRead(GPIOE, 2)) << 1; /* Read sensor 2 */
	value = value | GPIO_PinRead(GPIOD, 7);        /* Read sensor 1 */
	return (value & 0b00011111);                   /* Only keep 5 sensors */
}

void runDirection(void)
{
	uint8_t value;

	/* Read sensors */
	value = readSensor();
	/* Check with old direction */
	if (value != oldDirection)
	{
		/* Save direction value */
		oldDirection = value;
		switch(value)
		{
			case 0b00011111:
				RmotorDCStop(); /* Stop 2 motors */
				LmotorDCStop();
				delayms(50);
				LmotorDCGoBackward();
				RmotorDCGoForward();
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM);
				FTM_SetSoftwareTrigger(FTM0, true);

				do
				{
					value = readSensor();
				}while(value == 0b00011111);
				RmotorDCStop(); /* Stop 2 motors */
				LmotorDCStop();
				delayms(50);
				LmotorDCGoForward();
				RmotorDCGoForward();
				break;

			case 0b00011110: /* Lech phai 1 */
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM - DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM);
				break;
			case 0b00011100: /* Lech phai 2 */
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM - DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM);
				break;
			case 0b00011001: /* Lech phai 3 */
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM - DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM);
				break;

			case 0b00011011: /* Ko lech */
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM);
				break;

			case 0b00010011: /* Lech trai 1 */
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM - DCPWM);
				break;
			case 0b00000111: /* Lech trai 2 */
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM - DCPWM);
				break;
			case 0b00001111: /* Lech trai 3 */
				FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM);
				FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM - DCPWM);
				break;
		}
		FTM_SetSoftwareTrigger(FTM0, true);
	}
}

int main(void)
{

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    /* Init GPIO */
    initGPIO();
    /* Stop DC Motor */
    LmotorDCStop();
    RmotorDCStop();

    /* Init PDB */
    /*initPDB();*/

    /* Check button */
	while ((GPIO_PinRead(GPIOD, 2) != 0) && (GPIO_PinRead(GPIOD, 3) != 0));
	delayms(500);
	GPIO_PinWrite(GPIOB, 4, 0);
	GPIO_PinWrite(GPIOB, 5, 1);
	GPIO_PinWrite(GPIOD, 1, 1);
	delayms(500);
	GPIO_PinWrite(GPIOB, 4, 1);
	GPIO_PinWrite(GPIOB, 5, 0);
	GPIO_PinWrite(GPIOD, 1, 1);
	delayms(500);
	GPIO_PinWrite(GPIOB, 4, 1);
	GPIO_PinWrite(GPIOB, 5, 1);
	GPIO_PinWrite(GPIOD, 1, 0);

    /* Init FTM */
    initFTM();

	FTM_StartTimer(FTM0, kFTM_SystemClock);
	FTM_UpdatePwmDutycycle(FTM0, RIGHTDC, kFTM_CenterAlignedPwm, DCPWM);
	FTM_UpdatePwmDutycycle(FTM0, LEFTDC, kFTM_CenterAlignedPwm, DCPWM);
	FTM_SetSoftwareTrigger(FTM0, true);
	/* DC motor run forward */
	RmotorDCGoForward();
	LmotorDCGoForward();

	while(1)
	{
		runDirection();
	}

    return 0 ;
}
