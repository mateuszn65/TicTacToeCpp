//Mateusz Nowak
#include "raylib.h"
#include "game.h"
#include "utils.h"

void init();


int main() {
    init();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}



void init(){
    int width = 800;
    int height = 600;
    InitWindow(width, height, "TicTacToe");
    SetTargetFPS(60);
    float buttonWidth = 100;
    float buttonHeight = 40;
    float playButtonX = width / 2 - buttonWidth / 2;
    float playButtonY = height / 2 - buttonHeight / 2;
    Rectangle playButton =  { playButtonX, playButtonY, buttonWidth, buttonHeight};

    ButtonState btnState = Free;
    Vector2 mousePoint;
    InitAudioDevice();

    while (!WindowShouldClose()){
        //Draw
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        if (btnState == Free)
            DrawRectangleRec(playButton, BLUE);
        else
            DrawRectangleRec(playButton, DARKBLUE);
        DrawRectangleRoundedLines(playButton, 0.1, 0, 5, DARKBLUE);
        DrawText("Play!", playButtonX + 15, playButtonY + 5, 30, BLACK);

        EndDrawing();

        // Check button state
        mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, playButton))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = Pressed;
            else btnState = Hover;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                Game game;
                game.start();
                return;
            }

        }
        else btnState = Free;

    }
}