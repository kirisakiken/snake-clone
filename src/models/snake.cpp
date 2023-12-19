#include "snake.hpp"

#include <raymath.h>
#include "../common.hpp"

void Snake::Draw() {
  for (const Vector2& cell : body) {
    Rectangle segment = Rectangle{
      offset + cell.x * cellSize,
      offset + cell.y * cellSize,
      (float) cellSize,
      (float) cellSize,
    };
    DrawRectangleRounded(segment, 0.5, 6, darkGreen);
  }
}

void Snake::Update() {
  if (addSegment) {
    body.push_front(Vector2Add(body.front(), direction));
    addSegment = false;
  } else {
    // move snake towards the direction
    body.pop_back();
    body.push_front(Vector2Add(body.front(), direction));
  }
}
