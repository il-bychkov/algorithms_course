cmake_minimum_required(VERSION 3.16)
project("practice_0")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(addresses                    ${SRC_PREFIX}/addresses.c)
add_executable(int_and_float                ${SRC_PREFIX}/int_and_float.c)

INSTALL(TARGETS         addresses
                        int_and_float
        DESTINATION     ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR})
