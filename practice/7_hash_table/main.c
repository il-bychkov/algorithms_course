#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// this implementation is a C port of
// https://habr.com/ru/articles/509220/

#define VERBOSE

void print_string(const char* string) {
    for (size_t i = 0; i < strlen(string); i++) {
        printf("%c", string[i]);
    }
}

#ifdef VERBOSE

    static size_t depth = 0;
    static size_t current_line = 0;

    static bool verbose_enabled = false;

    #define PRINT_TABS() printf("[%4ld] >> ", current_line); current_line++; for (size_t i = 0; i < depth; i++) {printf("    ");}

    #define ENTER_FUNC(fname) if(verbose_enabled) { printf("[%4ld] >>\n", current_line); current_line++; PRINT_TABS(); depth++; printf("ENTER "); printf(fname); printf(" >>\n"); }
    #define EXIT_FUNC(fname) if(verbose_enabled) { depth--; PRINT_TABS(); printf("EXIT "); printf(fname); printf(" >>\n"); printf("[%4ld] >> \n", current_line); current_line++; }

    #define PRINT_VERBOSE(string) if(verbose_enabled) { PRINT_TABS(); printf(string); }
    #define PRINT_VERBOSE_ARGS(string, args) if(verbose_enabled) { PRINT_TABS(); printf(string, args); }

    #define PRINT_VERBOSE_STRING(comment, string) if(verbose_enabled) { PRINT_TABS(); printf(comment); print_string(string); printf("\n"); }

    #define ENABLE_VERBOSE() verbose_enabled = true; depth = 0; current_line = 0
    #define DISABLE_VERBOSE() verbose_enabled = false

#else

    #define PRINT_TABS()
    #define ENTER_FUNC(fname)
    #define EXIT_FUNC(fname)
    #define PRINT_VERBOSE(string)
    #define PRINT_VERBOSE_ARGS(string, args)
    #define PRINT_VERBOSE_STRING(comment, string)

    #define ENABLE_VERBOSE()
    #define DISABLE_VERBOSE()

#endif

size_t hashHorner(const char* string, const size_t table_size, const size_t key) {

    ENTER_FUNC("hashHorner");
    PRINT_VERBOSE_STRING("hashed string: ", string);
    PRINT_VERBOSE_ARGS("table_size: %ld\n", table_size);
    PRINT_VERBOSE_ARGS("key: %ld\n", key);

    size_t hash_result = 0;
    for (int i = 0; i != strlen(string); ++i)
        hash_result = (key * hash_result + string[i]) % table_size;
    hash_result = (hash_result * 2 + 1) % table_size;

    PRINT_VERBOSE_ARGS("hashing result: %ld\n", hash_result);
    EXIT_FUNC("hashHorner");

    return hash_result;
}

#define HASH_1(string, table_size) hashHorner(string, table_size, table_size - 1);
#define HASH_2(string, table_size) hashHorner(string, table_size, table_size + 1);

typedef struct node {
    char* key;
    size_t value;
    bool state;
} node_t;

typedef struct hash_table {
    double rehash_size;
    size_t size;
    size_t buffer_size;
    size_t size_all_non_nullptr;
    node_t** arr;
} hash_table_t;

node_t** new_nodes_arr(size_t size) {

    ENTER_FUNC("new_nodes_arr");
    PRINT_VERBOSE("new nodes array created\n");
    PRINT_VERBOSE_ARGS("size of array: %ld\n", size);

    node_t** arr = (node_t**)malloc(size * sizeof(node_t*));

    for (size_t i = 0; i < size; ++i) {
        arr[i] = NULL;
    }

    EXIT_FUNC("new_nodes_arr");

    return arr;
}

void new(hash_table_t* table) {
    table->buffer_size = 8;
    table->rehash_size = 0.75;
    table->size = 0;
    table->size_all_non_nullptr = 0;

    ENTER_FUNC("new");

    table->arr = new_nodes_arr(table->buffer_size);

    EXIT_FUNC("new");

}

void delete(hash_table_t* table) {

    ENTER_FUNC("delete");

    node_t** arr = table->arr;

    PRINT_VERBOSE_ARGS("size of array to clear: %ld\n", table->buffer_size);

    for (size_t i = 0; i < table->buffer_size; ++i) {
        if(arr[i]) {
            if(arr[i]->key && arr[i]->state) {
                free((void*)arr[i]->key);
                PRINT_VERBOSE_ARGS("free node key at index: %ld\n", i);
            }
            free(arr[i]);
            PRINT_VERBOSE_ARGS("free index: %ld\n", i);
        }
    }
    free(arr);

    EXIT_FUNC("delete");

}

void table_dump(hash_table_t* table) {
    ENTER_FUNC("table_dump");

    node_t** arr = table->arr;
    size_t size = table->buffer_size;

    for (size_t i = 0; i < size; i++)
    {
        printf("TD >> index %ld: ", i);
        if(arr[i] == NULL) {
            printf("NULL\n");
        } else if (arr[i]->state){
            printf(" active node\n");
            printf("TD >>    key: ");
            print_string(arr[i]->key);
            printf("\nTD >>    value: %ld\n", arr[i]->value);
        } else {
            printf(" deleted node\n");
        }
    }



    EXIT_FUNC("table_dump");
}

void update_node_value(node_t* node, char* key, size_t value) {

    ENTER_FUNC("update_node_value");
    PRINT_VERBOSE_STRING("key: ", key);
    PRINT_VERBOSE_ARGS("value: %ld\n", value);

    node->key = malloc(sizeof(char) * (strlen(key) + 1));
    memcpy((void*)node->key, key, strlen(key));
    node->key[strlen(key)] = 0;

    node->value = value;
    node->state = true;

    EXIT_FUNC("update_node_value");
}

bool _add(hash_table_t* table, char* key, size_t value) {
    ENTER_FUNC("_add");

    size_t h1 = HASH_1(key, table->buffer_size)
    size_t h2 = HASH_2(key, table->buffer_size)

    size_t i = 0;

    bool found_first_deleted = false;
    size_t first_deleted = 0;

    node_t** arr = table->arr;
    size_t buffer_size = table->buffer_size;

    PRINT_VERBOSE_ARGS("check index: %ld\n", h1);

    while (arr[h1] != NULL && i < buffer_size) {

        PRINT_VERBOSE("space is not empty, check satte and value\n");

        if (strcmp(arr[h1]->key, key) == 0 && arr[h1]->state) {
            PRINT_VERBOSE_ARGS("found same key at index: %ld\n", h1);
            EXIT_FUNC("add");
            return false;
        }

        if (!arr[h1]->state && found_first_deleted == false) {
            PRINT_VERBOSE_ARGS("found deleted node at index: %ld\n", h1);
            first_deleted = h1;
            found_first_deleted = true;
        }

        h1 = (h1 + h2) % buffer_size;
        PRINT_VERBOSE_ARGS("check index: %ld\n", h1);
        ++i;
    }

    if (found_first_deleted == false) {
        PRINT_VERBOSE_ARGS("found space to incert at index: %ld\n", h1);
        PRINT_VERBOSE("insert node to free space in buffer\n");

        node_t* new_node = (node_t*)malloc(sizeof(node_t));

        update_node_value(new_node, key, value);

        table->arr[h1] = new_node;
        table->size_all_non_nullptr++;
    } else {
        PRINT_VERBOSE_ARGS("found space to incert at index: %ld\n", first_deleted);
        PRINT_VERBOSE("insert node to instead of deleted node\n");

        update_node_value(arr[first_deleted], key, value);
    }

    table->size++;

    EXIT_FUNC("_add");

    return true;
}

void resize(hash_table_t* table) {

    ENTER_FUNC("resize");

    int past_buffer_size = table->buffer_size;
    table->buffer_size *= 2;
    table->size_all_non_nullptr = 0;
    table->size = 0;

    node_t** new_arr;
    new_arr = new_nodes_arr(table->buffer_size);

    node_t** old_arr;

    old_arr = table->arr;
    table->arr = new_arr;

    node_t** arr = table->arr;

    PRINT_VERBOSE_ARGS("new buffer size: %ld\n", table->buffer_size);

    for (size_t i = 0; i < past_buffer_size; ++i) {
        if (old_arr[i]) {
            if(old_arr[i]->state) {
                PRINT_VERBOSE_ARGS("add to new buffer element from index: %ld\n", i);
                _add(table, (char*)old_arr[i]->key, old_arr[i]->value);
                free((void*)old_arr[i]->key);
                free(old_arr[i]);
            } else {
                free(old_arr[i]);
                PRINT_VERBOSE_ARGS("free element at index: %ld\n", i);
            }
        }
    }

    free(old_arr);

    EXIT_FUNC("resize");
}

void rehash(hash_table_t* table) {
    table->size_all_non_nullptr = 0;
    table->size = 0;

    node_t** new_arr;
    new_arr = new_nodes_arr(table->buffer_size);

    node_t** old_arr;

    old_arr = table->arr;
    table->arr = new_arr;

    node_t** arr = table->arr;

    for (size_t i = 0; i < table->buffer_size; ++i) {
        if (old_arr[i]) {
            if(old_arr[i]->state) {
                PRINT_VERBOSE_ARGS("add to new buffer element from index: %ld\n", i);
                _add(table, (char*)old_arr[i]->key, old_arr[i]->value);
                free((void*)old_arr[i]->key);
                free(old_arr[i]);
            } else {
                free(old_arr[i]);
                PRINT_VERBOSE_ARGS("free element at index: %ld\n", i);
            }
        }
    }

    free(old_arr);
}

bool add(hash_table_t* table, char* key, size_t value) {

    ENTER_FUNC("add");

    PRINT_VERBOSE_STRING("key: ", key);
    PRINT_VERBOSE_ARGS("value: %ld\n", value);

    if (table->size + 1 > (size_t)(table->rehash_size * table->buffer_size)) {
        PRINT_VERBOSE_ARGS("next table size: %ld\n", table->size + 1);
        PRINT_VERBOSE_ARGS("size to rehash at: %ld\n", (size_t)(table->rehash_size * table->buffer_size));
        PRINT_VERBOSE("need to resize\n");
        resize(table);
    } else if (table->size_all_non_nullptr > 2 * table->size) {
        PRINT_VERBOSE_ARGS("size_all_non_nullptr: %ld\n", table->size_all_non_nullptr);
        PRINT_VERBOSE_ARGS("ssize: %ld\n", table->size);
        PRINT_VERBOSE("need to rehash\n");
        rehash(table);
    }

    return _add(table, key, value);

    EXIT_FUNC("add");

    return true;
}

// ht_ to avoid conflict
// /usr/include/stdio.h:146:12: note: previous declaration of ‘remove’ was here
bool ht_remove(hash_table_t* table, char* key) {
    ENTER_FUNC("remove");

    PRINT_VERBOSE_STRING("key: ", key);

    size_t h1 = HASH_1(key, table->buffer_size)
    size_t h2 = HASH_2(key, table->buffer_size)
    size_t i = 0;

    node_t** arr = table->arr;

    PRINT_VERBOSE_ARGS("check index: %ld\n", h1);

    while (arr[h1] != NULL && i < table->buffer_size)
    {
        if (strcmp(arr[h1]->key, key) == 0 && arr[h1]->state)
        {

            arr[h1]->state = false;
            free((void*)arr[h1]->key);
            table->size--;

            PRINT_VERBOSE_ARGS("remove element at index: %ld\n", h1);
            EXIT_FUNC("remove");
            return true;
        }

        PRINT_VERBOSE_ARGS("check index: %ld\n", h1);
        h1 = (h1 + h2) % table->buffer_size;
        ++i;
    }

    PRINT_VERBOSE("nothing to remove\n");
    EXIT_FUNC("remove");
    return false;
}

bool find(hash_table_t* table, char* key, size_t* value) {

        ENTER_FUNC("find");

        PRINT_VERBOSE_STRING("key: ", key);

        size_t h1 = HASH_1(key, table->buffer_size)
        size_t h2 = HASH_2(key, table->buffer_size)
        size_t i = 0;

        node_t** arr = table->arr;

        while (arr[h1] != NULL && i < table->buffer_size) {
            if (strcmp(arr[h1]->key, key) == 0 && arr[h1]->state) {

                PRINT_VERBOSE_ARGS("find element at index: %ld\n", h1);
                EXIT_FUNC("remove");
                *value = arr[h1]->value;
                return true;
            }
            h1 = (h1 + h2) % table->buffer_size;
            ++i;
        }

        PRINT_VERBOSE("can't find key\n");
        EXIT_FUNC("remove");
        return false;
}

int main() {

    PRINT_VERBOSE("start execution\n");

    hash_table_t table;
    hash_table_t* p_table = &table;

    new(p_table);

    ENABLE_VERBOSE();

    add(p_table, "foo", 12);
    add(p_table, "foo", 15);
    add(p_table, "bar", 15);

    table_dump(p_table);

    ht_remove(p_table, "bar");

    table_dump(p_table);

    add(p_table, "bar", 78);

    table_dump(p_table);

    size_t value_to_find;

    find(p_table, "foo", &value_to_find);

    DISABLE_VERBOSE();

    add(p_table, "el0", 15);
    add(p_table, "el1", 15);
    add(p_table, "el2", 15);
    add(p_table, "el3", 15);

    table_dump(p_table);

    ENABLE_VERBOSE();
    add(p_table, "el5", 15);
    DISABLE_VERBOSE();

    table_dump(p_table);

    add(p_table, "el4", 15);
    add(p_table, "el6", 15);
    add(p_table, "el7", 15);

    ht_remove(p_table, "el0");
    ht_remove(p_table, "el1");
    ht_remove(p_table, "el2");
    ht_remove(p_table, "el3");
    ht_remove(p_table, "el4");
    ht_remove(p_table, "el6");
    ht_remove(p_table, "el7");

    ENABLE_VERBOSE();

    add(p_table, "new_new", 15);

    find(p_table, "bar", &value_to_find);

    DISABLE_VERBOSE();

    table_dump(p_table);

    delete(p_table);

    PRINT_VERBOSE("end execution\n");

    return 0;
}
