/**
 * @file    bsp.c
 * @author  Pietro Levo [pietro.levo.sc@gmail.com]
 * @date    2025-09-05 (date of creation)
 * @updated 2025-09-05 (date of last update)
 * @version vX.X.X
 * @prefix  BSP
 *
 * @brief   Implementation of some software
 * @details This code implements bla bla
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes --------------------------------------------------------*/

#include "bsp.h"


/*---------- Private define --------------------------------------------------*/
#define BTN_THRESHOLD_HIGH 0.7f
#define BTN_THRESHOLD_LOW  0.3f

#define RSW_THRESHOLD_HIGH 0.7f
#define RSW_THRESHOLD_LOW  0.3f

/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/
static struct GPIO_Tuple BTN_Device_to_GPIO_Tuple_map[BTN_Device_NUM] = {
    [BTN_1] = {.GPIO_Port = BTN_1_GPIO_Port, .GPIO_Pin = BTN_1_Pin},
    [BTN_2] = {.GPIO_Port = BTN_2_GPIO_Port, .GPIO_Pin = BTN_2_Pin},
    [BTN_3] = {.GPIO_Port = BTN_3_GPIO_Port, .GPIO_Pin = BTN_3_Pin},
    [BTN_4] = {.GPIO_Port = BTN_4_GPIO_Port, .GPIO_Pin = BTN_4_Pin},
    [BTN_5] = {.GPIO_Port = BTN_5_GPIO_Port, .GPIO_Pin = BTN_5_Pin}
};


static struct GPIO_Quad RSW_Device_to_GPIO_Quad_map[RSW_Device_NUM] = {
    [RSW_Device1] = { 
        .Pins = {
            {.GPIO_Port = RSW1_C1_GPIO_Port, .GPIO_Pin = RSW1_C1_Pin},
            {.GPIO_Port = RSW1_C2_GPIO_Port, .GPIO_Pin = RSW1_C2_Pin},
            {.GPIO_Port = RSW1_C4_GPIO_Port, .GPIO_Pin = RSW1_C4_Pin},
            {.GPIO_Port = RSW1_C8_GPIO_Port, .GPIO_Pin = RSW1_C8_Pin} 
        }
    },
    [RSW_Device2] = { 
        .Pins = {
            {.GPIO_Port = RSW2_C1_GPIO_Port, .GPIO_Pin = RSW2_C1_Pin},
            {.GPIO_Port = RSW2_C2_GPIO_Port, .GPIO_Pin = RSW2_C2_Pin},
            {.GPIO_Port = RSW2_C4_GPIO_Port, .GPIO_Pin = RSW2_C4_Pin},
            {.GPIO_Port = RSW2_C8_GPIO_Port, .GPIO_Pin = RSW2_C8_Pin} 
        }
    },
    [RSW_Device3] = { 
        .Pins = {
            {.GPIO_Port = RSW3_C1_GPIO_Port, .GPIO_Pin = RSW3_C1_Pin},
            {.GPIO_Port = RSW3_C2_GPIO_Port, .GPIO_Pin = RSW3_C2_Pin},
            {.GPIO_Port = RSW3_C4_GPIO_Port, .GPIO_Pin = RSW3_C4_Pin},
            {.GPIO_Port = RSW3_C8_GPIO_Port, .GPIO_Pin = RSW3_C8_Pin} 
        }
    }
};


/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/
GPIO_PinState Read_Pin(struct GPIO_Tuple gpio) {
    return HAL_GPIO_ReadPin(gpio.GPIO_Port, gpio.GPIO_Pin);
}


/*########## BUTTONS #########################################################*/

void BTN_Devices_Init(BTN_handleTypedef *hbtn, float btn_IIR_alpha) {
    for (uint8_t i = 0; i < BTN_Device_NUM; i++) {
        hbtn[i].id = (enum BTN_Device) i;
        hbtn[i].gpio_tuple = BTN_Device_to_GPIO_Tuple_map[i];
        hbtn[i].value = 0;
        hbtn[i].prev_value = 0;
        hbtn[i].state = BTN_state_OFF;

        IIR_Init(&hbtn[i].filter, btn_IIR_alpha);
    }
}


void BTN_Device_Sample(BTN_handleTypedef *hbtn) {
    GPIO_PinState raw_value = Read_Pin(hbtn->gpio_tuple);

    float input = (raw_value == GPIO_PIN_RESET) ? 1.0f : 0.0f;
    float filtered = IIR_Update(&hbtn->filter, input);

    if (filtered > BTN_THRESHOLD_HIGH) {
        hbtn->value = 1;
    } else if (filtered < BTN_THRESHOLD_LOW) {
        hbtn->value = 0;
    }

    if (hbtn->prev_value == 1 && hbtn->value == 0) {
        hbtn->state = (hbtn->state == BTN_state_ON) ? BTN_state_OFF : BTN_state_ON;
    }

    hbtn->prev_value = hbtn->value;
}


void BTN_Device_SampleALL(BTN_handleTypedef *hbtn) {
    BTN_Device_Sample(&hbtn[0]);
    BTN_Device_Sample(&hbtn[1]);
    BTN_Device_Sample(&hbtn[2]);
    BTN_Device_Sample(&hbtn[3]);
    BTN_Device_Sample(&hbtn[4]);
}


enum BTN_State BTN_Device_GetState(BTN_handleTypedef *hbtn) {
    return hbtn->state;
}


/*########## ROTARY SWITCH ###################################################*/

void RSW_Devices_Init(RSW_handleTypedef *hrsw, float rsw_IIR_alpha) {
    for (uint8_t i = 0; i < RSW_Device_NUM; i++) {
        hrsw[i].id = (enum RSW_Device) i;
        hrsw[i].gpio_quad = RSW_Device_to_GPIO_Quad_map[i];
        hrsw[i].state = 0;

        for (int j = 0; j < 4; j++) {
            hrsw[i].value[j] = 0;
            IIR_Init(&hrsw[i].filters[j], rsw_IIR_alpha);
        }
    }
}


void RSW_Device_Sample(RSW_handleTypedef *hrsw) {
    GPIO_PinState raw_values[4] = {
        Read_Pin(hrsw->gpio_quad.Pins[0]),
        Read_Pin(hrsw->gpio_quad.Pins[1]),
        Read_Pin(hrsw->gpio_quad.Pins[2]),        
        Read_Pin(hrsw->gpio_quad.Pins[3])
    };

    for (uint8_t i = 0; i < 4; i++) {
        float input = (raw_values[i] == GPIO_PIN_SET) ? 1.0f : 0.0f;
        float filtered = IIR_Update(&hrsw->filters[i], input);

        if (filtered > RSW_THRESHOLD_HIGH) {
            hrsw->value[i] = 1;
        } else if (filtered < RSW_THRESHOLD_LOW) {
            hrsw->value[i] = 0;
        }
    }

    hrsw->state = 0;
    hrsw->state  |= (hrsw->value[0] & 0x01) << 0;
    hrsw->state  |= (hrsw->value[1] & 0x01) << 1;
    hrsw->state  |= (hrsw->value[2] & 0x01) << 2;
    hrsw->state  |= (hrsw->value[3] & 0x01) << 3;
}


void RSW_Device_SampleALL(RSW_handleTypedef *hrsw) {
    RSW_Device_Sample(&hrsw[0]);
    RSW_Device_Sample(&hrsw[1]);
    RSW_Device_Sample(&hrsw[2]);
}


uint8_t RSW_Device_GetState(RSW_handleTypedef *hrsw) {
    return hrsw->state;
}

/*---------- Private Functions -----------------------------------------------*/