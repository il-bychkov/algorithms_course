cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(bst_splay ${SRC_PREFIX}/bst_splay.c)

INSTALL(
    TARGETS
    bst_splay
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

