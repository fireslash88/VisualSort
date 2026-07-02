#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

//Structures
struct Values {
    float x;
    float y;
    float width;
    float height;
};

//Constants Variables
const int screenWidth=1080;
const int screenHeight=720;
const int maxValues=100;

//Global variables
Values value[maxValues];
int shownValues=5;
int newValues=0;

bool ValueBox1EM = false;

int ListViewIndexSel;
int ListViewIndexActive=-1;

float frameCounter=0;

//Main Functions
void InitGame();
void UpdateGame();
void DrawGame();
void UnloadGame();
void UpdateDrawFrame();

//Other functions
void randomize();

//Algorithms functions
void bubbleSort();

int main() {
    InitWindow( screenWidth, screenHeight, "Template Raylib");
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
    float rectSize=static_cast<float>(screenWidth)/static_cast<float>(shownValues);
    for (int i=0;i<shownValues;i++) {
        value[i].x=rectSize*static_cast<float>(i);
        value[i].y=300;
        value[i].width=rectSize;
        value[i].height=0;
    }
    randomize();

    ValueBox1EM = false;
}

//Update Game
void UpdateGame() {
    if (IsKeyPressed(KEY_SPACE)) {
        bubbleSort();
    }

    if (frameCounter<=5.0) {
        frameCounter+=GetFrameTime();
    }
}

//Draw game
void DrawGame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    GuiSetStyle(DEFAULT,TEXT_SIZE,20);

    // Draws all the values as rectangles, uses Vectors.
    for (int i=0;i<shownValues;i++) {
        Vector2 position = { value[i].x,value[i].y-value[i].height};
        Vector2 size = { value[i].width,value[i].height};

        DrawRectangleV(position,size,RED);
        DrawText(TextFormat("%.0f",value[i].height),value[i].x,value[i].y,20,BLACK);
    }

    // Draws box to insert the quantity of values to sort
    if (GuiValueBox({200,350,60,20},"Values to sort",&newValues,5,maxValues,ValueBox1EM)) {
        ValueBox1EM=!ValueBox1EM;
        if (!ValueBox1EM) {
            shownValues=newValues;
            InitGame();
        }
    }

    // Draws list view of all the algorithms available
    GuiListView({700,350,200,150},"Bubble sort;Test2;Test3",&ListViewIndexSel,&ListViewIndexActive);
    if (ListViewIndexActive==-1) {
        DrawText(TextFormat("No algorithm selected"),50,50,20,RED);
    }
    else {
        DrawText(TextFormat("Value: %d",ListViewIndexActive),50,50,20,RED);
    }

    if (GuiButton({300,350,150,50},"Shuffle")) {
        randomize();
    }

    DrawText(TextFormat("DeltaTime: %f",frameCounter),300,600, 20, RED);

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

void randomize() {
    for (int i=0;i<shownValues;i++) {
        value[i].height=(GetRandomValue(1,100));
    }
}

void bubbleSort() {
    bool swapped=false;
    for (int i=0;i<shownValues-1;i++) {
        for (int j=0;j<shownValues-1-i;j++) {
            if (value[j].height > value[j + 1].height) {
                float temp = value[j].height;
                value[j].height = value[j + 1].height;
                value[j + 1].height = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped=false;
    }

}