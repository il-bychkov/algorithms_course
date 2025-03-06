cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(prime_numbers ${SRC_PREFIX}/prime_numbers.c)

INSTALL(
    TARGETS
    prime_numbers
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

