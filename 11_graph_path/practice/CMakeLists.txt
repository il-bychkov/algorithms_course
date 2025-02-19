cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(bellman_ford ${SRC_PREFIX}/bellman_ford.c)
add_executable(dijkstra ${SRC_PREFIX}/dijkstra.c)
add_executable(floyd_warshall ${SRC_PREFIX}/floyd_warshall.c)

INSTALL(
    TARGETS
    bellman_ford
    dijkstra
    floyd_warshall
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

