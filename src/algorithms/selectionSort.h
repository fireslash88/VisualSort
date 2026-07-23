#ifndef VISUALSORT_SELECTIONSORT_H
#define VISUALSORT_SELECTIONSORT_H

#include "../main.h"

inline int minIndex=0;

inline void selectionSort() {
    if (counterI >= value.size()-1) {
        sortingMode = false;
        completed = true;
        minIndex=0;
        return;
    }
    if (counterJ < value.size()) {

        //AI: Helped to delete a useless if condition
        if (value.at(counterJ).height < value.at(minIndex).height) {

            value.at(minIndex).active = false;

            minIndex = counterJ;
        }

        arrayAccesses += 2;
        comparisonsPerformed++;

        value.at(minIndex).active=true;

        value.at(counterJ).active=false;
        value.at(counterI).active=true;

        counterJ++;

        //AI: Helped to fix after vector adjustment
        if (counterJ < value.size()) {
            value.at(counterJ).active=true;
        }

    } else {

        arrayAccesses+=4;
        swapsPerformed++;

        //Swap the values
        float temp = value.at(counterI).height;

        value.at(minIndex).active=false;

        value.at(counterI).height = value.at(minIndex).height;
        value.at(minIndex).height = temp;

        value.at(counterI).active=false;

        counterI++;

        //AI: Helped to fix after vector adjustment
        if (counterI < value.size()) {
            value.at(counterI).active=true;
        }

        counterJ = 1 + counterI;
        minIndex = counterI;
    }
}

#endif //VISUALSORT_SELECTIONSORT_H
