#ifndef EPI_PRINT
#define EPI_PRINT

#include <iostream>
#include <vector>

namespace epi {
    
    template <typename T>
    void printVec(const std::vector<T>& vec) {
        std::cout << "[";
        for (auto it = vec.begin(); it != vec.end(); it++) {
            std::cout << *it << ", ";
        }
        std::cout << "]\n";
    }

}

#endif /* EPI_PRINT */
