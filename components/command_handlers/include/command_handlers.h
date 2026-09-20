#ifndef COMMAND_HANDLERS_H
#define COMMAND_HANDLERS_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations
esp_err_t led_handler(int argc, char *argv[]);
esp_err_t info_handler(int argc, char *argv[]);
esp_err_t reboot_handler(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

#endif 