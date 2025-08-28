/**
 * @file    rotary_switch.c
 * @author  Pietro Levo [pietro.levo.sc@gmail.com]
 * @date    2025-08-28 (date of creation)
 * @updated 2025-08-28 (date of last update)
 * @version v1.0.0
 * @prefix  RSW
 *
 * @brief   Implementation of some software
 * @details This code implements functions for the 3 rotary switch on the steering
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes --------------------------------------------------------*/

#include "rotary_switch.h"

/*---------- Private define --------------------------------------------------*/


/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/


/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/
RSW_t rsw_PW;
RSW_t rsw_CT;
RSW_t rsw_USER;

/*---------- Exported Functions ----------------------------------------------*/
void RSW_init_all(void) {
  GPIO_TypeDef *rsw_PW_port[4] = {RSW1_C1_GPIO_Port, RSW1_C2_GPIO_Port, RSW1_C4_GPIO_Port, RSW1_C8_GPIO_Port};
  uint16_t rsw_PW_pin[4] = {RSW1_C1_Pin, RSW1_C2_Pin, RSW1_C4_Pin, RSW1_C8_Pin};

  GPIO_TypeDef *rsw_CT_port[4] = {RSW2_C1_GPIO_Port, RSW2_C2_GPIO_Port, RSW2_C4_GPIO_Port, RSW2_C8_GPIO_Port};
  uint16_t rsw_CT_pin[4] = {RSW2_C1_Pin, RSW2_C2_Pin, RSW2_C4_Pin, RSW2_C8_Pin};

  GPIO_TypeDef *rsw_USER_port[4] = {RSW3_C1_GPIO_Port, RSW3_C2_GPIO_Port, RSW3_C4_GPIO_Port, RSW3_C8_GPIO_Port};
  uint16_t rsw_USER_pin[4] = {RSW3_C1_Pin, RSW3_C2_Pin, RSW3_C4_Pin, RSW3_C8_Pin};

  for (uint8_t i = 0; i < 4; i++) {
    rsw_PW.gpiox[i] = rsw_PW_port[i];
    rsw_PW.pin[i]   = rsw_PW_pin[i];

    rsw_CT.gpiox[i] = rsw_CT_port[i];
    rsw_CT.pin[i]   = rsw_CT_pin[i];

    rsw_USER.gpiox[i] = rsw_USER_port[i];
    rsw_USER.pin[i]   = rsw_USER_pin[i];
  }
}


uint8_t RSW_read(RSW_t *rsw) {
  rsw->position = 0;
  rsw->position |= (HAL_GPIO_ReadPin(rsw->gpiox[0], rsw->pin[0]) == GPIO_PIN_SET ? 1 : 0) << 0;
  rsw->position |= (HAL_GPIO_ReadPin(rsw->gpiox[1], rsw->pin[1]) == GPIO_PIN_SET ? 1 : 0) << 1;
  rsw->position |= (HAL_GPIO_ReadPin(rsw->gpiox[2], rsw->pin[2]) == GPIO_PIN_SET ? 1 : 0) << 2;
  rsw->position |= (HAL_GPIO_ReadPin(rsw->gpiox[3], rsw->pin[3]) == GPIO_PIN_SET ? 1 : 0) << 3;

  return rsw->position;
}


RSW_State_t RSW_read_all(void) {
  RSW_State_t state;
  state.pw   = RSW_read(&rsw_PW);
  state.ct   = RSW_read(&rsw_CT);
  state.user = RSW_read(&rsw_USER);
  return state;
}

/*---------- Private Functions -----------------------------------------------*/

