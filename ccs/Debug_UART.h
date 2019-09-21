#ifndef DEBUG_UART_H_
#define DEBUG_UART_H_



typedef struct Debug_UART{
    int (*open)(void *self, unsigned int baud);
    void (*close)(void *self);
    int (*write)(void *self, const char *pcString, ...);
    // And data goes here.
} Debug_UART;


// Prototypes
Debug_UART * DebugUART_Init();
int DebugUART_open(Debug_UART *self, unsigned int baud);
void DebugUART_close(Debug_UART *self);
int DebugUART_write(Debug_UART *self, const char *pcString, ...);

#endif
