#ifndef SRC_INIT_INIT_MCU_H_
#define SRC_INIT_INIT_MCU_H_

/*//=========================================== BASE IO FUNCTIONS for OUTPUT CONTROL ===================================================*/
void LED1_BaseCtrl(uint8_t ON_OFF);
void LED2_BaseCtrl(uint8_t ON_OFF);
void LEDG_BaseCtrl(uint8_t ON_OFF);
void LEDB_BaseCtrl(uint8_t ON_OFF);
void BUZ_BaseCtrl(uint8_t ON_OFF);
// AutoFill IO
void AF_RLCOM_BaseCtrl(uint8_t ON_OFF);
void AF_SEN5V_BaseCtrl(uint8_t OFF_ON);
void RLSOL_BaseCtrl(uint8_t ON_OFF);
void AF_SOL_BaseCtrl(uint8_t ON_OFF);
void AF_WHIRL_BaseCtrl(uint8_t ON_OFF);
void AF_DRAIN_BaseCtrl(uint8_t ON_OFF);
// STEAMER IO
void ST_RLOldSS_BaseCtrl(uint8_t ON_OFF);
void ST_SOL_BaseCtrl(uint8_t ON_OFF);
void ST_AIRPUMP_BaseCtrl(uint8_t ON_OFF);
void ST_RL100_BaseCtrl(uint8_t ON_OFF);

//Init Pheriperal of MCU
void init_MCU_UART(UART_HandleTypeDef *huart);
void init_MCU_PWM();
void init_MCU_ADC1_DMA();
void init_MCU_IO_Ctrl();
void init_MCU_TIM();

#endif /* SRC_INIT_INIT_MCU_H_ */
