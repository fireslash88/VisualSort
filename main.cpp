#include <cstdlib>
#include <raylib.h>

//Structures
struct Values {
    int x;
    int y;
    int width;
    int height;
};

//Constants Variables
const int screenWidth=1080;
const int screenHeight=720;
const int maxValues=61;

//Global variables
Values value[maxValues];

//Main Functions
void InitGame();
void UpdateGame();
void DrawGame();
void UnloadGame();
void UpdateDrawFrame();

//Other functions
void Sort();

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
    float rectSize=1080.0/maxValues;
    for (int i=0;i<maxValues;i++) {
        value[i].x=static_cast<int>(rectSize)*i;
        value[i].y=300;
        value[i].width=(int)rectSize;
        value[i].height=2;
    }
    Sort();
}

//Update Game
void UpdateGame() {
}

//Draw game
void DrawGame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //Draw FPS
    DrawFPS(10,40);

    DrawText("Template Raylib", 10, 10, 20, GRAY);
    for (int i=0;i<maxValues;i++) {
        DrawRectangle(value[i].x,value[i].y-value[i].height,value[i].width,value[i].height,RED);
        DrawText(TextFormat("%d",value[i].height),value[i].x,value[i].y,20,BLACK);
    }

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

void Sort() {
    for (int i=0;i<maxValues;i++) {
        value[i].height=(GetRandomValue(1,100));
    }
}
