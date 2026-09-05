#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "esp_err.h"
#include "uart_console.h"

#define COMMAND_BUFFER_SIZE 256

void app_main(void)
{
    ESP_ERROR_CHECK(uart_console_init());

    const char *message = "UART Command Console\r\n";
    uart_console_write(message, strlen(message));

    char ch;
    char cmd_buffer[COMMAND_BUFFER_SIZE];
    size_t cmd_index = 0;

    /*
     * Tracks whether the previous character was a command terminator.
     * This allows us to handle both "\r", "\n", and "\r\n".
     */
    bool previous_was_terminator = false;

    while (1) {

        int len = uart_console_read(&ch, 1);

        if (len != 1) {
            continue;
        }

        /*
         * Handle carriage return or line feed.
         */
        if (ch == '\r' || ch == '\n') {

            /*
             * Ignore the second character of "\r\n" or "\n\r".
             */
            if (previous_was_terminator) {
                continue;
            }

            previous_was_terminator = true;

            /*
             * Terminate the C string.
             */
            cmd_buffer[cmd_index] = '\0';

            /*
             * Only process non-empty commands.
             */
            if (cmd_index > 0) {
                printf("Command: %s\r\n", cmd_buffer);
            }

            /*
             * Prepare for the next command.
             */
            cmd_index = 0;
        }

        /*
         * Normal printable character.
         */
        else if (isprint((unsigned char)ch)) {

            previous_was_terminator = false;

            /*
             * Reserve one byte for '\0'.
             */
            if (cmd_index < COMMAND_BUFFER_SIZE - 1) {
                cmd_buffer[cmd_index] = ch;
                cmd_index++;
            }
        }
    }
}
