#include <stdio.h>
#include <stdlib.h>

typedef char const* (*PTRFUN)();

char const* dogGreet(void) {
    return "vau!";
}
char const* dogMenu(void) {
    return "kuhanu govedinu";
}
char const* catGreet(void) {
    return "mijau!";
}
char const* catMenu(void) {
    return "konzerviranu tunjevinu";
}

PTRFUN dogFunctions[2] = { dogGreet, dogMenu };
PTRFUN catFunctions[2] = { catGreet, catMenu };

struct Animal {
    char const* name;
    PTRFUN* table;
};

void animalPrintGreeting(struct Animal* animal) {
    printf("%s pozdravlja: %s\n", animal->name, animal->table[0]());
}

void animalPrintMenu(struct Animal* animal) {
    printf("%s voli %s\n", animal->name, animal->table[1]());
}

void constructDog(struct Animal* dog, char* pocetnoIme) {
    dog->name = pocetnoIme;
    dog->table = dogFunctions;
}

void constructCat(struct Animal* cat, char* pocetnoIme) {
    //mozda malloc i tu nisam siguran triba pogledat jos
    cat->name = pocetnoIme;
    // i tu
    cat->table = catFunctions;
}

struct Animal* createDog(char* pocetnoIme) {
    struct Animal* dog = (struct Animal*)malloc(sizeof(struct Animal));
    constructDog(dog, pocetnoIme);
    return dog;
}

struct Animal* createCat(char* pocetnoIme) {
    struct Animal* cat = (struct Animal*)malloc(sizeof(struct Animal));
    constructCat(cat, pocetnoIme);
    return cat;
}

void createNDogs(int n) {
    struct Animal* dogs = malloc(n * sizeof(struct Animal));
    char int_str[n * 2];
    for (int i = 0; i < n; i++) {
        sprintf(int_str + i * 2 * sizeof(char), "%d\0", i);
        dogs[i].name = int_str + i * 2 * sizeof(char);
        dogs[i].table = dogFunctions;
    }
    for (int i = 0; i < n; i++) {
        animalPrintGreeting(&dogs[i]);
    }
    free(dogs);
}

void testAnimals(void) {
    struct Animal* p1 = createDog("Hamlet");
    struct Animal* p2 = createCat("Ofelija");
    struct Animal* p3 = createDog("Polonije");

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
    createNDogs(10);
    return 0;
}