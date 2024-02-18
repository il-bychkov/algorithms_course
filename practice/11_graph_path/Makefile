.PHONY: help

all: dijkstra # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

dijkstra: graph.c dijkstra.c # Build Dijkstra algorithm
	gcc graph.c	dijkstra.c -o dijkstra

bellman_ford: graph.c bellman_ford.c # Build Bellman–Ford algorithm
	gcc graph.c	bellman_ford.c -o bellman_ford

floyd_warshall: graph.c floyd_warshall.c # Build Floyd–Warshall algorithm
	gcc graph.c	floyd_warshall.c -o floyd_warshall

clean: # Delete all builded files
	rm -f dijkstra
