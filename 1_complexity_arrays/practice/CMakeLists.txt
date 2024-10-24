cmake_minimum_required(VERSION 3.16)
project("practice_1")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(addresses_arrays             ${SRC_PREFIX}/addresses_arrays.c)
add_executable(cols_rows_perf               ${SRC_PREFIX}/cols_rows_perf.c)
add_executable(delete_element_alg           ${SRC_PREFIX}/delete_element_alg.c)
add_executable(delete_element_perf          ${SRC_PREFIX}/delete_element_perf.c)
add_executable(find_element_index_alg       ${SRC_PREFIX}/find_element_index_alg.c)
add_executable(find_element_index_perf      ${SRC_PREFIX}/find_element_index_perf.c)
add_executable(get_element_by_index_perf    ${SRC_PREFIX}/get_element_by_index_perf.c)
add_executable(insert_element_alg           ${SRC_PREFIX}/insert_element_alg.c)
add_executable(insert_element_perf          ${SRC_PREFIX}/insert_element_perf.c)

INSTALL(TARGETS         addresses_arrays
                        cols_rows_perf
                        delete_element_alg
                        delete_element_perf
                        find_element_index_alg
                        find_element_index_perf
                        get_element_by_index_perf
                        insert_element_alg
                        insert_element_perf
        DESTINATION     ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR})
