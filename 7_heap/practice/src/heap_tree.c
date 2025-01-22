#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N_ITERATIONS 1000

typedef struct binary_tree_node {
    uint32_t value;
    struct binary_tree_node* left;
    struct binary_tree_node* right;
} binary_tree_node_t;

typedef struct binary_tree {
    binary_tree_node_t* root;
} binary_tree_t;

void create_tree(binary_tree_t* tree) {
    tree->root = NULL;
}

void _delete_tree(binary_tree_node_t* node) {
    if (node) {
        _delete_tree(node->left);
        _delete_tree(node->right);
        free(node);
    }
}

void delete_tree(binary_tree_t* tree) {
    _delete_tree(tree->root);
    tree->root = NULL;
}

// See details about DFS in <TBD>
void _print_traverse_inorder_dfs(const binary_tree_node_t* node) {
    if (node) {
        _print_traverse_inorder_dfs(node->left);
        printf("%d\n", node->value);
        _print_traverse_inorder_dfs(node->right);
    }
}

void print_traverse_inorder_dfs(const binary_tree_t* tree) {
    return _print_traverse_inorder_dfs(tree->root);
}

// list is used for elements addition
typedef struct linked_list_node {
    binary_tree_node_t* value;
    struct linked_list_node* next;
    struct linked_list_node* prev;
} linked_list_node_t;

typedef struct queue {
    struct linked_list_node* head;
    struct linked_list_node* tail;
} queue_t;

void new(queue_t* queue) {
    queue->head = NULL;
    queue->tail = NULL;
};

void delete(queue_t* queue) {
    linked_list_node_t* tail = queue->head;

    while (tail) {
        linked_list_node_t* current = tail;
        tail = tail->next;
        free(current);
    }
};

void flush(queue_t* queue) {
    delete(queue);
    new(queue);
}

void enqueue(queue_t* queue, binary_tree_node_t* value) {
    linked_list_node_t* head = queue->head;

    queue->head = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

    if (queue->tail == NULL)
    {
        queue->tail = queue->head;
    }

    if (head != NULL) {
        head->prev = queue->head;
    }

    queue->head->next = head;
    queue->head->prev = NULL;
    queue->head->value = value;
}

bool isEmpty(queue_t* queue) {
    return queue->head == NULL;
}

binary_tree_node_t* dequeue(queue_t* queue) {

    binary_tree_node_t* value = NULL;

    if(!isEmpty(queue)) {
        value = queue->tail->value;

        linked_list_node_t* new_tail = queue->tail->prev;

        if(new_tail) {
            new_tail->next == NULL;
        }

        if(queue->tail == queue->head) {
            queue->head = new_tail;
        }

        queue->tail = new_tail;
    }

    return value;
}

// note that this sunction does no heapify
void add_node(binary_tree_t* tree, uint32_t value) {

    if (!tree->root) {
        tree->root = (binary_tree_node_t*)malloc(sizeof(binary_tree_node_t));
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->root->value = value;

        return;
    }

    queue_t queue;
    queue_t* p_queue = &queue;

    new(p_queue);

    enqueue(p_queue, tree->root);

    while (!isEmpty(p_queue)) {
        binary_tree_node_t* node = dequeue(p_queue);

        if (node->left) {
            enqueue(p_queue, node->left);
        } else {
            node->left = (binary_tree_node_t*)malloc(sizeof(binary_tree_node_t));
            node->left->left = NULL;
            node->left->right = NULL;
            node->left->value = value;

            break;
        }

        if (node->right) {
            enqueue(p_queue, node->right);
        } else {
            node->right = (binary_tree_node_t*)malloc(sizeof(binary_tree_node_t));
            node->right->left = NULL;
            node->right->right = NULL;
            node->right->value = value;

            break;
        }

    }

    delete(p_queue);
}



bool _find_node(binary_tree_node_t* node, uint32_t value) {
    if (!node) {
        return false;
    } else if (node->value == value) {
        return true;
    }

    return _find_node(node->left, value) || _find_node(node->right, value);
}

bool find_node(binary_tree_t* tree, uint32_t value) {
    return _find_node(tree->root, value);
}

binary_tree_node_t* find_node_ptr(binary_tree_node_t* node, uint32_t value) {
    if (!node) {
        return NULL;
    } else if (node->value == value) {
        return node;
    }

    binary_tree_node_t* res_node = NULL;

    res_node = find_node_ptr(node->left, value);

    if(res_node) {
        return res_node;
    }

    return find_node_ptr(node->right, value);
}

binary_tree_node_t* find_first_with_leaf(binary_tree_node_t* node) {
    if (!node) {
        return NULL;
    } else {
        if (node->left && !node->left->left && !node->left->right) {
            return node;
        }

        if (node->right && !node->right->left && !node->right->right) {
            return node;
        }
    }

    binary_tree_node_t* res_node = NULL;

    res_node = find_first_with_leaf(node->left);

    if(res_node) {
        return res_node;
    }

    return find_first_with_leaf(node->right);
}

void delete_node(binary_tree_t* tree, uint32_t value) {
    binary_tree_node_t* node_to_replace_value = find_node_ptr(tree->root, value);

    if (!node_to_replace_value) {
        return;
    }

    if (node_to_replace_value == tree->root && !tree->root->left && !tree->root->right) {
        free(tree->root);
        tree->root = NULL;
        return;
    }

    binary_tree_node_t* node_with_leaf = find_first_with_leaf(tree->root);

    if (node_with_leaf->left && !node_with_leaf->left->left && !node_with_leaf->left->right) {
        node_to_replace_value->value = node_with_leaf->left->value;
        free(node_with_leaf->left);
        node_with_leaf->left = NULL;

        return;
    }

    if (node_with_leaf->right && !node_with_leaf->right->left && !node_with_leaf->right->right) {
        node_to_replace_value->value = node_with_leaf->right->value;
        free(node_with_leaf->right);
        node_with_leaf->right = NULL;

        return;
    }
}

void heapify_subtree(binary_tree_node_t* node) {

    if(!node) {
        return;
    }

    if(node->left == NULL && node->right == NULL) {
        return;
    }

    binary_tree_node_t* largest_node = node;

    if(node->left && node->left->value > largest_node->value) {
        largest_node = node->left;
    }

    if(node->right && node->right->value > largest_node->value) {
        largest_node = node->right;
    }

    if(largest_node == node) {
        return;
    } else {
        uint32_t tmp = largest_node->value;
        largest_node->value = node->value;
        node->value = tmp;

        heapify_subtree(largest_node);
    }
}

void _heapify(binary_tree_node_t* node) {
    if(!node) {
        return;
    }

    _heapify(node->left);
    _heapify(node->right);

    heapify_subtree(node);
}

void heapify(binary_tree_t* tree) {
    _heapify(tree->root);
}

uint32_t get_max(binary_tree_t* tree) {

    if(tree->root) {
        uint32_t max = tree->root->value;
        delete_node(tree, max);
        heapify_subtree(tree->root);
        return max;
    }

    return 0;
}

int main() {

    binary_tree_t tree;
    binary_tree_t* p_tree = &tree;

    create_tree(p_tree);

    add_node(p_tree, 1);
    add_node(p_tree, 2);
    add_node(p_tree, 3);
    add_node(p_tree, 44);
    add_node(p_tree, 5);
    add_node(p_tree, 100);
    add_node(p_tree, 7);
    add_node(p_tree, 88);
    add_node(p_tree, 9);
    add_node(p_tree, 10);

    heapify(p_tree);

    while (p_tree->root) {
        printf("%d\n", get_max(p_tree));
    }

    delete_tree(p_tree);

    clock_t t;
    double time_taken = 0;

    for (int n_exp = 0; n_exp < N_ITERATIONS; n_exp++) {

        create_tree(p_tree);

        t = clock();

        add_node(p_tree, 1);
        add_node(p_tree, 2);
        add_node(p_tree, 3);
        add_node(p_tree, 44);
        add_node(p_tree, 5);
        add_node(p_tree, 100);
        add_node(p_tree, 7);
        add_node(p_tree, 88);
        add_node(p_tree, 9);
        add_node(p_tree, 10);

        heapify(p_tree);

        t = clock() - t;

        delete_tree(p_tree);

        time_taken += ((double)t) / CLOCKS_PER_SEC;
    }

    printf("%d heap creations executed in %f seconds \n", N_ITERATIONS, time_taken);

    return 0;
}
