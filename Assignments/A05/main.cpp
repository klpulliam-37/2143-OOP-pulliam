#include "MyVector.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    int A[] = {1, 2, 3, 4, 5, 6};    // array initialized with 1-6
    for (int i = 0; i < 6; i++) {
        std::cout << A[i];
    }

    // MyVector L(A, 6);                     // linked list built with array

    // L.Print();  // print the list

    return 0;
}