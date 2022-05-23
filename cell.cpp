#include "cell.h"
Cell::Cell():
        state(Empty),
        position{0, 0, 0, 0}
{
}
Cell::Cell(float x, float y, float size, Texture2D cross, Texture2D circle):
        state(Empty),
        position{x, y, size, size},
        cross(cross),
        circle(circle)
{
}

void Cell::setState(CellState state) {
    this->state = state;
}

CellState Cell::getState() {
    return state;
}

Rectangle Cell::getPosition() {
    return position;
}

void Cell::draw() {
    if (state == Cross)
        DrawTexture(cross, position.x, position.y, BLUE);
    if (state == Circle)
        DrawTexture(circle, position.x, position.y, GREEN);

}



