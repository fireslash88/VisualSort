#ifndef VISUALSORT_INSERTIONSORT_H
#define VISUALSORT_INSERTIONSORT_H

#include "../main.h"

inline float key;
inline bool inserting = false;

inline void insertionSort() {
    if (counterI >= shownValues) {
        sortingMode = false;
        completed = true;
        return;
    }
    if (counterI == 0) {
        counterI = 1;
    }

    value[counterI].active = true;
    if (!inserting) {
        key = value[counterI].height;
        counterJ = counterI - 1;
        value[counterJ].active = false;
        inserting = true;
    }

    if (counterJ >= 0 && value[counterJ].height > key) {
        value[counterJ + 1].height = value[counterJ].height;
        counterJ--;
        return;
    }
    value[counterJ + 1].height = key;
    value[counterJ].active = false;
    counterI++;

    inserting = false;
}

#endif //VISUALSORT_INSERTIONSORT_H
