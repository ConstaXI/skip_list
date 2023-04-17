//
// Created by davi on 12/04/23.
//

#ifndef SKIP_LIST_SKIP_LIST_H
#define SKIP_LIST_SKIP_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct node_t {
    int32_t key;
    u_int32_t height;
    struct node_t *next;
    struct node_t *top;
    struct node_t *down;
} node_t;

node_t* create_node(int32_t key, u_int32_t height);

void free_nodes(node_t* node);

void print_skip_list(node_t* node);

node_t* insert(int32_t key, node_t** node);

node_t* delete(int32_t key, node_t* node);

node_t* find(int32_t key, node_t* node);

#endif //SKIP_LIST_SKIP_LIST_H
