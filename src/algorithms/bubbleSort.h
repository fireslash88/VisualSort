#ifndef VISUALSORT_BUBBLESORT_H
#define VISUALSORT_BUBBLESORT_H
#include "../main.h"

inline bool swapped = false;

inline void bubbleSort() {
    if (counterI >= value.size() - 1) {
        sortingMode = false;
        completed = true;
        return;
    }

    if (counterJ < value.size() - 1 - counterI) {
        arrayAccesses += 2;
        comparisonsPerformed++;

        if (value.at(counterJ).height > value.at(counterJ + 1).height) {
            arrayAccesses += 4;
            swapsPerformed++;

            float temp = value.at(counterJ).height;
            value.at(counterJ).height = value.at(counterJ + 1).height;
            value.at(counterJ + 1).height = temp;

            value.at(counterJ).active = false;
            value.at(counterJ + 1).active = true;

            swapped = true;
        }

        value.at(counterJ).active = false;
        value.at(counterJ + 1).active = true;

        counterJ++;
    } else {

        if (!swapped) {
            sortingMode = false;
            completed = true;
            return;
        }

        swapped = false;
        counterJ = 0;
        counterI++;
    }
}

#endif //VISUALSORT_BUBBLESORT_H
