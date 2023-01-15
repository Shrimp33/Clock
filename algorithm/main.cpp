#include <iostream>
#include <stdlib.h>
#include "calc.cpp"

int main() {
    // int* best = calc(4, 0.1);
    // for (int i = 0; i < 3; i++) {
    //     std::cout << best[i] << std::endl;
    // }
    // return 0;
    double* arr = new double[4];
    arr[0] = 2.2;
    arr[1] = 1.3;
    arr[2] = 1.2;
    arr[3] = 0.1;
    while (true) {
        // Get input int
        int input;
        std::cout << "Enter a number: ";
        std::cin >> input;
        double* scores = grade(arr, 4, input, true);
        double score = grade(arr, 4, input);
        std::cout << "Loss: " << score << std::endl;
        std::cout << "Gears: ";
        for (int i = 0; i < 4; i++) {
            std::cout << scores[i] << " ";
        }
        std::cout << std::endl;
    }
}
