/*
 * 007_state_led.c
 *
 *  Created on: Apr 15, 2021
 *      Author: Admin
 */
#include "007_state_led.h"

static state1_t State1;
static state2_t State2;

void initState()
{
    State1 = R_OFF;
}

void buttonInit()
{
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //0-SW2 4-SW1
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}

void ledInt()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //
}

void ledCrt(int state)
{
    if (state == OFF)
    {

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3, 0x00);

    }
    else if (state == ON)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3, 0x02);


    }

}

button_t button()
{
    if (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0))
    {
        SysCtlDelay(200000);


        return P;
    }
    else //if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0)==1)
    {
        SysCtlDelay(200000);

        return R;
    }

}


void stateMachineUpdate(void)
{
    switch (State1)
    {
    case R_OFF:
        if (button() == P)
            State = P_ON;
        break;

    case P_ON:
        if (button() == R)
            State = R_ON;
        break;
    case R_ON:
        if (button() == P)
            State = P_OFF;
        break;
    case P_OFF:
        if (button() == R)
            State = R_OFF;
        break;
    }

    switch (State1)
    {
    case R_ON:
    case P_ON:
        ledCrt(ON);
        break;
    case R_OFF:
    case P_OFF:
        ledCrt(OFF);
        break;
    }
}

int main (void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    buttonInit();
    ledInt();
    initState();
    while (1)
    {
        stateMachineUpdate();
    }

}



