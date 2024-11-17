cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(bubble_sort ${SRC_PREFIX}/bubble_sort.c)
add_executable(bucket_sort ${SRC_PREFIX}/bucket_sort.c)
add_executable(counting_sort ${SRC_PREFIX}/counting_sort.c)
add_executable(insertion_sort ${SRC_PREFIX}/insertion_sort.c)
add_executable(radix_sort ${SRC_PREFIX}/radix_sort.c)
add_executable(selection_sort ${SRC_PREFIX}/selection_sort.c)

INSTALL(
    TARGETS
    bubble_sort
    bucket_sort
    counting_sort
    insertion_sort
    radix_sort
    selection_sort
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

