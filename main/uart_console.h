#ifndef UART_CONSOLE_H
#define UART_CONSOLE_H

#include "esp_err.h"
#include <stddef.h>

esp_err_t uart_console_init(void);

int uart_console_write(const char *data, size_t length);

int uart_console_read(char *buffer, size_t length);

#endif