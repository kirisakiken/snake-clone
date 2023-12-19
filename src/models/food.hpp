#pragma once

#include <deque>
#include <raylib.h>

class Food {
public:
  Food(const std::deque<Vector2>& snakeBody);
  Vector2 position;
  void Draw();
  Vector2 GenerateRandomPosition(const std::deque<Vector2>& snakeBody);
};
