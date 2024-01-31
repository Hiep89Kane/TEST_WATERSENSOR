#include "myHeader.h"

/*FUNCTIONS COMMON */
void LED1_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		LED1_ON;
	else
		LED1_OFF;
}

void LED2_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		LED2_ON;
	else
		LED2_OFF;
}

void BUZ_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
	  FAN_ON;
	else
	  FAN_OFF;
}
void AF_RLCOM_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		RL_COM_ON;
	else
		RL_COM_OFF;
}

void AF_SEN5V_BaseCtrl(uint8_t OFF_ON)
{
	if (OFF_ON)
		SS_5V_CTRL_OFF;
	else
		SS_5V_CTRL_ON;
}

void RLSOL_BaseCtrl(uint8_t ON_OFF)
{
    if (ON_OFF)
      RL_SOL_COM_ON;
    else
      RL_SOL_COM_OFF;
}

void AF_SOL_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		FET_SOL_AF_ON;
	else
		FET_SOL_AF_OFF;
}

void AF_WHIRL_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		RL_WHIRL_On;
	else
		RL_WHIRL_Off;
}

void AF_DRAIN_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		RL_DRAIN_On;
	else
		RL_DRAIN_Off;
}

void ST_RLOldSS_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		RL_SS_STEAM_ON;
	else
		RL_SS_STEAM_OFF;
}

void ST_SOL_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		FET_SOL_STEAM_ON;
	else
		FET_SOL_STEAM_OFF;
}

void ST_AIRPUMP_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		RL_AIR_ON;
	else
		RL_AIR_OFF;
}

void ST_RL100_BaseCtrl(uint8_t ON_OFF)
{
	if (ON_OFF)
		RL_STEAM100_ON;
	else
		RL_STEAM100_OFF;
}

//Init Pheriperal of MCU
void init_MCU_UART(UART_HandleTypeDef *huart);
void init_MCU_PWM();
void init_MCU_ADC1_DMA();
void init_MCU_IO_Ctrl();
void init_MCU_TIM();
