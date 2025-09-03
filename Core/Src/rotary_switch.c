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
#define RSW_ALPHA_IIR 0.66f
#define RSW_THRESHOLD_HIGH 0.7f
#define RSW_THRESHOLD_LOW  0.3f

/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/


/*---------- Private function prototypes -------------------------------------*/
static void RSW_read(RSW_t *rsw);

/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/
void RSW_Init(rswStateHandleTypedef *hrsw) {
    hrsw->power.gpiox[0] = RSW1_C1_GPIO_Port; hrsw->power.gpiox[1] = RSW1_C2_GPIO_Port;
    hrsw->power.gpiox[2] = RSW1_C4_GPIO_Port; hrsw->power.gpiox[3] = RSW1_C8_GPIO_Port;

    hrsw->control.gpiox[0] = RSW2_C1_GPIO_Port; hrsw->control.gpiox[1] = RSW2_C2_GPIO_Port;
    hrsw->control.gpiox[2] = RSW2_C4_GPIO_Port; hrsw->control.gpiox[3] = RSW2_C8_GPIO_Port;

    hrsw->user.gpiox[0] = RSW3_C1_GPIO_Port; hrsw->user.gpiox[1] = RSW3_C2_GPIO_Port;
    hrsw->user.gpiox[2] = RSW3_C4_GPIO_Port; hrsw->user.gpiox[3] = RSW3_C8_GPIO_Port;

    hrsw->power.pin[0] = RSW1_C1_Pin; hrsw->power.pin[1] = RSW1_C2_Pin;
    hrsw->power.pin[2] = RSW1_C4_Pin; hrsw->power.pin[3] = RSW1_C8_Pin;

    hrsw->control.pin[0] = RSW2_C1_Pin; hrsw->control.pin[1] = RSW2_C2_Pin;
    hrsw->control.pin[2] = RSW2_C4_Pin; hrsw->control.pin[3] = RSW2_C8_Pin;

    hrsw->user.pin[0] = RSW3_C1_Pin; hrsw->user.pin[1] = RSW3_C2_Pin;
    hrsw->user.pin[2] = RSW3_C4_Pin; hrsw->user.pin[3] = RSW3_C8_Pin;


    for (uint8_t i = 0; i < 4; i++) {
        hrsw->power.state[i] = 0; hrsw->control.state[i] = 0; hrsw->user.state[i] = 0;

        IIR_Init(&hrsw->power.filter[i], RSW_ALPHA_IIR);
        IIR_Init(&hrsw->control.filter[i], RSW_ALPHA_IIR);
        IIR_Init(&hrsw->user.filter[i], RSW_ALPHA_IIR);
    }

    hrsw->power.position = 0;
    hrsw->control.position = 0;
    hrsw->user.position = 0;
}


void RSW_sample_one(RSW_t *rsw) {
    GPIO_PinState raw[4] = {
        HAL_GPIO_ReadPin(rsw->gpiox[0], rsw->pin[0]),
        HAL_GPIO_ReadPin(rsw->gpiox[1], rsw->pin[1]),
        HAL_GPIO_ReadPin(rsw->gpiox[2], rsw->pin[2]),
        HAL_GPIO_ReadPin(rsw->gpiox[3], rsw->pin[3])
    };

    for (uint8_t i = 0; i < 4; i++) {
        float input = (raw[i] == GPIO_PIN_SET) ? 1.0f : 0.0f;
        float filtered = IIR_Update(&rsw->filter[i], input);

        if (filtered > RSW_THRESHOLD_HIGH) {
            rsw->state[i] = 1;
        } else if (filtered < RSW_THRESHOLD_LOW) {
            rsw->state[i] = 0;
        }
    }
}


void RSW_sample(rswStateHandleTypedef *hrsw) {
    RSW_sample_one(&hrsw->power);
    RSW_sample_one(&hrsw->control);
    RSW_sample_one(&hrsw->user);

    RSW_read(&hrsw->power);
    RSW_read(&hrsw->control); 
    RSW_read(&hrsw->user);
}

/*---------- Private Functions -----------------------------------------------*/
static void RSW_read(RSW_t *rsw) {
    rsw->position = 0;
    rsw->position |= (rsw->state[0] & 0x01) << 0;
    rsw->position |= (rsw->state[1] & 0x01) << 1;
    rsw->position |= (rsw->state[2] & 0x01) << 2;
    rsw->position |= (rsw->state[3] & 0x01) << 3;
}

