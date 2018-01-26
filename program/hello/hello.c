//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************


#include "mpu6050.h"

#include<stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uartstdio.h"

#define MPU6050_SMPLRT_DIV                  0x19
#define MPU6050_INT_PIN_CFG                 0x37
#define MPU6050_ACCEL_XOUT_H                0x3B
#define MPU6050_GYRO_XOUT_H                 0x43
#define MPU6050_PWR_MGMT_1                  0x6B
#define MPU6050_WHO_AM_I                    0x75
 
#define MPU6050_ADDRESS                     0x68
#define MPU6050_WHO_AM_I_ID                 0x68
 
// Scale factor for +-2000deg/s and +-8g - see datasheet: 
#define MPU6050_GYRO_SCALE_FACTOR_2000      16.4f
#define MPU6050_ACC_SCALE_FACTOR_8          4096.0f
 int16_t  accaxisX;
 int16_t accaxisY;
 int16_t accaxisZ;
 
 float accaxisX_f;
  float accaxisY_f;
	 float accaxisZ_f;
	 
 int16_t gyroaxisX;
 int16_t gyroaxisY;
 int16_t gyroaxisZ;
 
  float gyroaxisX_f;
  float gyroaxisY_f;
	 float gyroaxisZ_f;
 char result[150];
int
main(void)
{


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 115200, 16000000);
   
initI2C();
SysCtlDelay(SysCtlClockGet()/10);
	initMPU6050();
	SysCtlDelay(SysCtlClockGet()/10);
    while(1)
    {
			uint8_t buf[14];
i2cReadData(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, buf, 14);
accaxisX = (buf[0] << 8) | buf[1];			
accaxisY = (buf[2] << 8) | buf[3];
accaxisZ = (buf[4] << 8) | buf[5];
accaxisX_f=accaxisX/MPU6050_ACC_SCALE_FACTOR_8;
accaxisY_f=accaxisY/MPU6050_ACC_SCALE_FACTOR_8;
accaxisZ_f=accaxisZ/MPU6050_ACC_SCALE_FACTOR_8;
						
gyroaxisX = (buf[8] << 8) | buf[9];
gyroaxisY = (buf[10] << 8) | buf[11];
gyroaxisZ = (buf[12] << 8) | buf[13];
gyroaxisX_f=gyroaxisX/MPU6050_GYRO_SCALE_FACTOR_2000;
gyroaxisY_f=gyroaxisY/MPU6050_GYRO_SCALE_FACTOR_2000;
gyroaxisZ_f=gyroaxisZ/MPU6050_GYRO_SCALE_FACTOR_2000;
       
		
			
    sprintf(result, "%d %d %d %d %d %d", accaxisX,accaxisY,accaxisZ,gyroaxisX,gyroaxisY,gyroaxisZ);
			
			UARTprintf(" %s\n",result);
		}
		
		
}
