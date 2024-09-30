.PHONY: help

all: kruskal prima # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

kruskal: kruskal.cpp
	g++ -std=c++20 kruskal.cpp -o kruskal

prima: prima.cpp
	g++ -std=c++20 prima.cpp -o prima

clean: # Delete all builded files
	rm -f kruskal prima
