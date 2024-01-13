.PHONY: help

all: utility_demo # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

utility_demo: ../2_sorting/sorting.c ../2_sorting/utility_demo.c # Build avaliable utilities demo
	gcc ../2_sorting/sorting.c ../2_sorting/utility_demo.c -o utility_demo

linear_search: ../2_sorting/sorting.c linear_search.c
	gcc ../2_sorting/sorting.c linear_search.c -o linear_search

binary_search: ../2_sorting/sorting.c binary_search.c
	gcc ../2_sorting/sorting.c binary_search.c -o binary_search

exponential_search_with_recursive_binary_search: ../2_sorting/sorting.c exponential_search_w_rec_binary.c
	gcc ../2_sorting/sorting.c exponential_search_w_rec_binary.c -o exponential_search_with_recursive_binary_search

exponential_search_with_iterative_binary_search: ../2_sorting/sorting.c exponential_search_w_itr_binary.c
	gcc ../2_sorting/sorting.c exponential_search_w_itr_binary.c -o exponential_search_with_iterative_binary_search

interpolation_search: ../2_sorting/sorting.c interpolation_search.c
	gcc ../2_sorting/sorting.c interpolation_search.c -o interpolation_search

clean: # Delete all builded files
	rm -f utility_demo
