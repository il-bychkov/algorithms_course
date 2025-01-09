cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(hash_table ${SRC_PREFIX}/hash_table.c)
add_executable(max_stack ${SRC_PREFIX}/max_stack.c)

INSTALL(
    TARGETS
    hash_table
    max_stack
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

