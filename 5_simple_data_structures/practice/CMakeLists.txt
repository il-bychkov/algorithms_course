cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(array_queue ${SRC_PREFIX}/array_queue.c)
add_executable(array_stack ${SRC_PREFIX}/array_stack.c)
add_executable(linked_list ${SRC_PREFIX}/linked_list.c)
add_executable(list_queue ${SRC_PREFIX}/list_queue.c)
add_executable(list_stack ${SRC_PREFIX}/list_stack.c)

INSTALL(
    TARGETS
    array_queue
    array_stack
    linked_list
    list_queue
    list_stack
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)
