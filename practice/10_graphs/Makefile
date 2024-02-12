.PHONY: help

all: adjacency_list adjacency_matrix edges_list # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

adjacency_list: adjacency_list.c # Build adjacency list based graph
	gcc adjacency_list.c -o adjacency_list

adjacency_matrix: adjacency_matrix.c # Build adjacency matrix based graph
	gcc adjacency_matrix.c -o adjacency_matrix

edges_list: edges_list.c # Build edges list based graph
	gcc edges_list.c -o edges_list

clean: # Delete all builded files
	rm -f adjacency_list adjacency_matrix edges_list
