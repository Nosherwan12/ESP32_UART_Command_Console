// uart_console.h
#ifndef UART_CONSOLE_H
#define UART_CONSOLE_H

#include "esp_err.h"
#include <stddef.h>  // For size_t

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations
esp_err_t uart_console_init(void);
int uart_console_write(const char *data, size_t length);
int uart_console_read(char *buffer, size_t length);

#ifdef __cplusplus
}
#endif

#endif // UART_CONSOLE_H