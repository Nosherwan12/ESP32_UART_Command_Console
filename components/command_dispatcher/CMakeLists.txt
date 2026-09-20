idf_component_register(
    SRCS "command_dispatcher.c"
    INCLUDE_DIRS "include"
    REQUIRES command_handlers uart_console
)
