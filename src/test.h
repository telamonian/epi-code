//
// Created by tel on 2019-05-07.
//

#ifndef EPI_CODE_TEST_H
#define EPI_CODE_TEST_H

#include <iostream>
#include <vector>

#include "exception.h"
#include "iter.h"
#include "print.h"

namespace epi
{
//template <typename T, bool IsUint=> struct numTag;
//template <> struct numTag;
//
//template <typename T> struct assertIntEqual
//{
//    bool operator() (T intended, T actual) {return intended == actual;}
//};

bool testPartition(int* A, int pivot, size_t low, size_t equal, size_t high)
{
    for (int i = 0; i < low; i++) if (A[i] >= pivot) return false;
    for (int i = low; i < low + equal; i++) if (A[i] != pivot) return false;
    for (int i = low + equal; i < low + equal + high; i++) if (A[i] <= pivot) return false;

    return true;
}

template <typename T>
bool testArrayEqual(const T* intended, const T* actual, size_t size) {
    for (size_t i=0; i < size; i++) {
        if (intended[i] != actual[i]) return false;
    }
    return true;
}

template <typename T>
bool testVectorEqual(const std::vector<T>& intended, const std::vector<T>& actual) {
    if (intended.size() != actual.size()) return false;

    // for now, this kills the compiler
    // for (auto& [x, y] : zip_range(intended, actual)) {
    //     if (x != y) return false;
    // }

    for (auto iit=intended.begin(),ait=actual.begin(); iit!=intended.end() and ait!=actual.end(); iit++,ait++) {
        if (*iit != *ait) return false;
    }

    return true;
}

#define ASSERT_INT_EQUAL(intended, actual) if (intended != actual) { \
    THROW_EXCEPTION(epi::AssertionError, "intended != actual.\n" \
                                         "intended: %lld, actual %lld\n", \
                                         intended, actual)}

#define ASSERT_UINT_EQUAL(intended, actual) if (intended != actual) { \
    THROW_EXCEPTION(epi::AssertionError, "intended != actual.\n" \
                                         "intended: %llu, actual %llu\n", \
                                         intended, actual)}

#define ASSERT_PARTITION(A, pivot, low, equal, high) if (not epi::testPartition(A, pivot, low, equal, high)) { \
    THROW_EXCEPTION(epi::AssertionError, "A was not correctly paritioned.\n" \
                                         "pivot: %d\n", \
                                         pivot)}

#define ASSERT_VECTOR_EQUAL(intended, actual) if (not epi::testVectorEqual(intended, actual)) { \
    THROW_EXCEPTION(epi::AssertionError, "intended != actual.\n" \
                                         "intended: %s\n" \
                                         "actual: %s\n", \
                                         epi::tocstr(intended), epi::tocstr(actual))}

}
#endif //EPI_CODE_TEST_H
