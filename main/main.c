#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include "esp_err.h"

#include "uart_console.h"
#include "command_parser.h"
#include "command_dispatcher.h"
#include "led.h"

#define COMMAND_BUFFER_SIZE 256

void app_main(void)
{
    // Initialize UART console
    ESP_ERROR_CHECK(uart_console_init());

    ESP_ERROR_CHECK(led_init());

    // Command storage
    char command_buffer[COMMAND_BUFFER_SIZE];
    size_t cmd_index = 0;
    char ch;

    // Argument storage
    char *argv[COMMAND_PARSER_MAX_ARGS + 1];
    int argc;

    // Track previous character for CR/LF handling
    bool previous_was_terminator = false;
    bool command_overflow = false;

    while (1) {
        // Read one character from UART
        int len = uart_console_read(&ch, 1);
        if (len != 1) {
            continue;
        }

        // Handle line termination (CR or LF)
        if (ch == '\r' || ch == '\n') {
            // Skip second character of CRLF pair
            if (previous_was_terminator) {
                previous_was_terminator = false;
                continue;
            }
            previous_was_terminator = true;

            // Check if overflow occurred
            if (command_overflow) {
                uart_console_printf("Error: Command too long\r\n");
                // Reset for next command
                cmd_index = 0;
                command_overflow = false;
                continue;
            }

            // Null-terminate the command string
            command_buffer[cmd_index] = '\0';

            // Process non-empty commands
            if (cmd_index > 0) {
                // Parse the command
                esp_err_t err = command_parser_parse(
                    command_buffer,
                    &argc,
                    argv,
                    COMMAND_PARSER_MAX_ARGS
                );

                if (err == ESP_OK) {
                    // Dispatch and execute the command
                    esp_err_t exec_err = command_dispatcher_execute(argc, argv);
                    
                    if (exec_err == ESP_ERR_NOT_FOUND) {
                        // Error message already printed by dispatcher
                    } 
                } else {
                    uart_console_printf("Error: Too many arguments!\r\n");
                }
            }

            // Reset for next command
            cmd_index = 0;
        }

        // Handle printable characters
        else if (isprint((unsigned char)ch)) {
            previous_was_terminator = false;

            // If overflow already occurred, discard characters
            if (command_overflow) {
                continue;
            }

            // Store character if buffer has space
            if (cmd_index < COMMAND_BUFFER_SIZE - 1) {
                command_buffer[cmd_index] = ch;
                cmd_index++;
            } else {
                // Buffer is full - set overflow flag
                command_overflow = true;
                // Discard this character (don't store it)
            }
        }
    }
}