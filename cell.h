#ifndef TICTACTOE_CELL_H
#define TICTACTOE_CELL_H
#include "raylib.h"
#include "utils.h"

class Cell{
public:
    Cell();
    Cell(float x, float y, float size, Texture2D cross, Texture2D circle);
    void draw();
    void setState(CellState state);
    CellState getState();
    Rectangle getPosition();
private:
    Rectangle position;
    CellState state;
    Texture2D cross;
    Texture2D circle;
};
#endif //TICTACTOE_CELL_H
