#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

//Structures
struct Values {
    float x;
    float y;
    float width;
    float height;
    bool active;
    Color color;
};

//Constants Variables
const int screenWidth = 1080;
const int screenHeight = 720;
const int maxValues = 100;

//Global variables
Values value[maxValues];
int shownValues = 5;
int newValues = 0;

int bubbleI=0;
int bubbleJ=0;
bool swapped =false;
bool completed = false;

float frameTime = 0.0;

int completedAnimI=0;

bool sortingMode = false;

// GUI Variables
bool ValueBox1EM = false;
int ListViewIndexSel;
int ListViewIndexActive = -1;

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
void bubbleSort();

int main() {
    InitWindow(screenWidth, screenHeight, "Template Raylib");
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
    value[0].active=true;

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

    if (sortingMode==true && delay(0.1)) {
        switch (ListViewIndexActive) {
            case 0: {
                bubbleSort();
                break;
            }
            case 1: {
                //selectionSort();
                break;
            }
            default: {
                break;
            }
        }
    }

    if (completed && delay(0.2)) {
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

        // !! TO DELETE shows value of the rectangle's height
        DrawText(TextFormat("%.0f", value[i].height), value[i].x, value[i].y, 20,BLACK);
    }

    // Draws box to insert the quantity of values to sort, minimum quantity of values is 5, maximum is decided by the constant. !!SHOULD ADD CONSTANT FOR MINIMUM TOO
    if (GuiValueBox({200, 350, 60, 20}, "Values to sort", &newValues, 5, maxValues, ValueBox1EM)) {
        ValueBox1EM = !ValueBox1EM;
        if (!ValueBox1EM) {
            shownValues = newValues;
            InitGame();
        }
    }

    // Draws list view of all the algorithms available
    GuiListView({700, 350, 200, 150}, "Bubble sort;Test2;Test3", &ListViewIndexSel, &ListViewIndexActive);
    if (ListViewIndexActive == -1) {
        DrawText(TextFormat("No algorithm selected"), 50, 50, 20,RED);
    } else {
        DrawText(TextFormat("Value: %d", ListViewIndexActive), 50, 50, 20,RED);
    }

    // Draws button to shuffle the rectangles
    if (GuiButton({300, 350, 150, 50}, "Shuffle")) {
        shuffle();
        InitGame();
    }

    if (GuiButton({500, 350, 150, 50}, "Sort")) {
        if (ListViewIndexActive>-1) {
            bubbleI=0;
            bubbleJ=0;
            sortingMode=true;
        }
    }

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


void bubbleSort() {
    if (bubbleI > shownValues - 1) {
        sortingMode = false;
        completed=true;
        return;
    }

    if (bubbleJ < shownValues - 1 - bubbleI) {
        if (value[bubbleJ].height > value[bubbleJ + 1].height) {
            float temp = value[bubbleJ].height;
            value[bubbleJ].height = value[bubbleJ + 1].height;
            value[bubbleJ + 1].height = temp;
            value[bubbleJ].active=false;
            value[bubbleJ+1].active=true;
            swapped = true;
        }
        value[bubbleJ].active=false;
        value[bubbleJ+1].active=true;
        bubbleJ++;
    } else {
        if (!swapped) {
            sortingMode = false;
            completed=true;
            return;
        }
        swapped = false;
        bubbleJ = 0;
        bubbleI++;
    }
}