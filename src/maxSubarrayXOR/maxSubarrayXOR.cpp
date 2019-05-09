#include <iostream>
#include <vector>

template <typename T>
void printArr(const std::vector<T>& arr) {
    auto it = arr.begin();
    if (it != arr.end()) std::cout << *it++;
    for (; it != arr.end(); it++) std::cout << ", " << *it;
    std::cout << '\n';
}

std::vector<int> maxSubarrayXOR(const std::vector<int>& arr) {
    std::vector<int> ret;
    auto it = arr.begin();


}

int main() {

}