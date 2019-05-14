#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

template<class InputIt>
void printRange(InputIt start, InputIt end) {
    if (start != end) std::cout << *start++;
    for (; start != end; start++) std::cout << ", " << *start;
    std::cout << '\n';
}

template <typename T>
void printArr(const std::vector<T>& arr) {
    printRange(arr.begin(), arr.end());
}

template <typename T>
inline int tri(T n) {
    return n*(n+1)/2;
}

template <typename T>
inline int invtri(T ntri) {
    return -1.0/2 + sqrt(1.0/4 + 2*ntri);
}

std::vector<int> maxSubarrayXOR(const std::vector<int>& arr) {
    int max = 0;
    int maxStart = 0;
    int maxEnd = 0;

    // loop over the individual subarrays
    for (int i=0; i < tri(arr.size()); i++) {
        // use triangular numbers to determine the range of each subarray
        // std::cout << "i - tri(invtri(i)): " << i - tri(invtri(i)) << ", invtri(i) + 1: " << invtri(i) + 1 << '\n';
        int acc = std::accumulate(arr.begin() + i - tri(invtri(i)), arr.begin() + invtri(i) + 1, 0, std::bit_xor<>());
        if (acc > max) {
            max = acc;
            maxStart = i - tri(invtri(i));
            maxEnd = invtri(i) + 1;
        }
    }
    return std::vector<int>(arr.begin() + maxStart, arr.begin() + maxEnd);
}

int main() {
    printArr(maxSubarrayXOR({3, 9, 4, 12, 7}));
    printArr(maxSubarrayXOR({11, 2, 5, 3, 16, 8}));
    printArr(maxSubarrayXOR({5, 18, 10, 7, 14, 3}));
}
