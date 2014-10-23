/**
 * @file VectorCBTree.h
 * @author Zhang Hai
 */

#ifndef _VECTOR_CB_TREE_H_
#define _VECTOR_CB_TREE_H_

#include <cstddef>
#include <stdexcept>
#include <vector>

#include <iostream>

template<typename T>
class VectorCBTree {

public:

    class Iterator {

    private:

        VectorCBTree *outer;

        size_t index;

    public:

        Iterator(VectorCBTree *outer, size_t index) : outer(outer),
        index(index) {
            if (!withinBound(index)) {
                throwOutOfBound();
            }
        }

        bool hasParent() {
            return withinBound(parentIndex());
        }

        bool hasChild() {
            return hasLeftChild();
        }

        bool hasLeftChild() {
            return withinBound(leftChildIndex());
        }

        bool hasRightChild() {
            return withinBound(rightChildIndex());
        }

        typename VectorCBTree<T>::Iterator parent() {
            return Iterator(outer, parentIndex());
        }

        typename VectorCBTree<T>::Iterator leftChild() {
            return Iterator(outer, leftChildIndex());
        }

        typename VectorCBTree<T>::Iterator rightChild() {
            return Iterator(outer, rightChildIndex());
        }

        T& get() {
            return outer->storage.at(index);
        }

        void set(const T& element) {
            get() = element;
        }

        Iterator &operator++() {
            if (!withinBound(index + 1)) {
                throwOutOfBound();
            }
            ++index;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++*this;
            return temp;
        }

        Iterator &operator--() {
            if (!withinBound(index - 1)) {
                throwOutOfBound();
            }
            --index;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --this;
            return temp;
        }

    private:

        size_t parentIndex() {
            return (index + 1) / 2 - 1;
        }

        size_t leftChildIndex() {
            return 2 * index + 1;
        }

        size_t rightChildIndex() {
            return 2 * index + 2;
        }

        bool withinBound(size_t index) {
            return index < outer->storage.size();
        }

        void throwOutOfBound() {
            throw std::out_of_range(
                    "Index for iterator out of range");
        }
    };

private:

    std::vector<T> storage;

public:

    VectorCBTree(std::vector<T> storage = std::vector<T>())
            : storage(storage) {}

    size_t size() {
        return storage.size();
    }

    void reserve(size_t capacity) {
        storage.reserve(capacity);
    }

    void add(const T& element) {
        storage.push_back(element);
    }

    void remove() {
        storage.pop_back();
    }

    T& get(size_t index) {
        return storage.at(index);
    }

    T& getFirst() {
        return get(0);
    }

    T& getLast() {
        return get(size() - 1);
    }

    void set(size_t index, const T& element) {
        get(index) = element;
    }

    void setFirst(const T& element) {
        getFirst() = element;
    }

    void setLast(const T& element) {
        getLast() = element;
    }

    void print() {
        bool first = true;
        for (T &element : storage) {
            if (first) {
                first = false;
            } else {
                std::cout << " ";
            }
            std::cout << element;
        }
        std::cout << std::endl;
    }

    typename VectorCBTree<T>::Iterator at(size_t index) {
        return Iterator(this, index);
    }

    typename VectorCBTree<T>::Iterator first() {
        return at(0);
    }

    typename VectorCBTree<T>::Iterator last() {
        return at(storage.size() - 1);
    }
};

#endif /* _VECTOR_CB_TREE_H_ */
