#include <iostream>

template <typename T>
T bitCount(T num) {
    T count = 0;
    do {
        if (num & 1) count++;
    } while (num >>= 1);

    return count;
}

int main() {
    int x = 19823918;
    std::cout << "There are " << bitCount(x) << " bits set to one in the base ten number " << x << std::endl;
}

