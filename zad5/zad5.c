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
    return (**(pfun **) (b))() + x;
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
    printf("Prva: %d\n", (**(pfun **) (b))());
    printf("Druga: %d\n",  (**((PTRFUN **) (b)) + 4)(b, 2));
}

int main() {
    struct B *b = (struct B *) newD();
    funkcija(b);
}