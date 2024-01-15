.PHONY: help

all: bitmanip # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

bitmanip: bitmanip.c # Build bit manupulation list
	gcc bitmanip.c -o bitmanip

clean: # Delete all builded files
	rm -f bitmanip
