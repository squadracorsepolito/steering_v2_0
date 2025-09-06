/**
 * @file    bsp.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BSP_H_
#define _BSP_H_

/* ---------- Includes -------------------------------------------------------*/
#include "gpio.h"
#include "IIR_filter.h"

/* ---------- Exported types -------------------------------------------------*/
struct GPIO_Tuple {
    GPIO_TypeDef *GPIO_Port;
    uint16_t GPIO_Pin;
};


struct GPIO_Quad {
    struct GPIO_Tuple Pins[4];
};


// Buttons
enum BTN_Device {
    BTN_1,
    BTN_2,
    BTN_3,
    BTN_4,
    BTN_5,
    BTN_Device_NUM
};


enum BTN_State {
    BTN_state_OFF,
    BTN_state_ON
};


typedef struct {
    enum BTN_Device id;
    struct GPIO_Tuple gpio_tuple;
    uint8_t value;
    uint8_t prev_value;
    enum BTN_State state;
    IIR_filter filter;
} BTN_handleTypedef;


// Rotary DIP Switches
enum RSW_Device {
    RSW_Device1,
    RSW_Device2,
    RSW_Device3,
    RSW_Device_NUM
};


typedef struct {
    enum RSW_Device id;
    struct GPIO_Quad gpio_quad;
    uint8_t value[4];
//  enum RSW_State state;
    uint8_t state;
    IIR_filter filters[4];
} RSW_handleTypedef;


/* ---------- Exported constants ---------------------------------------------*/


/* ---------- Exported variables ---------------------------------------------*/


/* ---------- Exported macros ------------------------------------------------*/


/* ---------- Exported functions ---------------------------------------------*/
GPIO_PinState Read_Pin(struct GPIO_Tuple gpio);

void BTN_Devices_Init(BTN_handleTypedef *hbtn, float btn_IIR_alpha);
void BTN_Device_Sample(BTN_handleTypedef *hbtn);
void BTN_Device_SampleALL(BTN_handleTypedef *hbtn);
enum BTN_State BTN_Device_GetState(BTN_handleTypedef *hbtn);


void RSW_Devices_Init(RSW_handleTypedef *hrsw, float rsw_IIR_alpha);
void RSW_Device_Sample(RSW_handleTypedef *hrsw);
void RSW_Device_SampleALL(RSW_handleTypedef *hrsw);
uint8_t RSW_Device_GetState(RSW_handleTypedef *hrsw);


/* ---------- Private types --------------------------------------------------*/


/* ---------- Private variables ----------------------------------------------*/


/* ---------- Private constants ----------------------------------------------*/


/* ---------- Private Macros -------------------------------------------------*/


#endif