/*
 * 007_state_led.h
 *
 *  Created on: Apr 15, 2021
 *      Author: Admin
 */

#ifndef INC_007_STATE_LED_H_
#define INC_007_STATE_LED_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"



typedef enum {R_OFF, R_ON, P_ON, P_OFF} state1_t;

typedef enum {R_OFF, R_ON, P_ON, P_OFF} state2_t;

typedef enum {R, P} button_t;
typedef enum {ON, OFF} led_t;

void initState(void);
void statemMachineUpdate(void);
void buttonInit(void);
button_t button(void);

void ledInt(void);
void ledCrt(int state);

#endif /* INC_007_STATE_LED_H_ */
