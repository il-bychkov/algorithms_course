cmake_minimum_required(VERSION 3.16)
project("practice")

set(SRC_PREFIX src)
set(INSTAL_DIR bin)

add_executable(merge_sort ${SRC_PREFIX}/merge_sort.c)
add_executable(nth_element ${SRC_PREFIX}/nth_element.c)
add_executable(qsort_hoar ${SRC_PREFIX}/qsort_hoar.c)
add_executable(qsort_lomuto ${SRC_PREFIX}/qsort_lomuto.c)
add_executable(req_1_to_n ${SRC_PREFIX}/req_1_to_n.c)
add_executable(req_a_to_b ${SRC_PREFIX}/req_a_to_b.c)
add_executable(req_check_pwr_2 ${SRC_PREFIX}/req_check_pwr_2.c)
add_executable(req_num_ones ${SRC_PREFIX}/req_num_ones.c)
add_executable(req_rotate_digits ${SRC_PREFIX}/req_rotate_digits.c)
add_executable(req_sum_digits ${SRC_PREFIX}/req_sum_digits.c)
add_executable(req_sum_digits ${SRC_PREFIX}/tim_sort.c)

INSTALL(
    TARGETS
    merge_sort
    nth_element
    qsort_hoar
    qsort_lomuto
    req_1_to_n
    req_a_to_b
    req_check_pwr_2
    req_num_ones
    req_rotate_digits
    req_sum_digits
    tim_sort
    DESTINATION
    ${CMAKE_CURRENT_SOURCE_DIR}/${INSTAL_DIR}
)

