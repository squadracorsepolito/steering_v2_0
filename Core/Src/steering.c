/**
 * @file    steering.c
 * @author  Pietro Levo [pietro.levo.sc@gmail.com]
 * @date    2025-09-03 (date of creation)
 * @updated 2025-09-04 (date of last update)
 * @version v0.1.0
 * @prefix  STE
 *
 * @brief   Implementation of some software
 * @details This code implements the function to activate the steering wheel
 *          and run the components
 *
 * @license Licensed under "THE BEER-WARE LICENSE", Revision 69 
 *          see LICENSE file in the root directory of this software component
 */

/*---------- Includes --------------------------------------------------------*/

#include "steering.h"

/*---------- Private define --------------------------------------------------*/
#define BTN_SAMPLE_TIME 10
#define RSW_SAMPLE_TIME 10
#define CAN_CYCLE_TIME 500
/*---------- Private macro ---------------------------------------------------*/


/*---------- Private variables -----------------------------------------------*/


/*---------- Private function prototypes -------------------------------------*/


/*---------- Exported Variables ----------------------------------------------*/


/*---------- Exported Functions ----------------------------------------------*/
void steering_run(btnStateHandleTypedef *hbtn, rswStateHandleTypedef *hrsw) {
    static uint32_t sfwTimSample = 0;
    static uint32_t sfwTimCan = 0;
    uint8_t payload[3];
    uint32_t now = HAL_GetTick();

    if (now >= sfwTimSample) {
        sfwTimSample = now + BTN_SAMPLE_TIME;
        BTN_Sample(hbtn);
        RSW_sample(hrsw);
    }

    if (now >= sfwTimCan) {
        sfwTimCan = now + CAN_CYCLE_TIME;
        CAN_build_payload(payload, hbtn, hrsw);
        CAN_steering_Msg_send(&hcan1, payload, 3);
    }
}

/*---------- Private Functions -----------------------------------------------*/

