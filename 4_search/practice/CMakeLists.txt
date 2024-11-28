cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(benchmark ${SRC_PREFIX}/benchmark.c)
add_executable(binary_search ${SRC_PREFIX}/binary_search.c)
add_executable(exponential_search ${SRC_PREFIX}/exponential_search.c)
add_executable(interpolation_search ${SRC_PREFIX}/interpolation_search.c)
add_executable(jump_search ${SRC_PREFIX}/jump_search.c)
add_executable(linear_search ${SRC_PREFIX}/linear_search.c)
add_executable(ternary_search ${SRC_PREFIX}/ternary_search.c)
add_executable(ternary_search_for_unimodal_func ${SRC_PREFIX}/ternary_search_for_unimodal_func.c)

target_link_libraries(benchmark m)
target_link_libraries(jump_search m)

INSTALL(
    TARGETS
    benchmark
    binary_search
    exponential_search
    interpolation_search
    jump_search
    linear_search
    ternary_search
    ternary_search_for_unimodal_func
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

