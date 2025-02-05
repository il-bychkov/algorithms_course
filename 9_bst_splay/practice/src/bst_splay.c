#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ported from
// https://habr.com/ru/companies/JetBrains-education/articles/210296/

typedef struct bst_node {
    uint32_t value;
    struct bst_node* left;
    struct bst_node* right;
    struct bst_node* parent;
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
bst_node_t* new_node(uint32_t value, bst_node_t* parent) {
    bst_node_t* temp = (bst_node_t*)malloc(sizeof(bst_node_t));
    temp->value = value;
    temp->left  = NULL;
    temp->right = NULL;
    temp->parent = parent;
    return temp;
}

// Utility functions

void set_parent(bst_node_t* current, bst_node_t* parent) {
    if(!current) {
        return;
    }

    current->parent = parent;
}

void keep_parent(bst_node_t* current) {
    set_parent(current->left, current);
    set_parent(current->right, current);
}

void rotate(bst_node_t* parent, bst_node_t* child) {
    if(!parent) {
        return;
    }

    bst_node_t* gparent = parent->parent;

    if (gparent) {
        if (gparent->left == parent) {
            gparent->left = child;
        } else {
            gparent->right = child;
        }
    }

    if (parent->left == child) {
        parent->left = child->right;
        child->right = parent;
    } else {
        parent->right = child->left;
        child->left = parent;
    }

}

bst_node_t* splay(bst_node_t* node) {
    if(!node->parent) {
        return node;
    }

    bst_node_t* parent = node->parent;
    bst_node_t* gparent = parent->parent;

    if(!gparent) {
        rotate(parent, node);
        return node;
    } else {
        bool zigzig = (gparent->left == parent) && (parent->left == node);

        if(zigzig) {
            rotate(gparent, parent);
            rotate(parent, node);
        } else { // zigzag
            rotate(parent, node);
            rotate(gparent, node);
        }

        return splay(node);
    }
}

bst_node_t* _find_node(bst_node_t* node, uint32_t value) {
    if (node == NULL)
        return node;

    if (node->value == value)
        return splay(node);

    if (node->value < value && node->right)
        return _find_node(node->right, value);
    else if(node->value > value && node->left)
        return _find_node(node->left, value);

    return splay(node);
}

bool find_node(bst_t* bst, uint32_t value) {
    return _find_node(bst->root, value) != NULL;
}

void split(bst_node_t* root, uint32_t value, bst_node_t** left, bst_node_t** right) {
    if(root == NULL) {
        *left = NULL;
        *right = NULL;
        return;
    }

    root = _find_node(root, value);

    if(root->value == value) {
        set_parent(root->left, NULL);
        set_parent(root->right, NULL);

        *left = root->left;
        *right = root->right;
        free(root);
        return;
    }

    if (root->value < value) {
        bst_node_t* mew_right = root->right;
        root->right = NULL;
        set_parent(mew_right, NULL);

        *left = root;
        *right = mew_right;
        return;
    } else {
        bst_node_t* mew_left = root->left;
        root->left = NULL;
        set_parent(mew_left, NULL);

        *left = mew_left;
        *right = root;
    }

}

void insert_node(bst_t* bst, uint32_t value) {
    bst_node_t* left;
    bst_node_t* right;

    split(bst->root, value, &left, &right);

    bst->root = new_node(value, NULL);

    bst->root->left = left;
    bst->root->right = right;

    keep_parent(bst->root);
}

bst_node_t* merge(bst_node_t* left, bst_node_t* right) {
    if(!left) {
        return right;
    }

    if(!right) {
        return left;
    }

    bst_node_t* new_root = _find_node(right, left->value);

    new_root->left = left;
    left->parent = new_root;

    return new_root;
}

void delete_node(bst_t* bst, uint32_t value) {
    bst_node_t* root = _find_node(bst->root, value);

    set_parent(root->left, NULL);
    set_parent(root->right, NULL);

    bst_node_t* new_root = merge(root->left, root->right);
    free(root);

    bst->root = new_root;
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
