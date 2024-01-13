.PHONY: help

all: linked_list array_stack list_stack list_queue array_queue # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

linked_list: linked_list.c # Build linked list
	gcc linked_list.c -o linked_list

array_stack: array_stack.c # Build array based stack
	gcc array_stack.c -o array_stack

list_stack: list_stack.c # Build list based stack
	gcc list_stack.c -o list_stack

list_queue: list_queue.c # Build list based queue
	gcc list_queue.c -o list_queue

array_queue: array_queue.c # Build array based queue
	gcc array_queue.c -o array_queue

clean: # Delete all builded files
	rm -f linked_list array_stack list_stack list_queue array_queue
