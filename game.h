#ifndef TICTACTOE_GAME_H
#define TICTACTOE_GAME_H

#include "cell.h"
#include "raylib.h"

class Game{
public:
    Game();
    ~Game();
    void start();
private:
    float cellSize;
    Cell cells[3][3];
    GameState state;
    CellState currentMove;
    Texture2D board;
    Texture2D cross;
    Texture2D circle;
    Music music;
    Vector2 position;
    Vector2 winStartPos;
    Vector2 winEndPos;
    int moves;
    bool pause;
    void drawBoard();
    void finish();
    void handleMove();
    GameState isOver();
    void playAgain();
    void handleMusic();
};


#endif //TICTACTOE_GAME_H
