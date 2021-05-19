/*
 * 003_systick_delay.c
 *
 *  Created on: Apr 15, 2021
 *      Author: Admin
 */


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

#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

#include "inc/tm4c123gh6pm.h"


/* delay is in 62.5ns units */

void SysTick_Wait(uint32_t delay)
{
    NVIC_ST_CTRL_R = 0;            /* (1) disable SysTick during setup */
    NVIC_ST_RELOAD_R = delay-1;    /* (2) number of counts to wait */
    NVIC_ST_CURRENT_R = 0;         /* (3) any value written to CURRENT clears */
    NVIC_ST_CTRL_R |= 0x5;         /* (4) enable SysTick with core clock */

    while((NVIC_ST_CTRL_R&0x00010000)==0) {
        ;                          /* wait for COUNT flag */
    }
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC| SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);


    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3, 0x02);
        SysTick_Wait(16000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3, 0x00);
        SysTick_Wait(16000000);

    }



}
