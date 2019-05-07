#include <algorithm>
#include <cstdio>
#include <iostream>

#include "test.h"

void partition(int* A, size_t size, size_t index) {
    int pivot = A[index];
    int steps = 0;
    for (int i=0; i < size; i++) {
        for (int j=i; j<size; j++) {
            steps++;
            if (A[j] < pivot) {
                // printf("A[%d]: %d, A[%d]: %d\n", i, A[i], j, A[j]);
                std::swap(A[i], A[j]);
                break;
            }
        }
    }
    printf("smaller-than partition: %d steps\n", steps);

    steps = 0;
    for (int i=(size - 1); i >= 0 and A[i] >= pivot; i--) {
        for (int j=(i - 1); j >= 0 and A[j] >= pivot; j--) {
            steps++;
            if (A[j] > pivot) {
                // printf("A[%d]: %d, A[%d]: %d\n", i, A[i], j, A[j]);
                std::swap(A[i], A[j]);
                break;
            }
        }
    }
    printf("larger-than partition: %d steps\n", steps);
}

void partitionOnePass(int* A, size_t size, size_t index) {
    int pivot = A[index];
    int steps = 0;
    int i = 0;
    for (int j=1; j<size;) {
        steps++;
        if (A[j] < pivot) {
            // printf("A[%d]: %d, A[%d]: %d\n", i, A[i], j, A[j]);
            std::swap(A[i], A[j]);
            if (i < j) i++;
            if (A[j] >= pivot or i==j) j++;
        } else {
            j++;
        }
    }
    printf("smaller-than partition: %d steps\n", steps);

    i = size - 1;
    for (int j=(i - 1); j >= 0 and A[j] >= pivot;) {
        steps++;
        if (A[j] > pivot) {
            // printf("A[%d]: %d, A[%d]: %d\n", i, A[i], j, A[j]);
            std::swap(A[i], A[j]);
            if (i > j) i--;
            if (A[j] <= pivot or i==j) j--;
        } else {
            j--;
        }
    }
    printf("larger-than partition: %d steps\n", steps);
}

/**
 * experimental, doesn't work
 */
void partitionFast(int* A, size_t size, size_t index) {
    int pivot = A[index];
    int steps = 0;
    size_t start = 0;
    size_t end = size - 1;
    for (int i=0; i<size; i++) {
        steps++;
        if (A[i] < pivot) {
            printf("A[%d]: %d, A[start:%lu]: %d\n", i, A[i], start, A[start]);
            std::swap(A[i], A[start]);
            start++;
        } else if (A[i] > pivot) {
            printf("A[%d]: %d, A[end:%lu]: %d\n", i, A[i], end, A[end]);
            std::swap(A[i], A[end]);
            end--;
        }
    }
    printf("fast partition: %d steps\n", steps);
}

void printArr(int* A, size_t size) {
    if (size > 0) std::cout << A[0];
    for (size_t i=1; i < size; i++) {
        std::cout << ", "  << A[i];
    }
    std::cout << '\n';
}

void doPartition(int* A, size_t size, size_t index) {
    std::cout << "The unpartitioned array is:\n";
    printArr(A, size);
    std::cout << "The pivot A[" << index << "] is: " << A[index] << '\n';

    // partition(A, size, index);
    partitionOnePass(A, size, index);
    // partitionFast(A, size, index);

    std::cout << "The partitioned array is:\n";
    printArr(A, size);
    std::cout << '\n';
}

int main() {
    int A[] = {4, 87, 53, 71, 28, 24, 8, 46, 5, 69, 61, 36, 15, 37, 68, 54, 27, 89, 64, 10, 97, 38, 11, 85, 42, 78, 33, 13, 32, 77, 57, 25, 96, 9, 93, 22, 52, 43, 88, 3, 75, 56, 35, 67, 79, 92, 94, 18, 26, 72, 40, 86, 91, 65, 60, 84, 45, 24, 1, 41, 2, 31, 21, 95, 66, 29, 39, 47, 73, 6, 55, 99, 76, 12, 19, 83, 58, 17, 59, 30, 44, 34, 49, 50, 23, 62, 16, 98, 48, 74, 80, 20, 24, 82, 14, 63, 90, 51, 70, 7, 81, 0};
    size_t sizeA = sizeof(A)/sizeof(A[0]);
    doPartition(A, sizeA, 57);
    ASSERT_PARTITION(A, 24, 24, 3, 75);

    int B[] = {49, 33, 71, 72, 97, 10, 22, 77, 6, 37, 97, 97, 90, 57, 52, 42, 53, 7, 18, 66, 97, 17, 43, 80, 45, 41, 62, 25, 14, 34, 70, 9, 94, 3, 67, 30, 48, 93, 78, 89, 0, 32, 58, 4, 95, 74, 64, 29, 11, 38, 50, 69, 27, 61, 82, 56, 24, 55, 13, 36, 65, 91, 12, 75, 44, 8, 16, 73, 68, 83, 40, 28, 85, 2, 84, 63, 51, 60, 46, 23, 26, 31, 5, 19, 54, 81, 1, 79, 47, 87, 86, 76, 99, 59, 39, 20, 92, 15, 35, 88, 96, 97, 98, 21};
    size_t sizeB = sizeof(B)/sizeof(B[0]);
    doPartition(B, sizeB, 4);
    ASSERT_PARTITION(B, 97, 97, 5, 2);

    int C[] = {90, 25, 94, 33, 22, 75, 77, 99, 17, 15, 96, 38, 8, 48, 77, 2, 9, 77, 40, 93, 46, 26, 60, 80, 97, 23, 88, 54, 85, 87, 6, 39, 57, 58, 61, 4, 20, 47, 74, 28, 89, 95, 77, 92, 42, 21, 69, 36, 68, 37, 67, 77, 56, 53, 13, 78, 29, 71, 3, 5, 10, 83, 35, 91, 30, 77, 49, 52, 27, 65, 12, 55, 63, 84, 62, 82, 19, 50, 24, 34, 43, 14, 1, 59, 64, 16, 98, 0, 11, 44, 45, 81, 18, 72, 7, 86, 51, 41, 66, 32, 77, 31, 73, 76, 70, 79};
    size_t sizeC = sizeof(C)/sizeof(C[0]);
    doPartition(C, sizeC, 6);
    ASSERT_PARTITION(C, 77, 77, 7, 22);

    int D[] = {86, 37, 55, 43, 83, 73, 68, 61, 5, 31, 25, 33, 60, 41, 41, 58, 41, 9, 92, 79, 36, 98, 84, 49, 11, 21, 7, 3, 34, 44, 8, 94, 59, 20, 89, 56, 39, 91, 29, 78, 85, 45, 57, 47, 82, 6, 65, 74, 40, 23, 16, 90, 87, 17, 26, 52, 71, 81, 46, 69, 95, 41, 28, 54, 4, 22, 32, 77, 88, 62, 80, 27, 41, 41, 76, 50, 41, 30, 24, 99, 53, 35, 14, 41, 38, 41, 64, 97, 72, 1, 19, 66, 18, 48, 10, 67, 13, 63, 42, 2, 70, 15, 96, 51, 0, 12, 41, 75, 93};
    size_t sizeD = sizeof(D)/sizeof(D[0]);
    doPartition(D, sizeD, 13);
    ASSERT_PARTITION(D, 41, 41, 10, 58);
};
