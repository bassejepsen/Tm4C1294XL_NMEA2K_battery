
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <stdlib.h>
#include "Debug_UART.h"



Debug_UART * DebugUART_Init(){
    Debug_UART *p = (Debug_UART *) malloc(sizeof(Debug_UART));
    p->open =&DebugUART_open;
    p->write = &DebugUART_write;
    p->close = &DebugUART_close;
    return p;
}

int DebugUART_open(Debug_UART *self, unsigned int baud){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
       GPIOPinConfigure(GPIO_PD5_U2TX);
       GPIOPinConfigure(GPIO_PD4_U2RX);
       // Enable UART0 so that we can configure the clock.
       SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);

       // Use the internal 16MHz oscillator as the UART clock source.
       UARTClockSourceSet(UART2_BASE, UART_CLOCK_PIOSC);


       // Select the alternate (UART) function for these pins.
       GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);

       UARTStdioConfig(2, baud, 16000000);
       UARTprintf("UART debugging is alive...\n");
       return 1;
}
void DebugUART_close(Debug_UART *self){
    return free(self);
}

int DebugUART_write(Debug_UART *self, const char *pcString, ...){
    va_list vaArgP;

        //
        // Start the varargs processing.
        //
        va_start(vaArgP, pcString);

        UARTprintf(pcString, vaArgP);

        //
        // We're finished with the varargs now.
        //
        va_end(vaArgP);
    return 1;
}
