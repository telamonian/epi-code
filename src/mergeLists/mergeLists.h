#ifndef EPI_MERGE_LISTS
#define EPI_MERGE_LISTS

#include <cstddef>
#include <iostream>
#include <vector>

namespace epi {
    
template <typename T>
class Node {
public:
    Node(): data(), next(NULL) {}

    Node(T& data): data(data), next(NULL) {}
    Node(T&& data): data(data), next(NULL) {}

    Node(T& data, Node<T>* next): data(data), next(next) {}
    Node(T&& data, Node<T>* next): data(data), next(next) {}

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
        Node<T>* next = this;

        std::cout << "[";
        while (next) {
            std::cout << next->data << ", ";
            next = next->next;
        }
        std::cout << "]\n";
    }

    std::vector<T> to() {
        std::vector<T> ret;
        Node<T>* next = this;

        while (next) {
            ret.push_back(next->data);
            next = next->next;
        }

        return ret;
    }

    static Node<T>* from(std::vector<T> vec) {
        Node<T>* ret = NULL;
        for (auto it=vec.rbegin(); it != vec.rend(); it++) {
            ret = new Node<T>(*it, ret);
            dynamicInstances++;
        }

        return ret;
    }

    T data;
    Node<T>* next;

    static uint dynamicInstances;
};

template <typename T>
uint Node<T>::dynamicInstances = 0;

}

#endif /* EPI_MERGE_LISTS */

