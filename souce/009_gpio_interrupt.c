/*
 * 009_gpio_interrupt.c
 *
 *  Created on: May 20, 2021
 *      Author: Admin
 */


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

//Definitions
#define LEDS GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
#define PINS GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3

//Declarations
void initClock(void);
void initGPIO(void);
void GPIOIntHandler(void);

//Main routine
int main(void) {
    initClock();
    initGPIO();
    return 0;
}

//Clock initialization
void initClock(void){
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_5);
}

//GPIO initialization and interrupt enabling
void initGPIO(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LEDS);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, PINS);
    GPIOPadConfigSet(GPIO_PORTB_BASE, PINS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_0|GPIO_INT_PIN_1|GPIO_INT_PIN_2|GPIO_INT_PIN_3);
    GPIOIntTypeSet(GPIO_PORTB_BASE, PINS, GPIO_LOW_LEVEL);
    IntPrioritySet(INT_GPIOB, 0);
    IntRegister(INT_GPIOB, GPIOIntHandler);
    IntEnable(INT_GPIOB);
    IntMasterEnable();
}

//Interrupt service routine
void GPIOIntHandler(void){
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_INT_PIN_0|GPIO_INT_PIN_1|GPIO_INT_PIN_2|GPIO_INT_PIN_3);

    if (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1))
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
    }
}

