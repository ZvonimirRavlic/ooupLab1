#include <stdio.h>
#include <stdlib.h>

typedef char const* (*PTRFUN)();

struct UnaryFunction {
    PTRFUN* table;
    int lower_bound;
    int upper_bound;
};

struct UnaryFunction* UnaryFunction(int lb, int ub) {
    struct UnaryFunction* unaryFunction = (struct UnaryFunction*)malloc(sizeof(struct UnaryFunction));
    unaryFunction->lower_bound = lb;
    unaryFunction->upper_bound = ub;
}

void tabulate(struct UnaryFunction* unaryFunction) {
    
}

int main() {
    Unary_Function* f1 = new Square(-2, 2);
    f1->tabulate();
    Unary_Function* f2 = new Linear(-2, 2, 5, -2);
    f2->tabulate();
    printf("f1==f2: %s\n", Unary_Function::same_functions_for_ints(f1, f2, 1E-6) ? "DA" : "NE");
    printf("neg_val f2(1) = %lf\n", f2->negative_value_at(1.0));
    delete f1;
    delete f2;
    return 0;
}