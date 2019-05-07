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

#define ASSERT_INT_EQUAL(intended, actual) if (intended != actual) {THROW_EXCEPTION(epi::AssertionError, "intended != actual.\n" "intended: %lld, actual %lld", intended, actual)}
#define ASSERT_UINT_EQUAL(intended, actual) if (intended != actual) {THROW_EXCEPTION(epi::AssertionError, "intended != actual.\n" "intended: %llu, actual %llu", intended, actual)}
}

#endif //EPI_CODE_TEST_H
