#include "led.h"
#include "driver/gpio.h"

// LED GPIO pin
static const gpio_num_t LED_GPIO = GPIO_NUM_6;

// LED state (true = ON, false = OFF)
static bool led_state = false;

esp_err_t led_init(void)
{
    gpio_config_t io_conf = {0};
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LED_GPIO);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    
    esp_err_t ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        return ret;
    }
    
    // Start with LED off
    gpio_set_level(LED_GPIO, 0);
    led_state = false;
    
    return ESP_OK;
}

esp_err_t led_on(void)
{
    gpio_set_level(LED_GPIO, 1);
    led_state = true;
    return ESP_OK;
}

esp_err_t led_off(void)
{
    gpio_set_level(LED_GPIO, 0);
    led_state = false;
    return ESP_OK;
}

esp_err_t led_toggle(void)
{
    // Toggle the state
    bool new_state = !led_state;
    
    // Write to GPIO
    gpio_set_level(LED_GPIO, new_state ? 1 : 0);
    
    // Update software state
    led_state = new_state;
    
    return ESP_OK;
}

bool led_get_state(void)
{
    return led_state;
}