#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t led_init(void);
esp_err_t led_on(void);
esp_err_t led_off(void);
esp_err_t led_toggle(void);
bool led_get_state(void);

#ifdef __cplusplus
}
#endif

#endif