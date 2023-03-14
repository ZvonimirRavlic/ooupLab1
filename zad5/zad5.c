//
// Created by Zvonimir Ravlic on 3/14/2023.
//
#include <stdio.h>
#include <stdlib.h>

typedef int (*PTRFUN)();

struct B {
    PTRFUN *table;
};

PTRFUN bFunctions[2] = {NULL, NULL};

int __cdecl prva() {
    return 42;
}

int __cdecl druga(struct B *b, int x) {
    return b->table[0]() + x;
}

struct D {
    PTRFUN *table;
};

PTRFUN dFunctions[2] = {&prva, &druga};

struct D *newD() {
    struct D *d = malloc(sizeof(struct D));
    d->table = dFunctions;
    return d;
}

void funkcija(struct B *b) {
    printf("Prva: %d\n", b->table[0]());
    printf("Druga: %d\n", b->table[1](b, 58));
}

int main() {
    struct B *b = (struct B *) newD();
    funkcija(b);
}