### Node class
The `Node` class implements key-value pairs along with a boolean flag indicating whether the node is currently in use or not. It provides functionality for updating values, checking for node emptiness, and overloading the print output statement.

### HashMap class
The `HashMap` class implements a hash table data structure using an array of pointers to `Node` objects. It supports insert (`put`), delete (`del`), search (`get`), resize and re-hash operations. In addition, operators for indexing (`[]`), equality comparison (`==` and `!=`), and the output operator (`<<`) are overloaded.

### Hashing Functions
The `HashMap` class uses two hash functions to generate indexes based on string and integer keys. These hash functions involve the double hashing method for efficient collision resolution.

### Collision Resolution
Collisions are resolved using the double hashing methods. If a collision occurs during insertion or search, the algorithm searches for an alternative index by applying a second hash function.

### Resizing and Re-hashing
The hash table automatically resizes itself and performs re-hashing when it becomes too full or contains too many deleted items. This helps maintain an acceptable load factor and ensures efficient performance.

### Test class
The `Test` class provides several tests to demonstrate the functionality of the `HashMap` class. The tests cover scenarios such as basic operations, string comparison, operator overloading, and handling invalid keys.
