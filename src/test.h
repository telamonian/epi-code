//
// Created by tel on 2019-05-07.
//

#ifndef EPI_CODE_TEST_H
#define EPI_CODE_TEST_H

#include "exception.h"


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


#define ASSERT_INT_EQUAL(intended, actual) if (intended != actual) {THROW_EXCEPTION(epi::AssertionError, "intended != actual.\n" "intended: %lld, actual %lld", intended, actual)}
#define ASSERT_UINT_EQUAL(intended, actual) if (intended != actual) {THROW_EXCEPTION(epi::AssertionError, "intended != actual.\n" "intended: %llu, actual %llu", intended, actual)}

#define ASSERT_PARTITION(A, pivot, low, equal, high) if (not epi::testPartition(A, pivot, low, equal, high) ) {THROW_EXCEPTION(epi::AssertionError, "A was not correctly paritioned.\n" "pivot: %d", pivot)}

}
#endif //EPI_CODE_TEST_H
