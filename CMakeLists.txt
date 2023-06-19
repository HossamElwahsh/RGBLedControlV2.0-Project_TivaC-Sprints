cmake_minimum_required(VERSION 3.25)
project(shared C)

set(CMAKE_C_STANDARD 11)

include_directories(LED-V2.0)
include_directories(LED-V2.0/APP)
include_directories(LED-V2.0/HAL)
include_directories(LED-V2.0/HAL/led)
include_directories(LED-V2.0/HAL/btn)
include_directories(LED-V2.0/LIB)
include_directories(LED-V2.0/MCAL)
include_directories(LED-V2.0/MCAL/gpio)
include_directories(LED-V2.0/MCAL/systick)
include_directories(LED-V2.0/RTE/_Target_1)

add_executable(shared

        LED-V2.0/APP/app.c
        LED-V2.0/APP/app.h
        LED-V2.0/HAL/led/led_interface.h
        LED-V2.0/HAL/led/led_program.c
        LED-V2.0/LIB/bit_math.h
        LED-V2.0/LIB/std.h
        LED-V2.0/MCAL/gpio/gpio_interface.h
        LED-V2.0/MCAL/gpio/gpio_private.h
        LED-V2.0/MCAL/gpio/gpio_program.c
        LED-V2.0/RTE/_Target_1/RTE_Components.h
        LED-V2.0/RTE/Device/TM4C123GH6PM/system_TM4C123.c
        LED-V2.0/led_interface.h
        LED-V2.0/main.c
        LED-V2.0/MCAL/systick/systick_program.c
        LED-V2.0/HAL/btn/btn_program.c)
