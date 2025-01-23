#include <iostream>

void exampleFunction() {
    int fixedStackDynamicArr[5] = {1,2,3,4,5};
}

int main() {
    // Static array
    int staticArray[5] = {1,2,3,4,5};
    
    // Fixed stack-dynamic array
    exampleFunction();
    
    // Fixed heap-dynamic array
    const int SIZE = 5;
    int* arr = new int[SIZE]{1, 2, 3, 4, 5};

    // Heap-dynamic array
    // Request size from user
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    int *intArray = new int[size];
    
    delete[] intArray;
    intArray = nullptr;
    delete[] arr;
    arr = nullptr;
    
    return 0;
}