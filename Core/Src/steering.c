/**
 * @file    steering.c
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

/*---------- Includes --------------------------------------------------------*/

#include "steering.h"

/*---------- Private define --------------------------------------------------*/
#define BTN_SAMPLE_TIME 10

/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/


/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/
void steering_run(btnStateHandleTypedef *hbtn) {
    static uint32_t sfwTimSample = 0;
    uint32_t now = HAL_GetTick();

    if (now >= sfwTimSample) {
        sfwTimSample = now + BTN_SAMPLE_TIME;
        BTN_Sample(hbtn);
    }

    char msg[100];

    sprintf(msg,
    "BTN: %d %d %d %d %d\r\n",
    hbtn->active[0],
    hbtn->active[1],
    hbtn->active[2],
    hbtn->active[3],
    hbtn->active[4]);
    HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

/*---------- Private Functions -----------------------------------------------*/

