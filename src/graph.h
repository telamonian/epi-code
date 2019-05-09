#ifndef EPI_MERGE_LISTS
#define EPI_MERGE_LISTS

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "exception.h"

namespace epi {
namespace graph {

enum Color {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2,
};

template <typename T>
class NodeSingle {
public:
    NodeSingle(): data(), next(NULL) {}

    NodeSingle(T& data): data(data), next(NULL) {}
    NodeSingle(T&& data): data(data), next(NULL) {}

    NodeSingle(T& data, NodeSingle<T>* next): data(data), next(next) {}
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
    typedef NodeDirected<T> This;
    typedef std::unordered_set<This*> ChildSet;

    NodeDirected(): _color() {}
    NodeDirected(T& data): _color(), data(data) {}
    NodeDirected(T&& data): NodeDirected(data) {}

    template <class... Args>
    NodeDirected(T&& data, Args... args): NodeDirected(data), children({args...}) {}

    This* dfsLoop() {
        if (_color != Color::WHITE) THROW_EXCEPTION(ValueError, "NodeDirected::dfsLoop should only be called on white colored instances.\n"
                                                                "this->data: %d, this->_color: %d", data, _color);

        _color = Color::GRAY;
        for (typename ChildSet::iterator it=children.begin(); it != children.end(); it++) {
            This* child = *it;
            if (child->_color == Color::WHITE) {
                This* loopHead = child->dfsLoop();
                if (loopHead) return loopHead;
            } else if (child->_color == Color::GRAY) {
                // encountered node still being processed, must be start of loop
                return child;
            }
        }

        _color = Color::BLACK;
        return NULL;
    }

    This* dfsLoopDebug() {
        if (_color != Color::WHITE) THROW_EXCEPTION(ValueError, "NodeDirected::dfsLoop should only be called on white colored instances.\n"
                                                                "this->data: %d, this->_color: %d", data, _color);

        _color = Color::GRAY;
        std::cout << "Node: " << data << " is now color: " << _color << '\n';
        for (typename ChildSet::iterator it=children.begin(); it != children.end(); it++) {
            This* child = *it;
            std::cout << "Node: " << data << " found child: " << child->data << " of color: " << child->_color << '\n';
            if (child->_color == Color::WHITE) {
                This* loopHead = child->dfsLoopDebug();
                if (loopHead) return loopHead;
            } else if (child->_color == Color::GRAY) {
                // encountered node still being processed, must be start of loop
                return child;
            }
        }

        _color = Color::BLACK;
        std::cout << "Node: " << data << " is now color: " << _color << '\n';
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
    typedef NodeDirected<T> Node;
    typedef std::unordered_map<int, Node> NodeMap;

    GraphDirected() {}

    template <typename... Args> GraphDirected(const char* name, Args... args): name(name) {addNode(args...);}
    template <typename... Args> GraphDirected(Args... args) {addNode(args...);}

    template <typename... Args>
    void addNode(Args... args) {
        std::vector<int> ids = {args...};
        for (auto id: ids) {
            nodes.emplace(id, id);
        }
    }

    void addEdge(int id0, int id1) {
        nodes[id0].children.insert(&nodes[id1]);
    }

    Node* dfsLoop() {
        Node* ret = NULL;
        for (typename NodeMap::iterator it=nodes.begin(); it != nodes.end(); it++) {
            if (it->second._color == Color::WHITE) {
                ret = it->second.dfsLoop();
                if (ret) return ret;
            }
        }

        return ret;
    }

    Node* dfsLoopDebug() {
        Node* ret = NULL;
        for (typename NodeMap::iterator it=nodes.begin(); it != nodes.end(); it++) {
            if (it->second._color == Color::WHITE) {
                std::cout << "Starting GraphDirected::dfsLoop at node: " << it->second.data << '\n';
                ret = it->second.dfsLoopDebug();
                if (ret) return ret;
            }
        }

        return ret;
    }

    NodeMap nodes;
    std::string name;
};

}
}

#endif /* EPI_MERGE_LISTS */
