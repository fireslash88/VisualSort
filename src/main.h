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
//Max. and min. values limits
const int maxValues = 100;
const int minValues = 5;

//Declaration of the values
inline Values value[maxValues];

//Variables that decides how many values are shown
//and how many to add
inline int shownValues = 5;
inline int newValues = 0;

//Statistics of the algorithms
inline int arrayAccesses = 0;
inline int comparisonsPerformed = 0;
inline int swapsPerformed = 0;

//Counters for algorithms
inline int counterI = 0;
inline int counterJ = 0;

//Check if sorting or it's completed
inline bool sortingMode = false;
inline bool completed = false;

//Counter for completed animation
inline int completedAnimI=0;

//Get time between frames
inline float frameTime = 0.0;

//Variables for the interactive GUI
inline int ListViewIndexActive = -1;
inline float SliderSortingSpeed;

#endif //VISUALSORT_MAIN_H
