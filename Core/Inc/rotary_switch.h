/**
 * @file    rotary_switch.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ROTARY_SWITCH_H_
#define _ROTARY_SWITCH_H_

/* ---------- Includes -------------------------------------------------------*/
#include "main.h"
#include "IIR_filter.h"

/* ---------- Exported types -------------------------------------------------*/
typedef struct {
    GPIO_TypeDef *gpiox[4];
    uint16_t pin[4];
    uint8_t state[4];
    IIR_filter filter[4];
    uint8_t position;
} RSW_t;


typedef struct {
    RSW_t power;
    RSW_t control;
    RSW_t user;
} rswStateHandleTypedef;

/* ---------- Exported constants ---------------------------------------------*/


/* ---------- Exported variables ---------------------------------------------*/


/* ---------- Exported macros ------------------------------------------------*/


/* ---------- Exported functions ---------------------------------------------*/
void RSW_Init(rswStateHandleTypedef *hrsw);
void RSW_sample_one(RSW_t *rsw);
void RSW_sample(rswStateHandleTypedef *hrsw);

/* ---------- Private types --------------------------------------------------*/


/* ---------- Private variables ----------------------------------------------*/


/* ---------- Private constants ----------------------------------------------*/


/* ---------- Private Macros -------------------------------------------------*/


#endif