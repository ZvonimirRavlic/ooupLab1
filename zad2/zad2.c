//
// Created by Zvonimir Ravlic on 3/13/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef double (*PTRFUN)();

struct UnaryFunction {
    PTRFUN *table;
    int lower_bound;
    int upper_bound;
};

struct UnaryFunction *UnaryFunction(int lb, int ub) {
    struct UnaryFunction *unaryFunction = (struct UnaryFunction *) malloc(sizeof(struct UnaryFunction));
    unaryFunction->lower_bound = lb;
    unaryFunction->upper_bound = ub;
}

double negative_value_at(struct UnaryFunction *unaryFunction, double x) {
    return -(unaryFunction->table[0](unaryFunction, x));
}

void tabulate(struct UnaryFunction *unaryFunction) {
    for (int x = unaryFunction->lower_bound; x <= unaryFunction->upper_bound; x++) {
        printf("f(%d)=%lf\n", x, (unaryFunction->table[0](unaryFunction, (double )x)));
    }
}

static bool same_functions_for_ints(struct UnaryFunction *f1, struct UnaryFunction *f2, double tolerance) {
    if (f1->lower_bound != f2->lower_bound) return false;
    if (f1->upper_bound != f2->upper_bound) return false;
    for (int x = f1->lower_bound; x <= f1->upper_bound; x++) {
        double delta = (f1->table[0](f1, x)) - (f2->table[0](f2, x));
        if (delta < 0) delta = -delta;
        if (delta > tolerance) return false;
    }
    return true;
}

PTRFUN unaryFunctions[2] = {NULL, &negative_value_at};

struct UnaryFunction *newUnaryFunction(int lb, int ub) {
    struct UnaryFunction *unaryFunction = (struct UnaryFunction *) malloc(sizeof(struct UnaryFunction));
    unaryFunction->table = unaryFunctions;
    unaryFunction->lower_bound = lb;
    unaryFunction->upper_bound = ub;
}

struct Square {
    PTRFUN *table;
    int lower_bound;
    int upper_bound;
};

double squareValueAt(struct Square *square, double x) {
    return x * x;
}

PTRFUN squareFunctions[2] = {&squareValueAt, &negative_value_at};

struct Square *newSquare(int lb, int ub) {
    struct Square *square = (struct Square *) malloc(sizeof(struct Square));
    square->table = squareFunctions;
    square->lower_bound = lb;
    square->upper_bound = ub;
}

struct Linear {
    PTRFUN *table;
    int lower_bound;
    int upper_bound;
    double a;
    double b;
};

double linearValueAt(struct Linear *linear, double x) {
    return linear->a * x + linear->b;
}

PTRFUN linearFunctions[2] = {&linearValueAt, &negative_value_at};

struct Linear *newLinear(int lb, int ub, double a_coef, double b_coef) {
    struct Linear *linear = (struct Linear *) malloc(sizeof(struct Linear));
    linear->table = linearFunctions;
    //mozda malloc
    linear->lower_bound = lb;
    linear->upper_bound = ub;
    linear->a = a_coef;
    linear->b = b_coef;
}

int main() {
    struct UnaryFunction *f1 = (struct UnaryFunction *) newSquare(-2, 2);
    tabulate(f1);
    struct UnaryFunction *f2 = (struct UnaryFunction *) newLinear(-2, 2, 5, -2);
    tabulate(f2);
    printf("f1==f2: %s\n", same_functions_for_ints(f1, f2, 1E-6) ? "DA" : "NE");
    printf("neg_val f2(1) = %lf\n", negative_value_at(f2, 1.0));
    free(f1);
    free(f2);
    return 0;
}