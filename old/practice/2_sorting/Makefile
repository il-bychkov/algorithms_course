.PHONY: help

all: utility_demo counting_sort bucket_sort qsort  # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

utility_demo: sorting.c utility_demo.c # Build avaliable utilities demo
	gcc sorting.c utility_demo.c -o utility_demo

counting_sort: sorting.c counting_sort.c # Build counting sort implementation
	gcc sorting.c counting_sort.c -o counting_sort

bucket_sort: sorting.c bucket_sort.c # Build bucket sort implementation
	gcc sorting.c bucket_sort.c -o bucket_sort

qsort:
	gcc qsort_hoar.c -o qsort_hoar
	gcc qsort_lomuto.c -o qsort_lomuto

clean: # Delete all builded files
	rm -f utility_demo counting_sort bucket_sort
