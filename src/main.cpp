#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "main.h"
#include "bubbleSort.h"
#include "selectionSort.h"
#include "insertionSort.h"
#include "mergeSort.h"
#include "quickSort.h"

//Structures

//Constants for screen size
const int screenWidth = 1080;
const int screenHeight = 720;

//Constants for sorting speed
const float maxSpeed=0.1;
const float minSpeed=2.0;

// GUI Variables
bool ValueBox1EM = false;

int ListViewIndexSel;

bool CheckBoxText = false;

//Main Functions
void InitGame();
void UpdateGame();
void DrawGame();
void UnloadGame();
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
    UnloadGame();

    CloseWindow();
    return 0;
}

//Initiate game variables;
void InitGame() {

    // Calculate how large is the width of every rectangle
    float rectSize = static_cast<float>(screenWidth) / static_cast<float>(shownValues);

    // Initialize every rectangle of the values with the calculated width and some base settings
    for (int i = 0; i < shownValues; i++) {
        value[i].x = rectSize * static_cast<float>(i);
        value[i].y = 300;
        value[i].width = rectSize;
        value[i].height = 0;
        value[i].active = false;
        value[i].color = BLACK;
    }

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
                break;
            }
            case 1: {
                selectionSort();
                break;
            }
            case 2: {
                insertionSort();
                break;
            }
            // case 3: {
            //     break;
            // }
            // case 4: {
            //     break;
            // }
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
    for (int i = 0; i < shownValues; i++) {
        Vector2 position = {value[i].x, value[i].y - value[i].height};
        Vector2 size = {value[i].width, value[i].height};

        //If the value is selected or being sorted, it becomes red
        if (value[i].active==true) {
            DrawRectangleV(position, size,RED);
        }else {
            DrawRectangleV(position, size,value[i].color);
        }
    }

    // Draws a line as a base for the rectangles
    DrawLineBezier({0,302},{screenWidth,302},4,GRAY);

    // Draws box to insert the quantity of values to sort, minimum quantity of values is 5, maximum is decided by the constant.
    if (GuiValueBox({200, 350, 60, 20}, "Values to sort", &newValues, minValues, maxValues, ValueBox1EM)) {
        ValueBox1EM = !ValueBox1EM;
        if (!ValueBox1EM) {
            shownValues = newValues;
            InitGame();
        }
    }

    // Draws list view of all the algorithms available
    GuiListView({700, 350, 200, 155}, "Bubble Sort;Selection Sort;Insertion Sort;Merge Sort;Quick Sort", &ListViewIndexSel, &ListViewIndexActive);

    // Draws button to shuffle the rectangles
    if (GuiButton({300, 350, 150, 50}, "Shuffle")) {
        InitGame();
    }

    // Draws button to start sorting
    if (GuiButton({500, 350, 150, 50}, "Sort")) {
        if (completed) {
            InitGame();
        }
        if (ListViewIndexActive>-1) {
            counterI=0;
            counterJ=0;
            sortingMode=true;
        }
    }

    // Draws slider to customize speed of the sorting
    GuiSliderBar({700, 550,70,30},"Quick","Slow",&SliderSortingSpeed,maxSpeed,minSpeed);

    GuiCheckBox({400,600,30,30},"Show number of the values",&CheckBoxText);
    if (CheckBoxText && shownValues<=30){
        for (int i = 0; i < shownValues; i++) {
            DrawText(TextFormat("%.0f", value[i].height), value[i].x, value[i].y, 20,BLACK);
        }
    }
    if (CheckBoxText && shownValues>30) {
        DrawText("The number of the values are shown only if the values to sort are below or equal to 30",20,400,20,RED);
    }

    DrawText(TextFormat("Array accesses: %d",arrayAccesses),100,500,20,RED);
    DrawText(TextFormat("Comparisons performed: %d",comparisonsPerformed),100,540,20,RED);
    DrawText(TextFormat("Swaps performed: %d",swapsPerformed),100,580,20,RED);

    EndDrawing();
}

//Unload game (useless for now)
void UnloadGame() {
}

//Update and draw
void UpdateDrawFrame() {
    UpdateGame();
    DrawGame();
}

//Shuffle the rectangle positions
void shuffle() {
    for (int i = 0; i < shownValues; i++) {
        value[i].height = (GetRandomValue(1, 100));
    }
}

void completedAnimation() {
    if (completedAnimI<shownValues) {
        value[completedAnimI].active=false;
        value[completedAnimI].color=GREEN;
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