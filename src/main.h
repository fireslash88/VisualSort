#ifndef VISUALSORT_MAIN_H
#define VISUALSORT_MAIN_H

struct Values {
    float x;
    float y;
    float width;
    float height;
    bool active;
    Color color;
};

const int maxValues = 100;
const int minValues = 5;

inline Values value[maxValues];
inline int shownValues = 5;
inline int newValues = 0;

inline int counterI = 0;
inline int counterJ = 0;
inline bool completed = false;

inline float frameTime = 0.0;

inline int completedAnimI=0;

inline bool sortingMode = false;

inline int ListViewIndexActive = -1;
inline float SliderSortingSpeed;

#endif //VISUALSORT_MAIN_H
