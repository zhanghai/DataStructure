/**
 * @file Sort.h
 * @author Zhang Hai
 */

#ifndef _SORT_H_
#define _SORT_H_

#include <algorithm>
#include <functional>
#include <utility>

template<typename InputIterator, class Distance>
InputIterator advancedBy(InputIterator &iterator, Distance distance) {
    InputIterator result(iterator);
    std::advance(result, distance);
    return result;
}

template<typename BiIterator, typename Compare =
        std::less<typename BiIterator::value_type>>
void insertionSort(BiIterator begin, BiIterator end,
        Compare compare = Compare()) {
    for (BiIterator sortedEnd = advancedBy(begin, 1);
            sortedEnd != end; ++sortedEnd) {
        BiIterator current(sortedEnd),
                previous = advancedBy(current, -1);
        while (compare(*current, *previous)) {
            std::swap(*current, *previous);
            if (previous == begin) {
                break;
            }
            --current;
            --previous;
        }
    }
}

template<typename BiIterator, typename Compare>
void _merge(BiIterator left, BiIterator right, BiIterator rightEnd,
        std::vector<typename BiIterator::value_type> temp,
        Compare compare) {

    BiIterator begin(left), leftEnd(right);

    temp.clear();
    while (left != leftEnd && right != rightEnd) {
        temp.push_back(compare(*left, *right) ? *(left++)
                : *(right++));
    }
    while (left != leftEnd) {
        temp.push_back(*(left++));
    }
    while (right != rightEnd) {
        temp.push_back(*(right++));
    }

    std::copy(temp.begin(), temp.end(), begin);
}

template<typename BiIterator, typename Compare =
        std::less<typename BiIterator::value_type>>
void mergeSort(BiIterator begin, BiIterator end,
        Compare compare = Compare()) {

    typedef typename BiIterator::value_type value_type;
    typedef typename BiIterator::difference_type difference_type;

    difference_type size = std::distance(begin, end), groupSize = 2;
    std::vector<value_type> temp;
    temp.reserve(size);

    for (groupSize = 1; groupSize < size; groupSize *= 2) {
        for (BiIterator mergeBegin = begin;
                std::distance(mergeBegin, end) > groupSize;
                std::advance(mergeBegin, 2 * groupSize)) {
            difference_type mergeLength =
                    std::min(std::distance(mergeBegin, end),
                            2 * groupSize);
            BiIterator mergeEnd(mergeBegin);
            std::advance(mergeEnd, mergeLength);
            _merge(mergeBegin, mergeBegin + groupSize, mergeEnd, temp,
                    compare);
        }
    }
}

template<typename BiIterator, typename Compare =
        std::less<typename BiIterator::value_type>>
void quickSort(BiIterator begin, BiIterator end,
        Compare compare = Compare()) {

    typedef typename BiIterator::difference_type difference_type;

    const difference_type CUT_OFF = 10;

    difference_type size = std::distance(begin, end);

    if (size <= CUT_OFF) {

        insertionSort(begin, end, compare);

    } else {

        // Make begin <= middle <= end.
        BiIterator middle = advancedBy(begin, size / 2),
                last = advancedBy(end, -1);
        if (compare(*middle, *begin)) {
            std::swap(*begin, *middle);
        }
        if (compare(*last, *begin)) {
            std::swap(*begin, *last);
        }
        if (compare(*last, *middle)) {
            std::swap(*middle, *last);
        }
        // Make the sequence begin, ... , middle(pivot), last, so that
        // the sequence is guarded on both ends.
        BiIterator pivot = advancedBy(last, -1);
        std::swap(*middle, *pivot);

        BiIterator left(begin);
        BiIterator right(pivot);
        while (true) {
            while (left != right && !compare(*pivot, *++left)) {}
            while (left != right && !compare(*--right, *pivot)) {}
            if (left == right) {
                break;
            } else {
                std::swap(*left, *right);
            }
        }
        std::swap(*left, *pivot);
        pivot = left;

        quickSort(begin, pivot, compare);
        quickSort(advancedBy(pivot, 1), end, compare);
    }
}

#endif /* _SORT_H_ */
