#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

template<typename InputIt>
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
void printSubArrs(const std::vector<std::vector<T>>& subArrs) {
    for (auto&& arr : subArrs) {
        printArr(arr);
    }
}

template <typename InputIt, typename T=typename std::iterator_traits<InputIt>::value_type>
void allSubarrays(InputIt begin, InputIt end, InputIt begin0, std::vector<std::vector<T>>& vv) {
    if (begin == end) {
        if (begin0 == end) {
            return;
        }
        return allSubarrays(begin0, --end, begin0, vv);
    }
    vv.emplace_back(begin++, end);
    return allSubarrays(begin, end, begin0, vv);
}

template <typename InputIt, typename T=typename std::iterator_traits<InputIt>::value_type>
auto allSubarrays(InputIt begin, InputIt end) {
    std::vector<std::vector<T>> vv;
    allSubarrays(begin, end, begin, vv);
    return vv;
}

std::vector<int> maxSubarrayXORRecursive(const std::vector<int>& arr) {
    int max = 0;
    int maxi = 0;

    auto vv = allSubarrays(arr.begin(), arr.end());
    // printSubArrs(vv);
    for (int i=0; i < vv.size(); i++) {
        int acc = std::accumulate(vv[i].begin(), vv[i].end(), 0, std::bit_xor<>());
        if (acc > max) {
            max = acc;
            maxi = i;
        }
    }

    return vv[maxi];
}

int main() {
    printArr(maxSubarrayXORRecursive({3, 9, 4, 12, 7}));
    printArr(maxSubarrayXORRecursive({11, 2, 5, 3, 16, 8}));
    printArr(maxSubarrayXORRecursive({5, 18, 10, 7, 14, 3}));
    printArr(maxSubarrayXORRecursive({4, 1, 3}));
}
