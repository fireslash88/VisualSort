#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "main.h"
#include "bubbleSort.h"
#include "selectionSort.h"
#include "insertionSort.h"

//Structures

//Constants Variables
const int screenWidth = 1080;
const int screenHeight = 720;

const float maxSpeed=0.1;
const float minSpeed=2.0;

//Global variables

// GUI Variables
bool ValueBox1EM = false;
int ListViewIndexSel;

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

//Algorithms functions

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
    // CHECK IF ALL VARIABLES ARE INITIATED

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

    sortingMode = false;
    completed=false;
    completedAnimI=0;
}

//Update Game
void UpdateGame() {

    // Updates the frameTime variables incrementing it by the FrameTime of the program
    frameTime += GetFrameTime();

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
            default: {
                break;
            }
        }
    }

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

        if (value[i].active==true) {
            DrawRectangleV(position, size,RED);
        }else {
            DrawRectangleV(position, size,value[i].color);
        }

        // TO-ADD, BUTTON TO DECIDE TO SHOW OR NOT THE VALUE ONLY AVAILABLE WHEN THERE'S TOT. VALUES
        DrawText(TextFormat("%.0f", value[i].height), value[i].x, value[i].y, 20,BLACK);
    }

    // Draws box to insert the quantity of values to sort, minimum quantity of values is 5, maximum is decided by the constant.
    if (GuiValueBox({200, 350, 60, 20}, "Values to sort", &newValues, minValues, maxValues, ValueBox1EM)) {
        ValueBox1EM = !ValueBox1EM;
        if (!ValueBox1EM) {
            shownValues = newValues;
            InitGame();
        }
    }

    // Draws list view of all the algorithms available
    GuiListView({700, 350, 200, 150}, "Bubble Sort;Selection Sort;Insertion Sort;Merge Sort", &ListViewIndexSel, &ListViewIndexActive);
    if (ListViewIndexActive == -1) {
        DrawText(TextFormat("No algorithm selected"), 50, 50, 20,RED);
    } else {
        DrawText(TextFormat("Value: %d", ListViewIndexActive), 50, 50, 20,RED);
    }

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
    GuiSliderBar({700, 500,70,30},"Quick","Slow",&SliderSortingSpeed,maxSpeed,minSpeed);

    // TO DELETE, just for testing purpose
    DrawText(TextFormat("DeltaTime: %f", frameTime), 300, 600, 20, RED);

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