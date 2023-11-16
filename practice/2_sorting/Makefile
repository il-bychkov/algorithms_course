.PHONY: help

all: utility_demo # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

utility_demo: sorting.c utility_demo.c # Build avaliable utilities demo
	gcc sorting.c utility_demo.c -o utility_demo

clean: # Delete all builded files
	rm -f utility_demo