#Служебная часть===================================================================================
cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE cmake/arm-none-eabi-gcc.cmake)


#Свойства проекта (прошивка)===================================================================================
project(mk_23 LANGUAGES C CXX ASM)
SET(DEVICE stm32f303cv)

include(libopencm3)


#Цель проекта===================================================================================
add_executable(${PROJECT_NAME}
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME}
    libopencm3
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
#Программированние МК===================================================================================
set(PROG stlink)
string(CONCAT PROG_TARGET ${LOCM3_DEVICE_SERIES} x)

include(oocd_flash_script)
install(CODE ${OOCD_FLASH_SCRIPT})
