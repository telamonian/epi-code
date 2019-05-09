#ifndef EPI_MERGE_LISTS
#define EPI_MERGE_LISTS

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "exception.h"

namespace epi {
namespace graph {

enum Color {
    WHITE = 0,
    GRAY,
    BLACK,
};

template <typename T>
class NodeSingle {
public:
    NodeSingle(): data(), next(NULL) {}

    // NodeSingle(T& data): data(data), next(NULL) {}
    NodeSingle(T&& data): data(data), next(NULL) {}

    // NodeSingle(T& data, NodeSingle<T>* next): data(data), next(next) {}
    NodeSingle(T&& data, NodeSingle<T>* next): data(data), next(next) {}

    void advance() {
        this = next;
    }

    void destroy() {
        if (next) {
            next->destroy();
            next = NULL;
        }
        delete this;
        dynamicInstances--;
    }

    void print() {
        NodeSingle<T>* next = this;

        std::cout << "[";
        while (next) {
            std::cout << next->data << ", ";
            next = next->next;
        }
        std::cout << "]\n";
    }

    std::vector<T> to() {
        std::vector<T> ret;
        NodeSingle<T>* next = this;

        while (next) {
            ret.push_back(next->data);
            next = next->next;
        }

        return ret;
    }

    static NodeSingle<T>* from(std::vector<T> vec) {
        NodeSingle<T>* ret = NULL;
        for (auto it=vec.rbegin(); it != vec.rend(); it++) {
            ret = new NodeSingle<T>(*it, ret);
            dynamicInstances++;
        }

        return ret;
    }

    T data;
    NodeSingle<T>* next;

    static uint dynamicInstances;
};

template <typename T>
uint NodeSingle<T>::dynamicInstances = 0;

template <typename T>
class NodeDirected {
public:
    typedef std::unordered_set<NodeDirected<T>*> ChildSet;

    NodeDirected(): _color() {}
    NodeDirected(T&& data): NodeDirected(), data(data) {}

    template <class... Args>
    NodeDirected(T&& data, Args... args): NodeDirected(data), children({args...}) {}

    NodeDirected<T>* dfsLoop() const {
        if (_color != Color::WHITE) THROW_EXCEPTION(ValueError, "NodeDirected::dfsLoop should only be called on white colored instances.\n"
                                                                "this->_color: %d", _color);

        _color = Color::GRAY;
        for (typename ChildSet::iterator it=children.begin(); it != children.end(); it++) {
            if (it->_color == Color::WHITE) {
                return it->dfsLoop();
            } else if (it->_color == Color::GRAY) {
                // encountered node still being processed, must be start of loop
                return &*it;
            }
        }

        _color = Color::BLACK;
        return NULL;
    }

    void print() {
        std::cout << "[";
        std::cout << data << ", ";
        for (auto&& c : children) {
            c->print();
        }
        std::cout << "]\n";
    }

    T data;
    ChildSet children;

    mutable Color _color;
};

template <typename T>
class GraphDirected {
public:
    NodeDirected<T>* addNode(int id) {

    }

    std::unordered_map nodes;
};

}
}

#endif /* EPI_MERGE_LISTS */
