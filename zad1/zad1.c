//
// Created by Zvonimir Ravlic on 3/12/2023.
//
#include <stdio.h>
#include <stdlib.h>

typedef char const *(*PTRFUN)();

char const *dogGreet(void) {
    return "vau!";
}

char const *dogMenu(void) {
    return "kuhanu govedinu";
}

char const *catGreet(void) {
    return "mijau!";
}

char const *catMenu(void) {
    return "konzerviranu tunjevinu";
}

PTRFUN dogFunctions[2] = {&dogGreet, &dogMenu};
PTRFUN catFunctions[2] = {&catGreet, &catMenu};

struct Animal {
    PTRFUN *table;
    char const *name;
};

struct Dog {
    PTRFUN *table;
    char const *name;
};

struct Cat {
    PTRFUN *table;
    char const *name;
};

void animalPrintGreeting(struct Animal *animal) {
    printf("%s pozdravlja: %s\n", animal->name, animal->table[0]());
}

void animalPrintMenu(struct Animal *animal) {
    printf("%s voli %s\n", animal->name, animal->table[1]());
}

void constructDog(struct Dog *dog, char *pocetnoIme) {
    dog->name = pocetnoIme;
    dog->table = dogFunctions;
}

void constructCat(struct Cat *cat, char *pocetnoIme) {
    //mozda malloc i tu nisam siguran triba pogledat jos
    cat->name = pocetnoIme;
    // i tu
    cat->table = catFunctions;
}

struct Dog *createDog(char *pocetnoIme) {
    //struct Dog *dog; //i uklonitit free sa dna programa
    struct Dog *dog = (struct Dog *) malloc(sizeof(struct Dog));
    constructDog(dog, pocetnoIme);
    return dog;
}

struct Cat *createCat(char *pocetnoIme) {
    //struct Cat *cat; //i uklonitit free sa dna programa
    struct Cat *cat = (struct Cat *) malloc(sizeof(struct Cat));
    constructCat(cat, pocetnoIme);
    return cat;
}

void createNDogs(int n) {
    struct Dog *dogs = malloc(n * sizeof(struct Dog));
    int countDigs = 0;
    for (int i = 0; i < n; i++) {
        int num = i;
        do {
            countDigs++;
            num /= 10;
        } while (num != 0);
        countDigs++;
    }
    char int_str[countDigs];
    int count = 0;
    for (int i = 0; i < n; i++) {
        int num = i;
        do {
            count++;
            num /= 10;
        } while (num != 0);
        count++;
        sprintf(int_str + count, "%d\0", i);
        dogs[i].name = int_str + count;
        dogs[i].table = dogFunctions;
    }
    for (int i = 0; i < n; i++) {
        animalPrintGreeting((struct Animal *) &dogs[i]);
    }
    free(dogs);
}

void testAnimals(void) {
    struct Animal *p1 = (struct Animal *) createDog("Hamlet");
    struct Animal *p2 = (struct Animal *) createCat("Ofelija");
    struct Animal *p3 = (struct Animal *) createDog("Polonije");

    animalPrintGreeting(p1);
    animalPrintGreeting(p2);
    animalPrintGreeting(p3);

    animalPrintMenu(p1);
    animalPrintMenu(p2);
    animalPrintMenu(p3);

    free(p1);
    free(p2);
    free(p3);
}

int main() {
    testAnimals();
    createNDogs(50);
    return 0;
}