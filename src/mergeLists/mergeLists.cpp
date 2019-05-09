#include <algorithm>
#include <iostream>
#include <vector>

#include "print.h"
#include "test.h"
#include "graph.h"

using epi::NodeSingle;

namespace epi {

template <typename T>
NodeSingle<T>* merge(NodeSingle<T>* l, NodeSingle<T>* f) {
    while (l != NULL and f != NULL) {
        if (l->data <= f->data) {
            std::swap(l->next, f);
            l->advance();
        } else {
            std::swap(f->next, l);

        }
    }

    return l != NULL ? l : f;
}

template <typename T>
NodeSingle<T>* mergeLeft(NodeSingle<T>* l, NodeSingle<T>* f) {
    if (l->data > f->data) std::swap(l, f);
    NodeSingle<T>* ret = l;

    while (l != NULL and f != NULL) {
        if (f->data >= l->data and (l->next == NULL or f->data < l->next->data)) std::swap(l->next, f);
        l = l->next;
    }

    return ret;
}

template <typename T>
NodeSingle<T>* doMerge(NodeSingle<T>* l, NodeSingle<T>* f, const std::vector<T>& intended) {
    std::cout << "l list: ";
    l->print();
    std::cout << "f list: ";
    f->print();

    NodeSingle<int>* merged = mergeLeft(l, f);

    std::cout << "merged list: ";
    merged->print();
    std::cout << "intended merged list: ";
    printVec(intended);
    std::cout << '\n';

    ASSERT_VECTOR_EQUAL(intended, merged->to());
    return merged;
}

}

int main() {
    // case 1
    {
        NodeSingle<int> l2(7);
        NodeSingle<int> l1(5, &l2);
        NodeSingle<int> l0(2, &l1);

        NodeSingle<int> f1(11);
        NodeSingle<int> f0(3, &f1);

        NodeSingle<int> m4(11);
        NodeSingle<int> m3(7, &m4);
        NodeSingle<int> m2(5, &m3);
        NodeSingle<int> m1(3, &m2);
        NodeSingle<int> m0(2, &m1);

        epi::doMerge(&l0, &f0, m0.to());
    }

    // case 2
    {
        std::vector<int> lvec = {0, 4, 6, 7, 8};
        std::vector<int> fvec = {1, 2, 3, 5, 6, 9};
        std::vector<int> mvec;
        std::merge(lvec.begin(), lvec.end(), fvec.begin(), fvec.end(), std::back_inserter(mvec));

        NodeSingle<int>* l = NodeSingle<int>::from(lvec);
        NodeSingle<int>* f = NodeSingle<int>::from(fvec);

        NodeSingle<int>* merged = epi::doMerge(l, f, mvec);
        // check the dynamic allocation stuff
        merged->destroy();
        ASSERT_UINT_EQUAL(0, NodeSingle<int>::dynamicInstances);
    }

    // case 3
    {
        std::vector<int> lvec = {6, 19, 21, 27, 37, 51, 56, 65, 75, 76};
        std::vector<int> fvec = {2, 4, 21, 28, 46, 58, 72, 74, 77, 80, 95};
        std::vector<int> mvec;
        std::merge(lvec.begin(), lvec.end(), fvec.begin(), fvec.end(), std::back_inserter(mvec));

        NodeSingle<int>* l = NodeSingle<int>::from(lvec);
        NodeSingle<int>* f = NodeSingle<int>::from(fvec);

        NodeSingle<int>* merged = epi::doMerge(l, f, mvec);
    }
}
