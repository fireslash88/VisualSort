#ifndef VISUALSORT_MERGESORT_H
#define VISUALSORT_MERGESORT_H

#include <vector>
#include "../main.h"


inline std::vector<float> L;
inline std::vector<float> R;

inline int left=0;
inline int mid=0;
inline int right=0;

inline int k=0;
inline int mergeSize=1;

inline bool copying=true;
inline bool merging=false;

inline void merge() {

    if (copying) {

        int n1= mid - left + 1;
        int n2= right - mid;

        L.resize(n1);
        R.resize(n2);

        for (int i=0;i<n1;i++) {
            L.at(i)=value.at(left+i).height;
        }
        for (int j=0;j<n2;j++) {
            R.at(j)=value.at(mid+1+j).height;
        }

        counterI=0;
        counterJ=0;

        k=left;

        copying=false;
    }

    if (counterI<L.size() && counterJ<R.size()) {

        comparisonsPerformed++;

        if (L.at(counterI) <= R.at(counterJ)) {
            value.at(k).height= L.at(counterI);
            counterI++;
        } else {
            value.at(k).height = R.at(counterJ);
            counterJ++;
        }

        arrayAccesses++;

        k++;
        return;
    }

    if (counterI<L.size()) {
        value.at(k).height=L.at(counterI);
        counterI++;

        arrayAccesses++;

        k++;
        return;
    }

    if (counterJ<R.size()) {
        value.at(k).height = R.at(counterJ);
        counterJ++;

        arrayAccesses++;

        k++;
        return;
    }

    copying=true;
}

//
inline void mergeSort() {

    if (mergeSize >= value.size()) {
        sortingMode = false;
        completed = true;

        mergeSize=1;
        left=0;
        return;
    }

    //AI: Used to generate some code and debug some problems I had
    if (!merging) {
        if (left>=value.size()) {
            left=0;
            mergeSize *=2;
            return;
        }

        mid = left + mergeSize - 1;

        if (mid >= value.size()-1) {
            left += mergeSize*2;
            return;
        }

        right=left+mergeSize*2-1;

        if (right>=value.size()) {
            right=value.size()-1;
        }

        merging=true;
    }

    merge();

    if (!copying && counterI >= L.size() && counterJ >= R.size()) {
        copying = true;
        merging = false;

        left += mergeSize * 2;
    }
}

#endif //VISUALSORT_MERGESORT_H