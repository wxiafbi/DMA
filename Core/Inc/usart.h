/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "dma.h"
#include <string.h>
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
//定义串口1操作变量
extern uint8_t aRxBuffer;
#define own 1  //串口1中断接收和DMA接收标志�?
#define DMA_RX_CNT 20
#define RXBUFFERSIZE 256

//定义串口1操作变量
#define USART3_RXBUFF_SIZE   1024              //定义串口3 接收缓冲区大�? 1024字节
extern char Usart3_Rx;            //定义�?个变�? 0：表示接收未完成 1：表示接收完�? 
extern unsigned int Usart3_RxCounter;      //定义�?个变量，记录串口3总共接收了多少字节的数据
extern char Usart3_RxBuff[USART3_RXBUFF_SIZE]; //定义�?个数组，用于保存串口3接收到的数据   	
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

