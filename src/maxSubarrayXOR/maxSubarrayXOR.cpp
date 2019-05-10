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

std::vector<int> maxSubarrayXOR(const std::vector<int>& arr) {
    int max = 0;
    typename std::vector<int>::const_iterator maxStart;
    int maxLen = 0;

    for (int i=1; i < arr.size() + 1; i++) {
        for (auto it = arr.begin(); (it + i -1) != arr.end(); it++) {
            int acc = std::accumulate(it, it+i, 0, std::bit_xor<>());
            if (acc > max) {
                max = acc;
                maxStart = it;
                maxLen = i;
            }
        }
    }
    return std::vector<int>(maxStart, maxStart+maxLen);
}

int main() {
    printArr(maxSubarrayXOR({3, 9, 4, 12, 7}));
    printArr(maxSubarrayXOR({11, 2, 5, 3, 16, 8}));
    printArr(maxSubarrayXOR({5, 18, 10, 7, 14, 3}));
}
