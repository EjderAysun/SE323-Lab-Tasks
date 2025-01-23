#include <stdio.h>
#include <stdlib.h>

void exampleFunction() {
    int fixedStackDynamicArr[5] = {1,2,3,4,5};
}

int main() {
    // Static array
    int staticArray[5] = {1,2,3,4,5};

    // Fixed stack-dynamic array
    exampleFunction();
    
    // Fixed heap-dynamic array
    int *arr = (int *) malloc(20 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        free(arr);
        arr = NULL;
        return 1;
    }

    // Heap-dynamic array
    arr = (int *) realloc(arr, 45 * sizeof(int));
                          // size
    if (arr == NULL) {
        printf("Memory reallocation failed\n");
        free(arr);
        arr = NULL;
        return 1;
    }

    free(arr);
    return 0;
}