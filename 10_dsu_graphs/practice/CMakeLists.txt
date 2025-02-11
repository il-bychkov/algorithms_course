cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(adjacency_list ${SRC_PREFIX}/adjacency_list.c)
add_executable(adjacency_matrix ${SRC_PREFIX}/adjacency_matrix.c)
add_executable(dsu ${SRC_PREFIX}/dsu.c)
add_executable(edges_list ${SRC_PREFIX}/edges_list.c)

INSTALL(
    TARGETS
    adjacency_list
    adjacency_matrix
    dsu
    edges_list
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

