.PHONY: help

all: hash_map # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

hash_map: hash_map_with_diff_key_value_types.cpp
	g++ -std=c++20 hash_map_with_diff_key_value_types.cpp -o hash_map

clean: # Delete all builded files
	rm -f hash_map
