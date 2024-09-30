.PHONY: help

all: knapsack_unbounded knapsack_0_1 lcm # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

knapsack_unbounded: knapsack_unbounded.c # Build knapsack_unbounded
	gcc knapsack_unbounded.c -o knapsack_unbounded

knapsack_0_1: knapsack_0_1.c # Build knapsack_0_1
	gcc knapsack_0_1.c -o knapsack_0_1

lcm: lcm.c # Build lcm
	gcc lcm.c -o lcm

clean: # Delete all builded files
	rm -f knapsack_unbounded knapsack_0_1 lcm
