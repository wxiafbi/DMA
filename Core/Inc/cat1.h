/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma.h
  * @brief   This file contains all the function prototypes for
  *          the dma.c file
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
#ifndef __cat1_H__
#define __cat1_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* DMA memory to memory transfer handles -------------------------------------*/

/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define CAT1_printf       u3_printf           
#define CAT1_RxCounter    Usart3_RxCounter    
#define CAT1_RX_BUF       Usart3_RxBuff       
#define CAT1_RXBUFF_SIZE  USART3_RXBUFF_SIZE 

/* USER CODE END Private defines */



/* USER CODE BEGIN Prototypes */

char CAT1_Reset(int timeout);
char CAT1_ExitTrans(int);
char CAT1_SendCmd(char *, int);
char CAT1_CSQ(int);
char CAT1_SYSINFO(int);

char CAT1_Connect_IoTServer(int);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DMA_H__ */

