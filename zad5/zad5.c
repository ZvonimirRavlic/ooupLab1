//
// Created by Zvonimir Ravlic on 3/14/2023.
//
#include <stdio.h>
#include <stdlib.h>

typedef int __cdecl (*pfun)();

struct B {
    pfun *table;
};

typedef int __cdecl (*PTRFUN)(struct B *, int);

pfun bFunctions[2] = {NULL, NULL};

int __cdecl prva() {
    return 42;
}

int __cdecl druga(struct B *b, int x) {
    int i = b->table[0]() + x;
    return i;
}

struct D {
    PTRFUN *table;
};

pfun dFunctions[2] = {&prva, &druga};

struct D *newD() {
    struct D *d = malloc(sizeof(struct D));
    d->table = dFunctions;
    return d;
}

void funkcija(struct B *b) {
    PTRFUN p = (int (*)(struct B *, int)) (b->table[1]);
    printf("Prva: %d\n", b->table[0]());
    printf("Druga: %d\n", p(b, 12));
}

int main() {
    struct B *b = (struct B *) newD();
    funkcija(b);
}