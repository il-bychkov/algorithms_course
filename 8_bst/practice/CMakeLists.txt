cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(bst ${SRC_PREFIX}/bst.c)
add_executable(bst_avl ${SRC_PREFIX}/bst_avl.c)

INSTALL(
    TARGETS
    bst
    bst_avl
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

