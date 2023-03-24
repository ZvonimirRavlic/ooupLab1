//
// Created by Zvonimir Ravlic on 3/23/2023.
//
#include <stdio.h>

class CoolClass {
public:
    virtual void set(int x) { x_ = x; };

    virtual int get() { return x_; };
private:
    int x_;
};

class PlainOldClass {
public:
    void set(int x) { x_ = x; };

    int get() { return x_; };
private:
    int x_;
};

int main() {
    printf("%d\n", sizeof(CoolClass));
    printf("%d", sizeof(PlainOldClass));
}