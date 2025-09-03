/**
 * @file    steering.h
 * @author  Pietro Levo [pietro.levo.sc@gmail.com]
 * @date    2025-09-03 (date of creation)
 * @updated 2025-09-04 (date of last update)
 * @version v0.1.0
 * @prefix  STE
 *
 * @brief   Implementation of some software
 * @details This code implements bla bla
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _STEERING_H_
#define _STEERING_H_

/* ---------- Includes -------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "buttons.h"
#include "rotary_switch.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

/* ---------- Exported types -------------------------------------------------*/


/* ---------- Exported constants ---------------------------------------------*/


/* ---------- Exported variables ---------------------------------------------*/


/* ---------- Exported macros ------------------------------------------------*/


/* ---------- Exported functions ---------------------------------------------*/
void steering_run(btnStateHandleTypedef *hbtn, rswStateHandleTypedef *hrsw);

/* ---------- Private types --------------------------------------------------*/


/* ---------- Private variables ----------------------------------------------*/


/* ---------- Private constants ----------------------------------------------*/


/* ---------- Private Macros -------------------------------------------------*/


#endif