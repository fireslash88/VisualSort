#ifndef VISUALSORT_INSERTIONSORT_H
#define VISUALSORT_INSERTIONSORT_H

#include "../main.h"

inline float key;
inline bool inserting = false;

inline  std::string insertionSortDescription="This is Insertion sort!\n"
                                             "\n"
                                             "It works by inserting each\n"
                                             "value of an unsorted list into\n"
                                             "its correct position in a sorted list!\n"
                                             "\n"
                                             "Pros: It's simple to implement and\n"
                                             "fast for small amount of data\n"
                                             "Cons: Inefficient and slow for large\n"
                                             "amount of data";
inline void insertionSort() {
    if (counterI >= value.size()) {
        sortingMode = false;
        completed = true;
        return;
    }

    if (!inserting) {
        key = value.at(counterI).height;

        arrayAccesses++;

        counterJ = counterI - 1;

        inserting = true;
    }

    value.at(counterI).active = true;

    if (counterJ>=0) {
        arrayAccesses++;
        comparisonsPerformed++;

        if (counterJ >= 0 && (value.at(counterJ).height > key)) {

            value.at(counterJ + 1).height = value.at(counterJ).height;

            arrayAccesses += 2;

            value.at(counterJ).active = false;

            counterJ--;

            return;
        }
    }

    arrayAccesses++;

    value.at(counterJ + 1).height = key;

    value.at(counterJ+1).active = false;

    counterI++;

    inserting = false;
}

#endif //VISUALSORT_INSERTIONSORT_H
