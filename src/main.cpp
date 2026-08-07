#include <string>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "main.h"
#include "bubbleSort.h"
#include "selectionSort.h"
#include "insertionSort.h"
#include "mergeSort.h"

//Constants for screen size
const int screenWidth = 1080;
const int screenHeight = 720;

//Constants for sorting speed
const float maxSpeed=0.01;
const float minSpeed=2.0;

//Starter description
std::string starterDescription="This software helps you to learn\n"
                               "sorting algorithms by visualizing them!\n"
                           "Select an algorithm and press Sort \n"
                           "to start!";

// GUI Variables
bool ValueBox1EM = false;

float SliderSortingSpeed=0.5;
int ListViewIndexSel;

bool CheckBoxText = true;

//Main Functions
void InitGame();
void UpdateGame();
void DrawGame();
void UpdateDrawFrame();

//Other functions
void shuffle();
void completedAnimation();
bool delay(float seconds);

int main() {
    InitWindow(screenWidth, screenHeight, "VisualSort");
    InitGame();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}

//Initiate game variables;
void InitGame() {

    // Calculate how large is the width of every rectangle
    float rectSize = static_cast<float>(screenWidth) / static_cast<float>(value.size());

    // Initialize every rectangle of the values with the calculated width and some base settings
    for (int i = 0; i < value.size(); i++) {
        value.at(i).x = rectSize * static_cast<float>(i);
        value.at(i).y = 300;
        value.at(i).width = rectSize;
        value.at(i).height = 0;
        value.at(i).active = false;
        value.at(i).color = BLACK;
    }

    description=starterDescription;

    // Shuffle the values at the start of the program
    shuffle();

    frameTime=0.0;

    sortingMode = false;
    completed=false;

    completedAnimI=0;

    //Reset statistics
    arrayAccesses=0;
    comparisonsPerformed=0;
    swapsPerformed=0;
}

//Update Game
void UpdateGame() {

    // Updates the frameTime variables incrementing it by the FrameTime of the program
    frameTime += GetFrameTime();

    //Decide what function to call and check if it needs to sort and if it waited enough
    if (sortingMode==true && delay(SliderSortingSpeed)) {
        switch (ListViewIndexActive) {
            case 0: {
                bubbleSort();
                description=bubbleSortDescription;
                break;
            }
            case 1: {
                selectionSort();
                description=selectionSortDescription;
                break;
            }
            case 2: {
                insertionSort();
                description=insertionSortDescription;
                break;
            }
            case 3: {
                mergeSort();
                description=mergeSortDescription;
                break;
            }
            default: {
                break;
            }
        }
    }

    //Plays animation if sorting is completed
    if (completed && delay(SliderSortingSpeed)) {
        completedAnimation();
    }

}

//Draw game
void DrawGame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    // Draws all the values as rectangles, uses Vectors.
    for (int i = 0; i < value.size(); i++) {
        Vector2 position = {value.at(i).x, value.at(i).y - value.at(i).height};
        Vector2 size = {value.at(i).width, value.at(i).height};

        //If the value is selected or being sorted, it becomes red
        if (value.at(i).active==true) {
            DrawRectangleV(position, size,RED);
        }else {
            DrawRectangleV(position, size,value.at(i).color);
        }
    }

    // Draws a line as a base for the rectangles
    DrawLineBezier({0,302},{screenWidth,302},4,GRAY);

    // Draws box to insert the quantity of values to sort, minimum quantity of values is 5, maximum is decided by the constant.
    if (GuiValueBox({170, 370, 60, 20}, "Values to sort", &newLength, minValues, maxValues, ValueBox1EM)) {
        ValueBox1EM = !ValueBox1EM;
        if (!ValueBox1EM) {
            vectorLength = newLength;
            value.resize(vectorLength);
            InitGame();
        }
    }

    // Draws list view of all the algorithms available
    DrawText("Algorithms", 30, 420, 20, GRAY);

    int DidAlgorithmChange=
        GuiListView({30, 450, 200, 125},
            "Bubble Sort;Selection Sort;Insertion Sort;Merge Sort",
            &ListViewIndexSel,
            &ListViewIndexActive)
    ;

    if (DidAlgorithmChange) {
        sortingMode=false;
        InitGame();
    }

    // Draws button to shuffle the rectangles
    if (GuiButton({300, 360, 150, 50}, "Shuffle")) {
        InitGame();
    }

    if (sortingMode) {
        GuiSetState(STATE_DISABLED);
    }

    // Draws button to start sorting
    if (GuiButton({500, 360, 150, 50}, "Sort") && !completed) {
        if (ListViewIndexActive>-1) {
            //Exception for select sort
            if (ListViewIndexActive==1) {
                counterI=0;
                counterJ=1;
                sortingMode=true;
            }
            //Exception for insertion sort
            else if (ListViewIndexActive==2) {
                counterI=1;
                counterJ=0;
                sortingMode=true;
            }
            else {
                counterI=0;
                counterJ=0;
                sortingMode=true;
            }
        }
    }

    GuiSetState(STATE_NORMAL);

    // Draws slider to customize speed of the sorting
    DrawText("Sorting speed",295,470,20,GRAY);
    GuiSliderBar({340, 500,70,30},"Quick","Slow",&SliderSortingSpeed,maxSpeed,minSpeed);
    DrawText("(Min: 0.01s, Max: 2.0s)",290,540,20,GRAY);


    // Draws checkbox to show/hide the number of the values
    GuiCheckBox({30,650,30,30},"Show number of the values",&CheckBoxText);
    if (CheckBoxText && value.size()<=30){
        for (int i = 0; i < value.size(); i++) {
            DrawText(TextFormat("%.0f", value.at(i).height), value.at(i).x, value.at(i).y+5, 20,BLACK);
        }
    }
    if (CheckBoxText && value.size()>30) {
        DrawText("The number of the values are shown only if the values to sort are below or equal to 30!" ,30,150,20,RED);
        DrawText("Uncheck the box below!", 30 ,180,20, RED);
    }

    GuiTextBox({700,370,360,320},description.data(),1,false);

    // Draws the statistics of the sorting algorithm
    DrawText(TextFormat("Array accesses: %d",arrayAccesses),30,30,20,GRAY);
    DrawText(TextFormat("Comparisons performed: %d",comparisonsPerformed),30,60,20,GRAY);
    DrawText(TextFormat("Swaps performed: %d",swapsPerformed),30,90,20,GRAY);

    EndDrawing();
}

//Update and draw
void UpdateDrawFrame() {
    UpdateGame();
    DrawGame();
}

//Shuffle the rectangle positions
void shuffle() {
    for (int i = 0; i < value.size(); i++) {
        value.at(i).height = (GetRandomValue(1, 100));
    }
}

//Animation that plays when a sorting is completed
void completedAnimation() {
    if (completedAnimI<value.size()) {
        value.at(completedAnimI).active=false;
        value.at(completedAnimI).color=GREEN;
    }
    completedAnimI++;
}

// Adds a delay between swaps
bool delay(float seconds) {

    if (seconds <= frameTime) {
        frameTime = 0;
        return true;
    }

    return false;
}