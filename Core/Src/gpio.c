/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "buttons.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin) {
  /*char debug[32];
  sprintf(debug, "CALLBACK\r\n");
  HAL_UART_Transmit(&huart1, (uint8_t*)debug, strlen(debug), HAL_MAX_DELAY);*/

  switch (GPIO_pin) {
  case BTN_TC_Pin:
    BTN_press(BTN_TC_GPIO_Port, BTN_TC_Pin, 0);
    break;
  case BTN_TV_Pin:
    BTN_press(BTN_TV_GPIO_Port, BTN_TV_Pin, 1);
    break;
  case BTN_LC_Pin:
    BTN_press(BTN_LC_GPIO_Port, BTN_LC_Pin, 2);
    break;
  case BTN_RTD_Pin:
    BTN_press(BTN_RTD_GPIO_Port, BTN_RTD_Pin, 3);
    break; 
  case BTN_USER_Pin:
    BTN_press(BTN_USER_GPIO_Port, BTN_USER_Pin, 4);
    break;
  default:
    BTN_recovery();
    break;
  }
}
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : BTN_TC_Pin BTN_TV_Pin BTN_LC_Pin BTN_RTD_Pin
                           BTN_USER_Pin */
  GPIO_InitStruct.Pin = BTN_TC_Pin|BTN_TV_Pin|BTN_LC_Pin|BTN_RTD_Pin
                          |BTN_USER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RSW1_C1_Pin RSW1_C2_Pin RSW1_C4_Pin RSW3_C1_Pin
                           RSW3_C2_Pin RSW3_C4_Pin RSW3_C8_Pin RSW1_C8_Pin
                           RSW2_C1_Pin RSW2_C2_Pin RSW2_C4_Pin RSW2_C8_Pin */
  GPIO_InitStruct.Pin = RSW1_C1_Pin|RSW1_C2_Pin|RSW1_C4_Pin|RSW3_C1_Pin
                          |RSW3_C2_Pin|RSW3_C4_Pin|RSW3_C8_Pin|RSW1_C8_Pin
                          |RSW2_C1_Pin|RSW2_C2_Pin|RSW2_C4_Pin|RSW2_C8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
