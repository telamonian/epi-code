#include <iostream>
#include <unordered_set>

#include "graph.h"
#include "test.h"

using epi::NodeSingle;

namespace epi {

template <typename T>
NodeSingle<T>* findCycleStart(NodeSingle<T>* slow) {
    NodeSingle<T>* fast(slow);
    while(slow != NULL and fast != NULL) {
        std::cout << slow->data << '\n';
        std::cout << fast->data << '\n';
        slow = slow->next;
        fast = fast->next;
        if (fast) {
            fast = fast->next;
        } else {
            return fast;
        }

        if (slow == fast) {
            return fast;
        }
    }

    return fast;
}

template <typename T>
NodeSingle<T>* findCycleStartHash(NodeSingle<T>* head) {
    std::unordered_set<NodeSingle<T>* > seen;

    NodeSingle<T>* next = head;
    while (next) {
        if (seen.count(next)) return next;
        seen.insert(next);
        next = next->next;
    }

    // next should be NULL here
    return next;
}

}


int main() {
    // case 1
    {
        NodeSingle<int> m7(23);
        NodeSingle<int> m6(16, &m7);
        NodeSingle<int> m5(14, &m6);
        NodeSingle<int> m4(11, &m5);
        NodeSingle<int> m3(7, &m4);
        NodeSingle<int> m2(5, &m3);
        NodeSingle<int> m1(3, &m2);
        NodeSingle<int> m0(2, &m1);

        // add a cycle
        m7.next = &m3;

        // find cycle, if any
        NodeSingle<int>* cycleNode = epi::findCycleStart(&m0);
        ASSERT_UINT_EQUAL(&m3, cycleNode);

        cycleNode = epi::findCycleStartHash(&m0);
        ASSERT_UINT_EQUAL(&m3, cycleNode);
    }

    // case 2
    {
        NodeSingle<int> m7(23);
        NodeSingle<int> m6(16, &m7);
        NodeSingle<int> m5(14, &m6);
        NodeSingle<int> m4(11, &m5);
        NodeSingle<int> m3(7, &m4);
        NodeSingle<int> m2(5, &m3);
        NodeSingle<int> m1(3, &m2);
        NodeSingle<int> m0(2, &m1);

        // find cycle, if any
        NodeSingle<int>* cycleNode = epi::findCycleStart(&m0);
        ASSERT_UINT_EQUAL(NULL, cycleNode);

        cycleNode = epi::findCycleStartHash(&m0);
        ASSERT_UINT_EQUAL(NULL, cycleNode);
    }
}
