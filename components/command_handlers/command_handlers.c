#include <string.h>

#include "esp_err.h"
#include "esp_chip_info.h"
#include "esp_system.h"
#include "esp_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "command_handlers.h"
#include "led.h"
#include "uart_console.h"


esp_err_t led_handler(int argc, char *argv[])
{
    if (argc != 2) {
        uart_console_printf("Usage: led <on|off|status>\r\n");
        return ESP_ERR_INVALID_ARG;
    }

    const char *action = argv[1];

    if (strcmp(action, "on") == 0) {
        esp_err_t ret = led_on();

        if (ret == ESP_OK) {
            uart_console_printf("LED turned ON\r\n");
        }

        return ret;
    }

    else if (strcmp(action, "off") == 0) {
        esp_err_t ret = led_off();

        if (ret == ESP_OK) {
            uart_console_printf("LED turned OFF\r\n");
        }

        return ret;
    }

    else if (strcmp(action, "status") == 0) {
        uart_console_printf("LED is %s\r\n",
                            led_get_state() ? "ON" : "OFF");
        return ESP_OK;
    }

    else {
        uart_console_printf(
            "Invalid action: %s (use on/off/status)\r\n",
            action
        );
        return ESP_ERR_INVALID_ARG;
    }
}


esp_err_t info_handler(int argc, char *argv[])
{
    if (argc != 1) {
        uart_console_printf("Usage: info\r\n");
        return ESP_ERR_INVALID_ARG;
    }

    uart_console_printf("=== System Info ===\r\n");

    // Chip information
    esp_chip_info_t chip;
    esp_chip_info(&chip);

    const char *chip_name;

    switch (chip.model) {
        case CHIP_ESP32:
            chip_name = "ESP32";
            break;

        case CHIP_ESP32S2:
            chip_name = "ESP32-S2";
            break;

        case CHIP_ESP32S3:
            chip_name = "ESP32-S3";
            break;

        case CHIP_ESP32C3:
            chip_name = "ESP32-C3";
            break;

        default:
            chip_name = "Unknown";
            break;
    }

    uart_console_printf(
        "Chip:      %s (%d cores)\r\n",
        chip_name,
        chip.cores
    );

    // Memory information
    uart_console_printf(
        "Free Heap: %lu KB\r\n",
        (unsigned long)(esp_get_free_heap_size() / 1024)
    );

    // Flash information
    uint32_t flash_size;
    esp_err_t ret = esp_flash_get_size(NULL, &flash_size);

    if (ret == ESP_OK) {
        uart_console_printf(
            "Flash:     %lu MB\r\n",
            (unsigned long)(flash_size / (1024 * 1024))
        );
    } else {
        uart_console_printf(
            "Flash:     unavailable (error: %s)\r\n",
            esp_err_to_name(ret)
        );
    }

    // ESP-IDF version
    uart_console_printf(
        "IDF:       %s\r\n",
        esp_get_idf_version()
    );

    // Firmware build information
    uart_console_printf(
        "Build:     %s %s\r\n",
        __DATE__,
        __TIME__
    );

    uart_console_printf("====================\r\n");

    return ESP_OK;
}


esp_err_t reboot_handler(int argc, char *argv[])
{
    // Validate: reboot command takes no arguments
    if (argc != 1) {
        uart_console_printf("Usage: reboot\r\n");
        uart_console_printf("This command takes no arguments\r\n");
        return ESP_ERR_INVALID_ARG;
    }

    // Print restart message
    uart_console_printf("SYSTEM REBOOTING...\r\n");

    // Small delay to allow UART to flush
    vTaskDelay(pdMS_TO_TICKS(100));

    // Restart the ESP32
    esp_restart();

    // Should never reach here
    return ESP_OK;
}
