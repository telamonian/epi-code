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

template <typename T> using Vec = std::vector<T>;
template <typename T> using Vecvec = std::vector<std::vector<T>>;

template <typename T>
void _allSubarrays(const Vec<T>& v0, const Vec<T>& v1, Vecvec<T>& vv) {
    if (v0.empty()) {
        if (v1.empty()) {
            return;
        }
        Vec<T> u0(v1.begin(), v1.end());
        Vec<T> u1(v1.begin(), v1.end() - 1);
        vv.push_back(u0);
        vv.push_back(u1);
        return _allSubarrays(u0, u1, vv);
    }
    Vec<T> u0(v0.begin() + 1, v0.end());
    Vec<T> u1(v1.begin(), v1.end());
    vv.push_back(u0);
    vv.push_back(u1);
    return _allSubarrays(u0, u1, vv);
}

template <typename T>
Vecvec<T> allSubarrays(const Vec<T>& arr) {
    Vecvec<T> vv;
    if (arr.empty()) return vv;

    vv.push_back(Vec<T>(arr.begin(), arr.end()));
    vv.push_back(Vec<T>(arr.begin(), arr.end() - 1));

    _allSubarrays(vv[0], vv[1], vv);
    return vv;
}

Vec<int> maxSubarrayXORRecursive(const Vec<int>& arr) {
    int max = 0;
    int maxi = 0;

    auto vv = allSubarrays(arr);
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
}
