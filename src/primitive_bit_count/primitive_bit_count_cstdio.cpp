#include <cstdio>

template <typename T>
T bitCount(T num) {
    T count = 0;
    while (num) {
        if (num & 1) count++;
        num = num >> 1;
    }

    return count;
}

int main() {
    int x = 19823918;
    printf("There are %lld bits set to one in the base ten number %lld\n", bitCount(x), x);
}

