/*
 * main.c
 *
 *  Created on: May 19, 2021
 *      Author: Admin
 */




#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"




void GPIOIntHandler()
{

}
void Timer0IntHandler()
{
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //echo pinA2
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_2);
    GPIOIntTypeSet(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_BOTH_EDGES);
    IntPrioritySet(INT_GPIOA, 0);
    IntRegister(INT_GPIOA, GPIOIntHandler);
    IntEnable(INT_GPIOA);
    IntMasterEnable();

    //trigger A3
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0x00);

    //Kich hoat timer0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
    IntRegister(INT_TIMER0A, Timer0IntHandler);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // timer2
    TimerConfigure(TIMER2_BASE, TIMER_CFG_ONE_SHOT_UP);

    while(1) {
        TimerLoadSet(TIMER0_BASE, TIMER_A, (SysCtlClockGet()/100000) - 1);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3);
        TimerEnable(TIMER0_BASE, TIMER_A);
    }
}




