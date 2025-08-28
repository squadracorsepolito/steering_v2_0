/**
 * @file    buttons.c
 * @author  Pietro Levo [pietro.levo.sc@gmail.com]
 * @date    2025-08-28 (date of creation)
 * @updated 2025-08-28 (date of last update)
 * @version v1.0.0
 * @prefix  BTN
 *
 * @brief   Implementation of some software
 * @details This code implements functions for the 5 buttons in the steering
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes --------------------------------------------------------*/

#include "buttons.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

/*---------- Private define --------------------------------------------------*/


/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/
uint8_t BTN_state[BTN_NUM] = {0};
uint8_t BTN_prev_state[BTN_NUM] = {0};
uint32_t last_press_time[BTN_NUM] = {0};

/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/
void BTN_press(GPIO_TypeDef *gpiox, uint16_t GPIO_pin, uint8_t num) {
  GPIO_PinState pin_state = HAL_GPIO_ReadPin(gpiox, GPIO_pin);
  uint32_t now = uwTick;

  if (pin_state == GPIO_PIN_RESET && (now - last_press_time[num]) > BTN_DEBOUNCE) {
    BTN_prev_state[num] = BTN_state[num];
    BTN_state[num] ^= 1;
    last_press_time[num] = now;
  }

  char debug[32];
  sprintf(debug, "BTN %hu pressed\r\n", (num+1));
  HAL_UART_Transmit(&huart1, (uint8_t*)debug, strlen(debug), HAL_MAX_DELAY);
}


void BTN_recovery() {
  char debug[32];
  sprintf(debug, "RECOVERY\r\n");
  HAL_UART_Transmit(&huart1, (uint8_t*)debug, strlen(debug), HAL_MAX_DELAY);

  for (uint8_t i = 0; i < BTN_NUM; i++) {
    BTN_state[i] = BTN_prev_state[i];
  }
}

/*---------- Private Functions -----------------------------------------------*/

