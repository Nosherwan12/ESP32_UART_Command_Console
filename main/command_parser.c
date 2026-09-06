#include "command_parser.h"
#include <string.h>
#include "esp_err.h"


esp_err_t command_parser_parse(
    char *input,
    int *argc,
    char *argv[],
    size_t max_args
){
    // Validate Parameters
    if(input == NULL || argc == NULL || argv == NULL || max_args == 0){
        return ESP_ERR_INVALID_ARG;
    }

    // Initialize argument count
    *argc = 0;

    // Get first token
    char *token = strtok(input, " \t");  // Split by space and tab

    while (token != NULL) {
        // Check if we have room for more arguments
        if (*argc >= max_args) {    
            return ESP_ERR_INVALID_ARG;     // Too many arguments
        }
        // Store the token in argv array
        argv[*argc] = token;
        
        //  Increment argument count
        (*argc)++;
        
        // Get next token
        token = strtok(NULL, " \t");
    }

     // NULL terminate the argv array 
    argv[*argc] = NULL;
    
    return ESP_OK;
}
