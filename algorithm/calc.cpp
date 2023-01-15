#include <iostream>
#include <cstdlib>

double* impose(double *arr, int size, int *barr) {
    // Create new array size of asize
    double *narry = new double[size];
    // For element in arr
    for (int i = 0; i < size; i++) {
        // barry is 0, set element to 1
        if (barr[i] == 0) {
            narry[i] = 1;
        }
        // barry is 1, set element to arr
        else if (barr[i] == 1) {
            narry[i] = arr[i];
        }
        // barry is 2, set element to 1/arr
        else if (barr[i] == 2) {
            narry[i] = 1/arr[i];
        }
    }
    return narry;
}

int* increment(int *arr, int size) {
    // The array stores digits in base 3
    // We can increment the array by adding 1 to the first element
    arr[0]++;
    // If the first element is 3, we need to carry the 1 to the next element
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == 3) {
            arr[i] = 0;
            arr[i+1]++;
        }
    }
    if (arr[size - 1] == 3) {
        // New array just [-1]
        int *narr = new int[1];
        narr[0] = -1;
        return narr;
    }
    return arr;
}

int* increment(int *arr, int size, int b) {
    // The array stores digits in base b
    // Increment the array by adding 1 to the first element
    arr[0]++;
    // If the first element is b, we need to carry the 1 to the next element
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] == b) {
            arr[i] = 0;
            arr[i+1]++;
        }
    }
    if (arr[size - 1] == b) {
        // New array just [-1]
        int *narr = new int[1];
        narr[0] = -1;
        return narr;
    }
    return arr;
}

double grade(double *arr, int size, double g) {
    double loss = 999;
    // Create arrays of the perumutations, but the doubles can also be the reciprocals
    // For each element it can be in 3 states: exists, doesn't exist, or is a reciprocal
    int* state = new int[size];
    // Set all elements to 0
    for (int i = 0; i < size; i++) {
        state[i] = 0;
    }
    while (state[0] != -1) {
        double *narr = impose(arr, size, state);
        // Multiply all elements together
        double product = 1;
        for (int i = 0; i < size; i++) {
            product *= narr[i];
        }
        // get diff squared
        double diff = g - product;
        diff *= diff;

        if (diff < loss) {
            loss = diff;
        }

        delete[] narr;

        // increment
        state = increment(state, size);
    }
    delete[] state;

    return loss;
}

double* grade(double *arr, int size, double g, bool yay) {
    double loss = 999;
    // Create arrays of the perumutations, but the doubles can also be the reciprocals
    // For each element it can be in 3 states: exists, doesn't exist, or is a reciprocal
    double* king = new double[size];
    int* state = new int[size];
    // Set all elements to 0
    for (int i = 0; i < size; i++) {
        state[i] = 0;
    }
    while (state[0] != -1) {
        double *narr = impose(arr, size, state);
        // Multiply all elements together
        double product = 1;
        for (int i = 0; i < size; i++) {
            product *= narr[i];
        }
        // get diff squared
        double diff = g - product;
        diff *= diff;

        if (diff < loss) {
            king = narr;
            loss = diff;
        }

        delete[] narr;

        // increment
        state = increment(state, size);
    }
    delete[] state;

    return king;
}

double fitness(double *arr, int size, int g_start, int g_end, double g_step) {
    double total = 0;
    int count = 0;
    for (double i = g_start; i < g_end; i += g_step) {
        double loss = grade(arr, size, i);
        total += loss;
        count++;
    }
    return total / count;
}

int* calc(int free, double presision) {
    // Regionals Preset
    int g_start = 10;
    int g_end = 30;
    double g_step = 1;
    // Create int array with free size
    int *arr = new int[free];
    // Populate with 0
    for (int i = 0; i < free; i++) {
        arr[i] = 0;
    }
    // array of the best fitnesses
    int *best = new int[free];
    double loss = 999;
    // While incrementing the array doesn't return [-1]
    int count = 0;
    while (arr[0] != -1) {
        double* raw = new double[free];
        for (int i = 0; i < free; i++) {
            raw[i] = 0.1 + arr[i] * presision;
        }
        double f = fitness(raw, free, g_start, g_end, g_step);
        // std::cout << "Loss of " << f << " for ";
        // for (int i = 0; i < free; i++) {
        //     std::cout << raw[i] << " ";
        // }
        // std::cout << std::endl;
        if (f < loss) {
            loss = f;
            best = arr;
            std::cout << "New Best: " << loss << std::endl;
            // Print out raw
            for (int i = 0; i < free; i++) {
                std::cout << raw[i] << " ";
            }
        }
        arr = increment(arr, free, 50);
        count++;

        // Heartbeat for every 5000 iterations
        if (count % 5000 == 0) {
            std::cout << "Checked " << count << " combinations" << std::endl;
            std::cout << "Best Loss: " << loss << std::endl;
        }

        delete[] raw;
    }
    std::cout << "Checked " << count << " combinations" << std::endl;
    std::cout << "Best Loss: " << loss << std::endl;
    return best;
}