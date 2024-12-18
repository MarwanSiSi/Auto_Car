# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Auto_Car C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Auto_Car Auto_Car.c bluetooth.c ultrasonicBehind.c br_motor.c bl_motor.c ultrasonicFront.c light.c fr_motor.c fl_motor.c speed.c led.c 
buzzer.c  )
pico_set_program_name(Auto_Car "Auto_Car")
pico_set_program_version(Auto_Car "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Auto_Car 0)
pico_enable_stdio_usb(Auto_Car 1)

# Add the standard library to the build
target_link_libraries(Auto_Car pico_stdlib hardware_adc hardware_pwm hardware_uart hardware_irq)


# Add the standard include files to the build
target_include_directories(Auto_Car PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(Auto_Car 
        
        )

pico_add_extra_outputs(Auto_Car)

