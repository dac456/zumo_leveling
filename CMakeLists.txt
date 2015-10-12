set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # AVR Toolchain


cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(zumo_leveling C CXX ASM)

#SET(ASM_OPTIONS "-x assembler-with-cpp")
#SET(CMAKE_ASM_FLAGS "${CFLAGS} ${ASM_OPTIONS}" )
SET(CMAKE_C_FLAGS "${CFLAGS} -std=gnu99 -O2 -Wl,-u,vfprintf -lprintf_flt -lm" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wl,-u,vfprintf -lprintf_flt -lm")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Wire)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Wire/utility)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Zumo32U4)

#print_board_list()
#print_programmer_list()

file(GLOB C_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp src/*.c Wire/*.cpp Wire/utility/*.c Zumo32U4/*.cpp)


generate_arduino_firmware(zumo_leveling
SRCS ${C_SRC}
BOARD leonardo)

#add_custom_command(TARGET input_controller
#                   POST_BUILD
#                   COMMAND avr-objcopy -O ihex input_controller.elf input_controller.hex)

set(${FIRMWARE_NAME}_PORT /dev/ttyACM0)