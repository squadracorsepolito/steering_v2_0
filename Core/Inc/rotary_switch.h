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

/* ---------- Exported types -------------------------------------------------*/
typedef struct {
  GPIO_TypeDef *gpiox[4];
  uint16_t pin[4];
  uint8_t position;
} RSW_t;

typedef struct {
  uint8_t pw;
  uint8_t ct;
  uint8_t user;
} RSW_State_t;
/* ---------- Exported constants ---------------------------------------------*/


/* ---------- Exported variables ---------------------------------------------*/
extern RSW_t rsw_PW;
extern RSW_t rsw_CT;
extern RSW_t rsw_USER;

/* ---------- Exported macros ------------------------------------------------*/


/* ---------- Exported functions ---------------------------------------------*/
void RSW_init_all(void);
uint8_t RSW_read(RSW_t *rsw);
RSW_State_t RSW_read_all(void);

/* ---------- Private types --------------------------------------------------*/


/* ---------- Private variables ----------------------------------------------*/


/* ---------- Private constants ----------------------------------------------*/


/* ---------- Private Macros -------------------------------------------------*/


#endif