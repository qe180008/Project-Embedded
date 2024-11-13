/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <string.h>
/*  SDK Included Files */
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"

#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* I2C source clock */
#define I2C_MASTER_CLK_SRC I2C0_CLK_SRC
#define I2C_MASTER_CLK_FREQ CLOCK_GetFreq(I2C0_CLK_SRC)
#define EXAMPLE_I2C_MASTER_BASEADDR I2C0

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x68U
#define I2C_BAUDRATE 100000U
#define I2C_DATA_LENGTH 7U

#define SYST_CSR *((uint32_t*)0xE000E010)
#define SYST_RVR *((uint32_t*)0xE000E014)
#define SYST_CVR *((uint32_t*)0xE000E018)

uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];
volatile bool g_MasterCompletionFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay1ms(void)
{
	SYST_CSR = 0; /* Reset and disable */
	SYST_RVR = 71999; /* Value to count */
	SYST_CSR = 5; /* Select source clock, Enable */
	while((SYST_CSR & 0x10000) != 0x10000); /* Wait flag */
	SYST_CSR = 0; /* Reset and disable */
}

void delayms(uint32_t n)
{
	uint32_t i;

	for(i = 0; i < n; i++)
	{
		delay1ms();
	}
}

/*!
 * @brief Main function
 */
int main(void)
{
    i2c_master_config_t masterConfig;
    uint32_t sourceClock;
    i2c_master_transfer_t masterXfer;
    uint8_t deviceAddress;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Set up buffer for master and slave */
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH; i++)
    {
        g_master_txBuff[i] = 0;
    }

    /*
     * masterConfig->baudRate_Bps = 100000U;
     * masterConfig->enableStopHold = false;
     * masterConfig->glitchFilterWidth = 0U;
     * masterConfig->enableMaster = true;
     */
    I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = I2C_BAUDRATE;

    sourceClock = I2C_MASTER_CLK_FREQ;

    I2C_MasterInit(EXAMPLE_I2C_MASTER_BASEADDR, &masterConfig, sourceClock);

    memset(&masterXfer, 0, sizeof(masterXfer));

#if 1
    g_master_rxBuff[0] = 0; /* Giay */
    g_master_rxBuff[1] = 0x29; /* Phut */
    g_master_rxBuff[2] = 0x13; /* Gio */
    g_master_rxBuff[3] = 5; /* Thu */
    g_master_rxBuff[4] = 3; /* Ngay */
    g_master_rxBuff[5] = 0x10; /* Thang */
    g_master_rxBuff[6] = 0x30; /* Nam */
    /* subAddress = 0x01, data = g_master_txBuff - write to slave.
	  start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
	deviceAddress = 0x00U;
	masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR_7BIT;
	masterXfer.direction = kI2C_Write;
	masterXfer.subaddress = (uint32_t)deviceAddress;
	masterXfer.subaddressSize = 1;
	masterXfer.data = g_master_rxBuff;
	masterXfer.dataSize = 7;h
	masterXfer.flags = kI2C_TransferDefaultFlag;

	I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &masterXfer);
#endif

    while(1)
    {
		/* subAddress = 0x01, data = g_master_rxBuff - read from slave.
		  start + slaveaddress(w) + subAddress + repeated start + slaveaddress(r) + rx data buffer + stop */
    	deviceAddress = 0x00U;
		masterXfer.slaveAddress = I2C_MASTER_SLAVE_ADDR_7BIT;
		masterXfer.direction = kI2C_Read;
		masterXfer.subaddress = (uint32_t)deviceAddress;
		masterXfer.subaddressSize = 1;
		masterXfer.data = g_master_rxBuff;
		masterXfer.dataSize = I2C_DATA_LENGTH;
		masterXfer.flags = kI2C_TransferDefaultFlag;

		I2C_MasterTransferBlocking(EXAMPLE_I2C_MASTER_BASEADDR, &masterXfer);

		PRINTF("\r\nTime:\r\n");
		PRINTF("%x:", g_master_rxBuff[2]); /* In ra gio */
		PRINTF("%x:", g_master_rxBuff[1]); /* In ra phut */
		PRINTF("%x - ", g_master_rxBuff[0]); /* In ra giay */

		PRINTF("%x-", g_master_rxBuff[4]); /* In ra ngay */
		PRINTF("%x-", g_master_rxBuff[5]); /* In ra thang */
		PRINTF("20%x", g_master_rxBuff[6]); /* In ra nam */
		delayms(1000);
    }
}
