idf_component_register(
    SRCS "command_handlers.c"
    INCLUDE_DIRS "include"
    REQUIRES led uart_console
    PRIV_REQUIRES spi_flash
)