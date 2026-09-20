#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function declarations
esp_err_t command_dispatcher_execute(int argc, char *argv[]);
esp_err_t command_dispatcher_print_help(void);

#ifdef __cplusplus
}
#endif

#endif 