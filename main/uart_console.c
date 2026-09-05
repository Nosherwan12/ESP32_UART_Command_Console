#include "uart_console.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"    
#include "esp_log.h"           
#include <stdbool.h>   

#define UART_CONSOLE_NUM        UART_NUM_1
#define UART_CONSOLE_TX_GPIO    17
#define UART_CONSOLE_RX_GPIO    18
#define UART_CONSOLE_BAUD_RATE  115200

#define UART_CONSOLE_RX_BUFFER_SIZE 1024
#define UART_CONSOLE_TX_BUFFER_SIZE 1024

static const char *TAG = "UART_CONSOLE";

esp_err_t uart_console_init(void)
{
    esp_err_t err;
    
    // Install UART driver
    err = uart_driver_install(
        UART_CONSOLE_NUM,
        UART_CONSOLE_RX_BUFFER_SIZE,
        UART_CONSOLE_TX_BUFFER_SIZE,
        0,
        NULL,
        0
    );
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "uart_driver_install failed: %s", esp_err_to_name(err));
        return err;
    }

    // Configure UART parameters
    const uart_config_t uart_config = {
        .baud_rate = UART_CONSOLE_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    err = uart_param_config(UART_CONSOLE_NUM, &uart_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "uart_param_config failed: %s", esp_err_to_name(err));
        return err;
    }

    // Set UART pins
    err = uart_set_pin(
        UART_CONSOLE_NUM,
        UART_CONSOLE_TX_GPIO,
        UART_CONSOLE_RX_GPIO,
        UART_PIN_NO_CHANGE,
        UART_PIN_NO_CHANGE
    );
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "uart_set_pin failed: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(TAG, "UART initialized on TX: GPIO%d, RX: GPIO%d, Baud: %d", 
             UART_CONSOLE_TX_GPIO, UART_CONSOLE_RX_GPIO, UART_CONSOLE_BAUD_RATE);
    
    return ESP_OK;
}

int uart_console_write(const char *data, size_t length)
{
    return uart_write_bytes(UART_CONSOLE_NUM, data, length);
}

int uart_console_read(char *buffer, size_t length)
{
    return uart_read_bytes(
        UART_CONSOLE_NUM,
        buffer,
        length,
        pdMS_TO_TICKS(1000)   // Wait up to 1000ms
    );
}


