cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(2D_rows_cols_sum ${SRC_PREFIX}/2D_rows_cols_sum.c)
add_executable(2D_rows_cols_sum_simple ${SRC_PREFIX}/2D_rows_cols_sum_simple.c)
add_executable(addresses_arrays ${SRC_PREFIX}/addresses_arrays.c)
add_executable(cols_rows_perf ${SRC_PREFIX}/cols_rows_perf.c)
add_executable(delete_element_alg ${SRC_PREFIX}/delete_element_alg.c)
add_executable(delete_element_perf ${SRC_PREFIX}/delete_element_perf.c)
add_executable(D_two_dim_array_sum ${SRC_PREFIX}/D_two_dim_array_sum.c)
add_executable(find_element_index_alg ${SRC_PREFIX}/find_element_index_alg.c)
add_executable(find_element_index_perf ${SRC_PREFIX}/find_element_index_perf.c)
add_executable(get_element_by_index_perf ${SRC_PREFIX}/get_element_by_index_perf.c)
add_executable(insert_delete ${SRC_PREFIX}/insert_delete.c)
add_executable(insert_delete_global ${SRC_PREFIX}/insert_delete_global.c)
add_executable(insert_element_alg ${SRC_PREFIX}/insert_element_alg.c)
add_executable(insert_element_perf ${SRC_PREFIX}/insert_element_perf.c)

INSTALL(
    TARGETS
    2D_rows_cols_sum
    2D_rows_cols_sum_simple
    addresses_arrays
    cols_rows_perf
    delete_element_alg
    delete_element_perf
    D_two_dim_array_sum
    find_element_index_alg
    find_element_index_perf
    get_element_by_index_perf
    insert_delete
    insert_delete_global
    insert_element_alg
    insert_element_perf
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

