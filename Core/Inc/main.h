/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define DEBUG 1
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_1_Pin GPIO_PIN_0
#define BTN_1_GPIO_Port GPIOA
#define BTN_2_Pin GPIO_PIN_1
#define BTN_2_GPIO_Port GPIOA
#define BTN_3_Pin GPIO_PIN_2
#define BTN_3_GPIO_Port GPIOA
#define BTN_4_Pin GPIO_PIN_3
#define BTN_4_GPIO_Port GPIOA
#define BTN_5_Pin GPIO_PIN_4
#define BTN_5_GPIO_Port GPIOA
#define RSW1_C1_Pin GPIO_PIN_0
#define RSW1_C1_GPIO_Port GPIOB
#define RSW1_C2_Pin GPIO_PIN_1
#define RSW1_C2_GPIO_Port GPIOB
#define RSW1_C4_Pin GPIO_PIN_2
#define RSW1_C4_GPIO_Port GPIOB
#define RSW3_C1_Pin GPIO_PIN_12
#define RSW3_C1_GPIO_Port GPIOB
#define RSW3_C2_Pin GPIO_PIN_13
#define RSW3_C2_GPIO_Port GPIOB
#define RSW3_C4_Pin GPIO_PIN_14
#define RSW3_C4_GPIO_Port GPIOB
#define RSW3_C8_Pin GPIO_PIN_15
#define RSW3_C8_GPIO_Port GPIOB
#define RSW1_C8_Pin GPIO_PIN_8
#define RSW1_C8_GPIO_Port GPIOA
#define RSW2_C1_Pin GPIO_PIN_4
#define RSW2_C1_GPIO_Port GPIOB
#define RSW2_C2_Pin GPIO_PIN_5
#define RSW2_C2_GPIO_Port GPIOB
#define RSW2_C4_Pin GPIO_PIN_6
#define RSW2_C4_GPIO_Port GPIOB
#define RSW2_C8_Pin GPIO_PIN_7
#define RSW2_C8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
