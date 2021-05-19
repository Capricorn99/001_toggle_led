
//LED R 1s, LED B 2s

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

volatile uint32_t time = 0;
uint32_t RedLedTime = 0, BlueLedTime = 0;

void SysTick_ISR()
{
    time++;
    if ((RedLedTime + 499) < time) //mất khoảng 1 ms để thực hiện các lệnh trong if, nên lấy 499 cho tròn số
     {
         GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
         // Đọc giá trị PF1 từ thanh ghi, đảo bit (~) sau đó ghi trở lại.
         RedLedTime = time;
     }
     if ((BlueLedTime + 999) < time)
      {
          GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2));
          BlueLedTime = time;
      }
}

int main(void)
{ // 16MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC| SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    SysTickPeriodSet(SysCtlClockGet()/1000);
    SysTickIntRegister(&SysTick_ISR);
    SysTickIntEnable();
    SysTickEnable();
}
