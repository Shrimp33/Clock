#include <iostream>
#include <stdlib.h>
#include "calc.cpp"

int main() {
    int* best = calc(4, 0.1);
    for (int i = 0; i < 3; i++) {
        std::cout << best[i] << std::endl;
    }
    return 0;
}
