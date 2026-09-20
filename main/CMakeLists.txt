idf_component_register(
    SRCS "main.c"
    REQUIRES uart_console command_parser command_dispatcher led
)