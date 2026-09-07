#include <string.h>

#include "esp_err.h"

#include "command_dispatcher.h"
#include "command_handlers.h"
#include "uart_console.h"


// Handler function pointer type
typedef esp_err_t (*command_handler_t)(int argc, char *argv[]);


// Command structure with description
typedef struct {
    const char *name;
    command_handler_t handler;
    const char *description;
} command_t;


// Command table
static const command_t command_table[] = {
    {"help",   help_handler,   "Show available commands"},
    {"led",    led_handler,    "Control LED"},
    {"info",   info_handler,   "Show system information"},
    {"reboot", reboot_handler, "Restart the ESP32"}
};


// Number of commands in table
static const size_t command_count =
    sizeof(command_table) / sizeof(command_table[0]);


// Print help function
esp_err_t command_dispatcher_print_help(void)
{
    uart_console_printf("\r\n=== Available Commands ===\r\n");
    uart_console_printf("%-10s %s\r\n", "Command", "Description");
    uart_console_printf("------------------------------\r\n");

    for (size_t i = 0; i < command_count; i++) {
        uart_console_printf(
            "%-10s %s\r\n",
            command_table[i].name,
            command_table[i].description
        );
    }

    uart_console_printf("==============================\r\n");

    return ESP_OK;
}


// Execute command function
esp_err_t command_dispatcher_execute(int argc, char *argv[])
{
    if (argc <= 0 || argv == NULL || argv[0] == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    const char *command_name = argv[0];

    // Search for command in table
    for (size_t i = 0; i < command_count; i++) {

        if (strcmp(command_name, command_table[i].name) == 0) {

            // Command found - execute handler
            if (command_table[i].handler != NULL) {
                return command_table[i].handler(argc, argv);
            }

            uart_console_printf(
                "Command '%s' handler not implemented yet\r\n",
                command_name
            );

            return ESP_ERR_NOT_SUPPORTED;
        }
    }

    // Command not found
    uart_console_printf(
        "Unknown command: %s\r\n",
        command_name
    );

    uart_console_printf(
        "Type 'help' for available commands\r\n"
    );

    return ESP_ERR_NOT_FOUND;
}