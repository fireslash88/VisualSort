#ifndef VISUALSORT_SELECTIONSORT_H
#define VISUALSORT_SELECTIONSORT_H

#include "../main.h"

inline int minIndex=0;

inline void selectionSort() {
    if (counterI > shownValues - 1) {
        sortingMode = false;
        completed = true;
        return;
    }
    if (counterJ < shownValues) {
        if (counterJ >= counterI) {
            if (value[counterJ].height < value[minIndex].height) {
                value[minIndex].active=false;
                minIndex = counterJ;
            }

        }
        value[minIndex].active=true;

        value[counterJ].active=false;
        value[counterI].active=true;

        counterJ++;

        value[counterJ].active=true;
    } else {
        //Swap the values
        float temp = value[counterI].height;
        value[minIndex].active=false;
        value[counterI].height = value[minIndex].height;
        value[minIndex].height = temp;

        value[counterI].active=false;
        counterI++;
        value[counterI].active=true;

        counterJ = 0 + counterI;
        minIndex = counterI;
    }
}

#endif //VISUALSORT_SELECTIONSORT_H
