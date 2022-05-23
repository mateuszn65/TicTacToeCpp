#include "game.h"

Game::Game():
        position{175, 90},
        cellSize(150),
        moves(0),
        pause(false),
        state{NotFinished},
        currentMove{Cross},
        board{(LoadTexture("../assets/board.png"))},
        cross {LoadTexture("../assets/cross.png")},
        circle {LoadTexture("../assets/circle.png")},
        music{LoadMusicStream("../assets/country.mp3")}
{
    SetMusicVolume(music, 0.1 );
    PlayMusicStream(music);


    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cells[i][j] = Cell(i * 150 + position.x, j * 150 + position.y, cellSize - 5, cross, circle);
        }
    }

}

void Game::start() {
    while (!WindowShouldClose() && state == NotFinished){

        BeginDrawing();
        drawBoard();
        EndDrawing();

        handleMusic();
        handleMove();

    }
    finish();

}

void Game::handleMove() {
    Vector2 mousePoint = GetMousePosition();
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (CheckCollisionPointRec(mousePoint, cells[i][j].getPosition()))
            {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && cells[i][j].getState() == Empty){
                    moves++;
                    cells[i][j].setState(currentMove);
                    state = isOver();
                    if (state == NotFinished){
                        if (currentMove == Cross) currentMove = Circle;
                        else currentMove = Cross;
                    }
                }
            }
        }
    }
}

void Game::drawBoard() {
    ClearBackground(LIGHTGRAY);
    DrawTexture(board,position.x, position.y, YELLOW);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cells[i][j].draw();
        }
    }
}

void Game::finish() {
    float buttonWidth = 170;
    float buttonHeight = 40;
    float playButtonX = GetScreenWidth() / 2 - buttonWidth / 2;
    float playButtonY = 20;

    Rectangle playButton =  { playButtonX, playButtonY, buttonWidth, buttonHeight};

    ButtonState btnState;
    Vector2 mousePoint;
    while (!WindowShouldClose() && state != NotFinished){
        handleMusic();
        //Draw
        BeginDrawing();
        drawBoard();

        if (state == Won){
            DrawLineEx(winStartPos, winEndPos, 5, RED);
            if (currentMove == Cross)
                DrawText("Cross Won!", 10, 25, 30, BLACK);
            else
                DrawText("Circle Won!", 10, 25, 30, BLACK);
        }else{
            DrawText("You tied!", 10, 25, 30, BLACK);
        }

        //Play again button
        if (btnState == Free)
            DrawRectangleRec(playButton, BLUE);
        else
            DrawRectangleRec(playButton, DARKBLUE);
        DrawRectangleRoundedLines(playButton, 0.1, 0, 5, DARKBLUE);
        DrawText("Play Again!", playButtonX + 5, playButtonY + 5, 30, BLACK);
        EndDrawing();

        // Check button state
        mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, playButton))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = Pressed;
            else btnState = Hover;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                playAgain();
                return;
            }

        }
        else btnState = Free;
    }

}

GameState Game::isOver() {
    for (int i = 0; i < 3; i++){
        if (cells[i][0].getState() != Empty &&
            cells[i][0].getState() == cells[i][1].getState() &&
            cells[i][1].getState() == cells[i][2].getState()){
            winStartPos = Vector2{cells[i][0].getPosition().x + cellSize/2, cells[i][0].getPosition().y};
            winEndPos = Vector2{cells[i][2].getPosition().x + cellSize/2, cells[i][2].getPosition().y + cellSize};
            return Won;
        }
    }

    for (int i = 0; i < 3; i++){
        if (cells[0][i].getState() != Empty &&
            cells[0][i].getState() == cells[1][i].getState() &&
            cells[1][i].getState() == cells[2][i].getState()){
            winStartPos = Vector2{cells[0][i].getPosition().x, cells[0][i].getPosition().y+ cellSize/2};
            winEndPos = Vector2{cells[2][i].getPosition().x + cellSize, cells[2][i].getPosition().y + cellSize/2};
            return Won;
        }
    }

    if (cells[0][0].getState() != Empty &&
        cells[0][0].getState() == cells[1][1].getState() &&
        cells[1][1].getState() == cells[2][2].getState()){
        winStartPos = Vector2{cells[0][0].getPosition().x, cells[0][0].getPosition().y};
        winEndPos = Vector2{cells[2][2].getPosition().x + cellSize, cells[2][2].getPosition().y + cellSize};
        return Won;
    }

    if (cells[0][2].getState() != Empty &&
        cells[0][2].getState() == cells[1][1].getState() &&
        cells[1][1].getState() == cells[2][0].getState()){
        winStartPos = Vector2{cells[2][0].getPosition().x + cellSize, cells[2][0].getPosition().y};
        winEndPos = Vector2{cells[0][2].getPosition().x, cells[0][2].getPosition().y + cellSize};
        return Won;
    }

    if (moves == 9)
        return Tie;
    return NotFinished;
}

void Game::playAgain() {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cells[i][j].setState(Empty);
        }
    }
    moves = 0;
    state = NotFinished;
    currentMove = Cross;
    start();
}

void Game::handleMusic() {
    UpdateMusicStream(music);
    if (IsKeyPressed(KEY_SPACE))
    {
        StopMusicStream(music);
        PlayMusicStream(music);
    }

    // Pause/Resume music playing
    if (IsKeyPressed(KEY_P))
    {
        pause = !pause;
        if (pause) PauseMusicStream(music);
        else ResumeMusicStream(music);
    }
}

Game::~Game() {
    UnloadTexture(board);
    UnloadTexture(circle);
    UnloadTexture(cross);
    UnloadMusicStream(music);
}






