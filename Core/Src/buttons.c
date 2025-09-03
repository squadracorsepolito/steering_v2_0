/**
 * @file    buttons.c
 * @author  Pietro Levo [pietro.levo.sc@gmail.com]
 * @date    2025-08-28 (date of creation)
 * @updated 2025-09-04 (date of last update)
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

/*---------- Private define --------------------------------------------------*/
#define BTN_N 5
#define BTN_ALPHA_IIR 0.66f
#define BTN_THRESHOLD_HIGH 0.7f
#define BTN_THRESHOLD_LOW  0.3f

/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/


/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/
void BTN_Init(btnStateHandleTypedef *hbtn) {
    for (uint8_t i = 0; i < BTN_N; i++) {
        hbtn->state[i] = 0;
        hbtn->prev_state[i] = 0;
        hbtn->active[i] = 0;
        IIR_Init(&hbtn->filter[i], BTN_ALPHA_IIR);
    }
}


void BTN_Sample(btnStateHandleTypedef *hbtn) {
        GPIO_PinState raw[5] = {
        HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin),
        HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin),
        HAL_GPIO_ReadPin(BTN_3_GPIO_Port, BTN_3_Pin),
        HAL_GPIO_ReadPin(BTN_4_GPIO_Port, BTN_4_Pin),
        HAL_GPIO_ReadPin(BTN_5_GPIO_Port, BTN_5_Pin)
    };

    for (uint8_t i = 0; i < BTN_N; i++) {
        float input = (raw[i] == GPIO_PIN_RESET) ? 1.0f : 0.0f;
        float filtered = IIR_Update(&hbtn->filter[i], input);

        if (filtered > BTN_THRESHOLD_HIGH) {
            hbtn->state[i] = 1;
        } else if (filtered < BTN_THRESHOLD_LOW) {
            hbtn->state[i] = 0;
        }

        if (hbtn->prev_state[i] == 1 && hbtn->state[i] == 0) {
            hbtn->active[i] ^= 1;
        }

        hbtn->prev_state[i] = hbtn->state[i];
    }
}

/*---------- Private Functions -----------------------------------------------*/

