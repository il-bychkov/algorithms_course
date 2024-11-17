cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(addresses ${SRC_PREFIX}/addresses.c)
add_executable(bitmasks ${SRC_PREFIX}/bitmasks.c)
add_executable(bitmask_simple_example ${SRC_PREFIX}/bitmask_simple_example.c)
add_executable(bitop_oneline ${SRC_PREFIX}/bitop_oneline.c)
add_executable(bitop_oneline ${SRC_PREFIX}/bitop_oneline_alternative.c)
add_executable(bitwise_operator_example ${SRC_PREFIX}/bitwise_operator_example.c)
add_executable(check_overflow ${SRC_PREFIX}/check_overflow.c)
add_executable(check_pwr_of_two ${SRC_PREFIX}/check_pwr_of_two.c)
add_executable(decimal_to_octal ${SRC_PREFIX}/decimal_to_octal.c)
add_executable(find_unique ${SRC_PREFIX}/find_unique.c)
add_executable(int_and_float ${SRC_PREFIX}/int_and_float.c)
add_executable(literals_example ${SRC_PREFIX}/literals_example.c)
add_executable(print_bits ${SRC_PREFIX}/print_bits.c)
add_executable(signed_unsigned ${SRC_PREFIX}/signed_unsigned.c)
add_executable(swap_variables ${SRC_PREFIX}/swap_variables.c)

INSTALL(
    TARGETS
    addresses
    bitmasks
    bitmask_simple_example
    bitop_oneline
    bitop_oneline_alternative
    bitwise_operator_example
    check_overflow
    check_pwr_of_two
    decimal_to_octal
    find_unique
    int_and_float
    literals_example
    print_bits
    signed_unsigned
    swap_variables
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

