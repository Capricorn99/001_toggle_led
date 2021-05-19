/*
 * test_code_1.c
 *
 *  Created on: Apr 15, 2021
 *      Author: Admin
 */
#include <stdint.h>
#include <stdbool.h>
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

void initTIVA()
{
    //50MHz
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
}

void initSwitchLed()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3, 0x00);
}

void SysTick_ISR()
{
}

void initSysTick()
{
    SysTickPeriodSet(SysCtlClockGet());
    SysTickIntRegister(&SysTick_ISR);
    SysTickIntEnable();
    SysTickEnable();
}

void initUART0()
{
    // Kich hoat uart0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //Cau hinh chan PA0 va PA1 lan luot la chan RX va TX
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);  //Thieu dinh nghia pin pa1 pa0 la chan cua UART
    // Initialize the UART. Set the baud rate, number of data bits 8, number of stop bits 1, turn off parity,and stick mode. The UART is enabled by the function call.
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}

void putstr(char *str)
{
    while (*str != '\0')
    {
        //Gui tung ki tu len may tinh
        UARTCharPut(UART0_BASE, *str);
        str++;
    }
}

void getstr(char *str)
{
    int32_t input_char;
    int i;
    while(1)
    {
        if(UARTCharsAvail(UART0_BASE))
        {
            input_char = UARTCharGet(UART0_BASE);
            if (input_char == 13)
            {
                input_char = '\0';
                char *ptr = (char*)&input_char;
                for(i = 0; i < 4; i++, ptr++) str[i] = *ptr;
                break;
            }
            else
            {
                char *ptr = (char*)&input_char;
                for(i = 0; i < 4; i++) str[i] = *ptr;
                str++;
                UARTCharPut(UART0_BASE, input_char);
            }
        }
    }
}

int main (void)
{
    char *x[4];
    initTIVA();
    initUART0();
    //UARTCharPut(UART0_BASE, 'A' );

    //putstr("hello");
    putstr("\ntext: \n");
    getstr(x);
    putstr(x);
}
