/**
 * @file BinaryHeap.h
 * @author Zhang Hai
 */

#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include <functional>

#include "VectorCBTree.h"

template<typename T, typename CBTree = VectorCBTree<T>,
        typename Compare = std::less<T>>
class BinaryHeap {

private:

    typedef typename CBTree::size_type size_type;

    typedef typename CBTree::Iterator Iterator;

    CBTree cbTree;

    Compare compare;

public:

    BinaryHeap(CBTree cbTree = CBTree(), Compare compare = Compare()) :
            cbTree(cbTree), compare(compare) {
        if (this->cbTree.size() > 1) {
            for (Iterator iter = this->cbTree.last().parent();
                    iter.hasParent(); --iter) {
                percolateDown(iter);
            }
            percolateDown(this->cbTree.first());
        }
    }

    size_type size() {
        return cbTree.size();
    }

    void reserve(size_type capacity) {
        cbTree.reserve(capacity);
    }

    void insert(const T& element) {
        // vector expects the element to exist when using operator [].
        cbTree.add(element);
        percolateUp(cbTree.last());
    }

    T removeMin() {
        Iterator iter = cbTree.first();
        T minElement = iter.get();
        iter.set(cbTree.getLast());
        cbTree.remove();
        percolateDown(iter);
        return minElement;
    }

    void set(size_type index, const T& element) {
        Iterator iter = cbTree.at(index);
        T oldElement = iter.get();
        iter.set(element);
        if (compare(element, oldElement)) {
            percolateUp(iter);
        } else {
            percolateDown(iter);
        }
    }

    T remove(size_type index) {
        Iterator iter = cbTree.at(index);
        T element = iter.get();
        percolateUp(iter, true);
        removeMin();
        return element;
    }

    void print() {
        cbTree.print();
    }

private:

    void percolateUp(Iterator iter, bool toTop = false) {
        T element = iter.get();
        while (iter.hasParent()) {
            Iterator parentIter = iter.parent();
            if (!toTop && compare(parentIter.get(), element)) {
                break;
            }
            iter.set(parentIter.get());
            iter = parentIter;
        }
        iter.set(element);
    }

    void percolateDown(Iterator iter, bool toBottom = false) {
        T element = iter.get();
        while (iter.hasChild()) {
            Iterator *minIter;
            Iterator leftIter = iter.leftChild();
            // Check if right index is out of bound.
            if (iter.hasRightChild()) {
                Iterator rightIter = iter.rightChild();
                minIter = compare(leftIter.get(), rightIter.get()) ?
                        &leftIter : &rightIter;
            } else {
                minIter = &leftIter;
            }
            if (!toBottom && compare(element, minIter->get())) {
                // Already done.
                break;
            }
            iter.set(minIter->get());
            iter = *minIter;
        }
        iter.set(element);
    }
};

#endif /* _BINARY_HEAP_H_ */
