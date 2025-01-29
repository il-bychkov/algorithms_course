#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ported from
// https://www.geeksforgeeks.org/insertion-in-binary-search-tree/
// https://www.geeksforgeeks.org/deletion-in-binary-search-tree/
// https://www.geeksforgeeks.org/binary-search-tree-traversal-inorder-preorder-post-order/

typedef struct bst_node {
    uint32_t value;
    struct bst_node* left;
    struct bst_node* right;
} bst_node_t;

typedef struct bst {
    struct bst_node* root;
} bst_t;

void create_bst(bst_t* bst) {
    bst->root = NULL;
}

void _delete_bst(bst_node_t* node) {
    if(!node) {
        return;
    }

    _delete_bst(node->left);
    _delete_bst(node->right);

    free(node);
}

void delete_bst(bst_t* bst) {
    _delete_bst(bst->root);
}

// Function to create a new BST node
bst_node_t* new_node(uint32_t value) {
    bst_node_t* temp = (bst_node_t*)malloc(sizeof(bst_node_t));
    temp->value = value;
    temp->left  = NULL;
    temp->right = NULL;
    return temp;
}

// Function to insert a new node with the given value
bst_node_t* _insert_node(bst_node_t* node, int value) {

    // If the tree is empty, return a new node
    if (node == NULL)
        return new_node(value);

    // If the value is already present in the tree,
    // return the node
    if (node->value == value)
        return node;

    // Otherwise, recur down the tree. If the value
    // to be inserted is greater than the node's value,
    // insert it in the right subtree
    if (node->value < value)
        node->right = _insert_node(node->right, value);

    // If the value to be inserted is smaller than
    // the node's value,insert it in the left subtree
    else
        node->left = _insert_node(node->left, value);

    // Return the (unchanged) node pointer
    return node;
}

void insert_node(bst_t* bst, uint32_t value) {
    bst->root = _insert_node(bst->root, value);
}

// Note that it is not a generic inorder successor
// function. It mainly works when the right child
// is not empty, which is  the case we need in
// BST delete.
bst_node_t* _get_successor(bst_node_t* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

// This function deletes a given value from the
// given BST and returns the modified root of
// the BST (if it is modified)
bst_node_t* _delete_node(bst_node_t* root, int value) {

    // Base case
    if (root == NULL)
        return root;

    // If value to be searched is in a subtree
    if (root->value > value)
        root->left = _delete_node(root->left, value);
    else if (root->value < value)
        root->right = _delete_node(root->right, value);
    else {
        // If root matches with the given value

        // Cases when root has 0 children or
        // only right child
        if (root->left == NULL) {
            bst_node_t* temp = root->right;
            free(root);
            return temp;
        }

        // When root has only left child
        if (root->right == NULL) {
            bst_node_t* temp = root->left;
            free(root);
            return temp;
        }

        // When both children are present
        bst_node_t* succ = _get_successor(root);
        root->value = succ->value;
        root->right = _delete_node(root->right, succ->value);
    }
    return root;
}

void delete_node(bst_t* bst, uint32_t value) {
    bst->root = _delete_node(bst->root, value);
}

bool _find_node(bst_node_t* node, int value) {
    if (node == NULL)
        return false;

    if (node->value == value)
        return true;

    if (node->value < value)
        return _find_node(node->right, value);
    else
        return _find_node(node->left, value);
}

void find_node(bst_t* bst, uint32_t value) {
    return _find_node(bst->root, value);
}

void _print_inorder(bst_node_t* node) {
    if (node == NULL)
        return;

    // Traverse left subtree
    _print_inorder(node->left);

    // Visit node
    printf("%d, ", node->value);

    // Traverse right subtree
    _print_inorder(node->right);
}

// Inorder Traversal
// left -> root -> right
void print_inorder(bst_t* bst) {
    printf("Print in-order: ");
    _print_inorder(bst->root);
    printf("\n");
}

void _print_preorder(bst_node_t* node) {
    if (node == NULL)
        return;

    // Visit node
    printf("%d, ", node->value);

    // Traverse left subtree
    _print_preorder(node->left);

    // Traverse right subtree
    _print_preorder(node->right);
}

// Preorder Traversal
// root -> left -> right
void print_preorder(bst_t* bst) {
    printf("Print pre-order: ");
    _print_preorder(bst->root);
    printf("\n");
}

void _print_postorder(bst_node_t* node) {
    if (node == NULL)
        return;

    // Traverse left subtree
    _print_postorder(node->left);

    // Traverse right subtree
    _print_postorder(node->right);

    // Visit node
    printf("%d, ", node->value);
}

// Postorder Traversal
// left -> right -> root
void print_postorder(bst_t* bst) {
    printf("Print post-order: ");
    _print_postorder(bst->root);
    printf("\n");
}

int main() {

    bst_t bst;
    bst_t* p_bst = &bst;

    create_bst(p_bst);

    insert_node(p_bst, 10);
    insert_node(p_bst, 5);
    insert_node(p_bst, 15);
    insert_node(p_bst, 12);
    insert_node(p_bst, 18);

    delete_node(p_bst, 15);

    print_inorder(p_bst);
    print_preorder(p_bst);
    print_postorder(p_bst);

    delete_bst(p_bst);

    return 0;
}
