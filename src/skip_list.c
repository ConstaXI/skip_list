//
// Created by davi on 12/04/23.
//

#include "skip_list.h"

int MAX_HEIGHT = 3;

void set_max_height(int height) {
    MAX_HEIGHT = height;
}

node_t* create_node(int key, int value, int height) {
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->height = height;
    new_node->next = NULL;
    new_node->top = NULL;
    new_node->down = NULL;
    return new_node;
}

node_t* create_nodes() {
    node_t* head = create_node(0, 0, MAX_HEIGHT - 1);
    node_t* current = head;
    for (int i = head->height - 1; i >= 0; i--) {
        node_t* new_node = create_node(0, 0, i);
        current->down = new_node;
        new_node->top = current;
        current = new_node;
    }
    return head;
}

void print_skip_list(const node_t* head) {
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

node_t* find(int key, const node_t* head) {
    node_t* current = (node_t*) head;

    int interactions = 0;

    while (current != NULL) {
        if (current->key == key) {
            printf("Found %d in %d interactions\n", key, interactions);
            return current;
        } else if (current->next == NULL || current->next->key > key) {
            current = current->down;
        } else {
            current = current->next;
        }
        interactions++;
    }
    return NULL;
}

node_t* find_previous_by_key(int key, int node_height, const node_t* head) {
    node_t* current = (node_t*) head;

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

node_t* find_previous(node_t* node, const node_t* head) {
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

node_t* find_next(int key, int node_height, const node_t* head) {
    node_t* current = (node_t*) head;

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

int get_random() {
    srand(time(NULL) + rand());
    return rand() & 1;
}

node_t *promote(node_t* node, const node_t* head) {
    node_t* top = create_node(node->key, node->value, node->height + 1);

    node->top = top;
    top->down = node;

    node_t* previous = find_previous_by_key(top->key, top->height, head);
    node_t* next = find_next(top->key, top->height, head);

    previous->next = top;
    top->next = next;

    node = top;

    return node;
}

const node_t* insert(int key, int value, const node_t* head) {
    node_t* current = (node_t*) head;

    while (current != NULL) {
        if (current->next != NULL && current->next->key < key) {
            current = current->next;
        } else if (current->down != NULL) {
            current = current->down;
        } else {
            node_t* node = create_node(key, value, current->height);
            node->next = current->next;
            current->next = node;

            int coin = get_random();

            while (coin && node->height < MAX_HEIGHT - 1) {
                node = promote(node, head);
                coin = get_random();
            }

            return head;
        }
    }

    return head;
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

node_t* delete(int key, const node_t* head) {
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