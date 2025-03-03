cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(kruskal ${SRC_PREFIX}/kruskal.cpp)
add_executable(prim ${SRC_PREFIX}/prim.cpp)

INSTALL(
    TARGETS
    kruskal
    prim
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

