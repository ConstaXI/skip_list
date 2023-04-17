//
// Created by davi on 14/04/23.
//

#include "generator.h"

int count = 0;

u_int32_t prev;
u_int32_t seed = 0;

const u_int32_t a = 1664525;
const u_int32_t c = 1013904223;

void set_seed(u_int32_t s) {
    seed = s;
}

u_int32_t get_next() {
    if (count == 0) {
        prev = seed;
        count++;
        return seed;
    }
    count++;
    u_int32_t val = (a * prev + c);
    prev = val;
    return val;
}
