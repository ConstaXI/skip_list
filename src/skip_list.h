//
// Created by davi on 12/04/23.
//

#ifndef SKIP_LIST_SKIP_LIST_H
#define SKIP_LIST_SKIP_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct node_t {
    int key;
    int value;
    int height;
    struct node_t *next;
    struct node_t *top;
    struct node_t *down;
} node_t;

extern int MAX_HEIGHT;

void set_max_height(int height);

node_t* create_nodes();

void free_nodes(node_t* node);

void print_skip_list(const node_t* node);

const node_t* insert(int key, int value, const node_t* node);

node_t* delete(int key, const node_t* node);

node_t* find(int key, const node_t* node);

#endif //SKIP_LIST_SKIP_LIST_H
