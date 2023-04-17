//
// Created by davi on 12/04/23.
//

#include "skip_list.h"
#include "generator.h"

void assign_new_head(node_t* new_head, node_t** old_head) {
    new_head->down = *old_head;
    (*old_head)->top = new_head;
    *old_head = new_head;
}

node_t* create_node(int32_t key, u_int32_t height) {
    node_t* node = (node_t*) malloc(sizeof(node_t));
    node->key = key;
    node->height = height;
    node->next = NULL;
    node->top = NULL;
    node->down = NULL;
    return node;
}

void print_skip_list(node_t* head) {
    node_t* current = (node_t*) head;

    while (current) {
        node_t* level = current;

        while (level) {
            printf("%d(%d) -> ", level->height, level->key);
            level = level->next;
        }

        printf("NULL \n");
        current = current->down;
    }
}

node_t* find(int32_t key, node_t* head) {
    node_t* current = (node_t*) head;

    while (current != NULL) {
        if (current->key == key) {
            return current;
        } else if (current->next == NULL || current->next->key > key) {
            current = current->down;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

node_t* find_previous_by_key(int32_t key, u_int32_t node_height, node_t* head) {
    node_t* current = (node_t*) head;

    if (node_height > head->height) {
        return NULL;
    }

    while (current->height != node_height) {
        current = current->down;
    }

    while (current->next != NULL) {
        if (current->next->key > key) {
            return current;
        } else {
            current = current->next;
        }
    }

    return current;
}

node_t* find_previous(node_t* node, node_t* head) {
    node_t* current = (node_t*) head;

    while (current->height != node->height) {
        current = current->down;
    }

    while (current->next != NULL) {
        if (current->next == node) {
            return current;
        } else {
            current = current->next;
        }
    }

    return current;
}

node_t* find_next(int32_t key, u_int32_t node_height, node_t* head) {
    node_t* current = (node_t*) head;

    if (node_height > head->height) {
        return NULL;
    }

    while (current->height != node_height) {
        current = current->down;
    }

    while (current != NULL) {
        if (current->next == NULL) {
            return NULL;
        } else if (current->next->key > key) {
            return current->next;
        } else {
            current = current->next;
        }
    }

    return NULL;
}

node_t *promote(node_t* node, node_t **head) {
    node_t* top = create_node(node->key, node->height + 1);

    node->top = top;
    top->down = node;

    node_t* previous = find_previous_by_key(top->key, top->height, *head);
    node_t* next = find_next(top->key, top->height, *head);

    if (previous == NULL) {
        previous = create_node(-1, top->height);
        assign_new_head(previous, head);
    }

    previous->next = top;
    top->next = next;

    node = top;

    return node;
}

node_t* insert(int32_t key, node_t** head) {
    node_t* current = (node_t*) *head;

    while (current != NULL) {
        if (current->next != NULL && current->next->key < key) {
            current = current->next;
        } else if (current->down != NULL) {
            current = current->down;
        } else {
            node_t* node = create_node(key, current->height);
            node->next = current->next;
            current->next = node;

            u_int32_t coin = get_next() % 100;

            while (coin < 50) {
                printf("\tPROMOTED\n");
                node = promote(node, head);
                coin = get_next() % 100;
            }

            return node;
        }
    }

    return NULL;
}

void free_nodes(node_t* node) {
    while (node != NULL) {
        node_t* down_node = node->down;
        while (down_node != NULL) {
            node_t* next_down_node = down_node->down;
            free(down_node);
            down_node = next_down_node;
        }
        node_t* next_node = node->next;
        free(node);
        node = next_node;
    }
}

node_t* delete(int32_t key, node_t* head) {
    node_t* current = (node_t*) find(key, head);

    while (current != NULL) {
        node_t* previous = find_previous(current, head);
        previous->next = current->next;
        node_t* down = current->down;
        free(current);
        current = down;
    }

    return (node_t*) head;
}