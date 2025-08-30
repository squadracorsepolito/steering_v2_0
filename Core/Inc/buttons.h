/**
 * @file    buttons.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BUTTONS_H_
#define _BUTTONS_H_

/* ---------- Includes -------------------------------------------------------*/
#include "main.h"

/* ---------- Exported types -------------------------------------------------*/


/* ---------- Exported constants ---------------------------------------------*/
#define BTN_NUM 5
#define BTN_DEBOUNCE 10

/* ---------- Exported variables ---------------------------------------------*/
extern volatile uint8_t BTN_state[BTN_NUM];
extern volatile uint8_t BTN_prev_state[BTN_NUM];
extern volatile uint32_t last_press_time[BTN_NUM]; 

/* ---------- Exported macros ------------------------------------------------*/


/* ---------- Exported functions ---------------------------------------------*/
void BTN_init(void);
void BTN_press(GPIO_TypeDef *gpiox, uint16_t GPIO_pin, uint8_t num);
void BTN_recovery();

/* ---------- Private types --------------------------------------------------*/


/* ---------- Private variables ----------------------------------------------*/


/* ---------- Private constants ----------------------------------------------*/


/* ---------- Private Macros -------------------------------------------------*/


#endif