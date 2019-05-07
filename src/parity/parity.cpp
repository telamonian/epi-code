#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>

#include "test.h"

using std::cout;
using std::vector;

const uint64_t WORD_SIZE = 256;

uint64_t count(uint64_t n) {
    uint64_t cnt = n & 1;
    while (n >>= 1) cnt += n & 1;

    return cnt;
}

vector<uint64_t> initCountTable() {
    vector<uint64_t> cntTab;
    for (uint64_t i=0; i < WORD_SIZE; i++) {
        cntTab.push_back(count(i));
    }

    return cntTab;
}

uint64_t parity(uint64_t n) {
    return count(n) % 2;
}

vector<uint64_t> initParityTable() {
    vector<uint64_t> parTab;
    for (uint64_t i=0; i < WORD_SIZE; i++) {
        parTab.push_back(parity(i));
    }

    return parTab;
}

static vector<uint64_t> cntTab = initCountTable();
static vector<uint64_t> parTab = initParityTable();

uint64_t fastCount(uint64_t n) {
    uint64_t mask = WORD_SIZE - 1;
    return (cntTab[n & mask]
          + cntTab[(n >> 8) & mask]
          + cntTab[(n >> 16) & mask]
          + cntTab[(n >> 24) & mask]
          + cntTab[(n >> 32) & mask]
          + cntTab[(n >> 40) & mask]
          + cntTab[(n >> 48) & mask]
          + cntTab[(n >> 56) & mask]);
}

uint64_t fastParity(uint64_t n) {
    uint64_t mask = WORD_SIZE - 1;
    return ((parTab[n & mask]
           + parTab[(n >> 8) & mask]
           + parTab[(n >> 16) & mask]
           + parTab[(n >> 24) & mask]
           + parTab[(n >> 32) & mask]
           + parTab[(n >> 40) & mask]
           + parTab[(n >> 48) & mask]
           + parTab[(n >> 56) & mask]) % 2);
}

void printCount(uint64_t n) {
    cout << "The count of " << n << " is " << fastCount(n) << '\n';
}

void printParity(uint64_t n) {
    cout << "The parity of " << n << " is " << fastParity(n) << '\n';
}

void assertParity(uint64_t n, uint64_t count, uint64_t par) {
    printCount(n);
    printParity(n);
    ASSERT_UINT_EQUAL(count, fastCount(n));
    ASSERT_UINT_EQUAL(par, fastParity(n));
}

void printTable(vector<uint64_t>& tab) {
    uint64_t i = 0;
    for (vector<uint64_t>::iterator it = tab.begin(); it != tab.end(); it++) {
        cout << i++ << ": " << *it << '\n';
    }
}

int main() {
    //printTable(cntTab);
    //printTable(parTab);
    //cout << "The size of int is " << sizeof(int) << '\n';
    //cout << "The size of uint is " << sizeof(uint) << '\n';
    //cout << "The size of unsinged is " << sizeof(unsigned) << '\n';
    //cout << "The size of unsigned int is " << sizeof(unsigned int) << '\n';
    //cout << "The size of long is " << sizeof(long) << '\n';
    //cout << "The size of unsigned long is " << sizeof(unsigned long) << '\n';
    //cout << "The size of long long is " << sizeof(long long) << '\n';
    //cout << "The size of unsigned long long is " << sizeof(unsigned long long) << '\n';
    
    cout << "The parity of -1 is " << fastParity(-1) << '\n';
    cout << "The parity of -2 is " << fastParity(-2) << '\n';

    try
    {
        assertParity(17102472071623797226ull, 34, 0);
        assertParity(13685118662955289121ull, 33, 1);
        assertParity(16949684047099354875ull, 42, 0);
        assertParity(12380270825930137469ull, 37, 1);
    }
    catch (epi::AssertionError& e)
    {
        cout << e.what() << '\n';
    }
}
