# Binary search tree

## Introduction

A binary search tree is a data structure consisting of nodes, each of which has at most two descendants: left and right. In such a tree, all values in the left subtree are less than or equal to the root value, and values in the right subtree are greater than or equal. This allows you to efficiently perform search, insertion and deletion operations.

## Class Binary Search Tree Node

### Fields:

+ BinarySearchTreeNode* parent;
+ BinarySearchTreeNode* leftChild;
+ BinarySearchTreeNode* rightChild;
+ int key;

## Class Binary Search Tree

### Fields:

+ BinarySearchTreeNode* root.

### Functions:

+ minNode - search for the minimum
+ maxNode - search for maximal
+ preorderWalk, inorderWalk, postorderWalk - tree traversal
+ inorderExploration, inorderExplorationUtility - traversal of a tree with return of a vector (traversal result)
+ successor, predecessor - calculation of ancestor, descendant
+ insert - insert into tree
+ deleteVertex - deletion from the tree
+ transplant - auxiliary function for deletion

## Example of work

```cpp
binarySearchTree.insert(3);
binarySearchTree.insert(25);
binarySearchTree.insert(10);
binarySearchTree.insert(30);
binarySearchTree.insert(8);
binarySearchTree.insert(6);
binarySearchTree.insert(20);
binarySearchTree.insert(4);
binarySearchTree.insert(7);
```

Inorder walk:
```
3 4 6 7 8 10 20 25 30
```
Preorder walk:
```
3 25 10 8 6 4 7 20 30
```
Postorder walk:
```
4 7 6 8 20 10 30 25 3
```

Is inorder walk sorted?
```
CORRECT
```
