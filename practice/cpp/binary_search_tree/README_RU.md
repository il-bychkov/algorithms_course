# Бинарное дерево поиска

## Вводная информация

Бинарное дерево поиска - это структура данных, состоящая из узлов, каждый из которых имеет не более двух потомков: левого и правого. В таком дереве все значения в левом поддереве меньше либо равны значению корня, а значения в правом поддереве больше либо равны. Это позволяет эффективно выполнять операции поиска, вставки и удаления элементов.

## Класс Binary Search Tree Node

### Поля:

+ BinarySearchTreeNode* parent;
+ BinarySearchTreeNode* leftChild;
+ BinarySearchTreeNode* rightChild;
+ int key;

## Класс Binary Search Tree

### Поля:

+ BinarySearchTreeNode* root (корень)

### Функции: 

+ minNode - поиск минимального
+ maxNode - поиск максимального
+ preorderWalk, inorderWalk, postorderWalk - обход дерева
+ inorderExploration, inorderExplorationUtility - обход дерева с возвратом вектора (результата обхода)
+ successor, predecessor - вычисление предка, потомка 
+ insert - вставка в дерево
+ deleteVertex - удаление из дерева
+ transplant - вспомогательная функция для удаления

## Пример работы

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

Inorder обход:
```
3 4 6 7 8 10 20 25 30
```
Preorder обход:
```
3 25 10 8 6 4 7 20 30
```
Postorder обход:
```
4 7 6 8 20 10 30 25 3
```

Inorder обход - отсортированный массив?
```
CORRECT
```
