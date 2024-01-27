.PHONY: help

all: hash_table_map # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

hash_table_map: main.c # Build map based on hash table
	gcc main.c -o hash_table_map

clean: # Delete all builded files
	rm -f hash_table_map
