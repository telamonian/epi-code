#include <iostream>

#include "exception.h"
#include "graph.h"
#include "test.h"

template <typename T> using Node = epi::graph::NodeDirected<T>;
template <typename T> using Graph = epi::graph::GraphDirected<T>;

namespace epi {

template <typename T>
void assertDFSLoop(Graph<T>& g, int loopHeadID=-1) {
    std::cout << "Looking for loops in graph: " << g.name << '\n';
    Node<int>* loopHead = g.dfsLoop();
    std::cout << "done." << std::endl;

    if (loopHead) {
        if (loopHeadID < 0) THROW_EXCEPTION(AssertionError, "Found non-existant loop head. id: %d", loopHead->data);

        std::cout << "Found loop head at node id: " << loopHead->data << "\n\n";
        ASSERT_INT_EQUAL(loopHeadID, loopHead->data);
    } else {
        if (loopHeadID >= 0) THROW_EXCEPTION(AssertionError, "Could not find expected loop head.");

        std::cout << "Found no loop head, as expected\n\n";
    }
}

}

int main () {
    {
        Graph<int> g("simple linear", 0, 1, 2, 3, 4, 5);

        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.addEdge(3, 4);
        g.addEdge(4, 5);

        epi::assertDFSLoop(g);
    }

    {
        Graph<int> g("linear with loop", 0, 1, 2, 3, 4, 5);

        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.addEdge(3, 1);
        g.addEdge(3, 4);
        g.addEdge(4, 5);

        epi::assertDFSLoop(g, 3);
    }

    {
        Graph<int> g("lecture_11_jessica_su_0", 0, 1, 2, 3, 4, 5);

        g.addEdge(0, 1);
        g.addEdge(0, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 1);
        g.addEdge(4, 3);

        epi::assertDFSLoop(g, 4);
    }

    {
        Graph<int> g("lecture_11_jessica_su_1", 0, 1, 2, 3, 4, 5);

        g.addEdge(0, 1);
        g.addEdge(0, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 1);
        g.addEdge(4, 5);
        g.addEdge(5, 2);

        epi::assertDFSLoop(g, 5);
    }

    {
        Graph<int> g("lecture_11_jessica_su_2", 0, 1, 2, 3, 4, 5);

        g.addEdge(0, 1);
        g.addEdge(0, 3);
        g.addEdge(1, 4);
        g.addEdge(2, 4);
        g.addEdge(2, 5);
        g.addEdge(3, 1);
        g.addEdge(4, 5);

        Node<int>* loopHead = g.dfsLoop();

        epi::assertDFSLoop(g);
    }
}
