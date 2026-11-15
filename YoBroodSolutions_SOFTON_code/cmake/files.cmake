file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/SYSTEM/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/*.c"
)

# Filter the HAL library so that only the non-template and -ll files remain
list(FILTER APP_SOURCES EXCLUDE REGEX "_template\\.(c|h)$")
list(FILTER APP_SOURCES EXCLUDE REGEX "stm32f4xx_ll_.*\\.c$")
list(FILTER APP_SOURCES EXCLUDE REGEX "_hcd\\.c$")

# Don't need this because we are filtering the glob-made list above
# set(HAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src")

# set(HAL_SOURCES
#   "${HAL_DIR}/stm32f4xx_hal.c"
#   "${HAL_DIR}/stm32f4xx_hal_cortex.c"
#   "${HAL_DIR}/stm32f4xx_hal_gpio.c"
#   "${HAL_DIR}/stm32f4xx_hal_rcc.c"
#   "${HAL_DIR}/stm32f4xx_hal_rcc_ex.c"
#   "${HAL_DIR}/stm32f4xx_hal_pwr.c"
#   "${HAL_DIR}/stm32f4xx_hal_pwr_ex.c"
#   "${HAL_DIR}/stm32f4xx_hal_tim.c"
#   "${HAL_DIR}/stm32f4xx_hal_tim_ex.c"
#   "${HAL_DIR}/stm32f4xx_hal_uart.c"
#   # Add stm32f4xx_hal_dma.c if your application uses HAL DMA functions.
# )


# Add sources to executable/library
target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Startup/startup_stm32f407xx.S"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/EE_API_LIB/EE_API.c"
    ${APP_SOURCES}
    ${HAL_SOURCES}
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/stm32f407xg_flash.ld" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/stm32f407xg_flash.ld")
