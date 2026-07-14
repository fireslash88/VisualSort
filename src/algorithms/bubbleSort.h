#ifndef VISUALSORT_BUBBLESORT_H
#define VISUALSORT_BUBBLESORT_H
#include "../main.h"

inline bool swapped = false;

inline void bubbleSort() {
    if (counterI > shownValues - 1) {
        sortingMode = false;
        completed=true;
        return;
    }

    if (counterJ < shownValues - 1 - counterI) {
        if (value[counterJ].height > value[counterJ + 1].height) {
            float temp = value[counterJ].height;
            value[counterJ].height = value[counterJ + 1].height;
            value[counterJ + 1].height = temp;
            value[counterJ].active=false;
            value[counterJ+1].active=true;
            swapped = true;
        }
        value[counterJ].active=false;
        value[counterJ+1].active=true;
        counterJ++;
    } else {
        if (!swapped) {
            sortingMode = false;
            completed=true;
            return;
        }
        swapped = false;
        counterJ = 0;
        counterI++;
    }
}

#endif //VISUALSORT_BUBBLESORT_H
