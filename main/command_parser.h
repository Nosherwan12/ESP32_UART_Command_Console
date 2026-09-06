#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <stddef.h>
#include "esp_err.h"

#define COMMAND_PARSER_MAX_ARGS 8

esp_err_t command_parser_parse(
    char *input,
    int *argc,
    char *argv[],
    size_t max_args
);

#endif