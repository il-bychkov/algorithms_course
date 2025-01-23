cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(binary_tree ${SRC_PREFIX}/binary_tree.c)
add_executable(heap_array ${SRC_PREFIX}/heap_array.c)
add_executable(heap_tree ${SRC_PREFIX}/heap_tree.c)

INSTALL(
    TARGETS
    binary_tree
    heap_array
    heap_tree
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

