## Topological sorting algorithms

### Kahn's Algorithm

### Description.
Kahn's algorithm uses a queue to process vertices with zero incoming degree.

### Example of work

Input:
```
8
0 0 0 0 0 0 0 0
0 0 0 0 1 0 1 0
0 0 0 0 0 0 0 1
0 0 0 0 1 0 0 1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
1 0 0 0 0 1 1 0
```

Output:
```
Graph
0 - None
1 - 4 6
2 - 7
3 - 4 7
4 - None
5 - None
6 - None
7 - 0 5 6
Khan`s topological sort result:
1 2 3 4 7 0 5 6
```

### Topological sorting algorithm using DFS

### Description

DFS traverses the graph and adds vertices to the stack in traversal order, then retrieves vertices from the stack in reverse order.

### Example of work

Input:
```
8
0 0 0 0 0 0 0 0
0 0 0 0 1 0 1 0
0 0 0 0 0 0 0 1
0 0 0 0 1 0 0 1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
1 0 0 0 0 1 1 0
```

Output:

```
Graph
0 - None
1 - 4 6
2 - 7
3 - 4 7
4 - None
5 - None
6 - None
7 - 0 5 6
DFS topsort result:
3 2 7 5 1 6 4 0
```
