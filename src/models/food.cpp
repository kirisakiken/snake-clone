#include "food.hpp"

#include "../common.hpp"

Food::Food(const std::deque<Vector2>& snakeBody) {
    position = GenerateRandomPosition(snakeBody);
}

Vector2 Food::GenerateRandomPosition(const std::deque<Vector2>& snakeBody) {
    Vector2 pos = Vector2{
      (float)GetRandomValue(0, cellCount - 1),
      (float)GetRandomValue(0, cellCount - 1)
      };

    while (ElementInDeque(snakeBody, pos)) {
      pos = Vector2{
      (float)GetRandomValue(0, cellCount - 1),
      (float)GetRandomValue(0, cellCount - 1)
      };
    }

    return pos;
}

void Food::Draw() {
    DrawRectangle(
      offset + position.x * cellSize,
      offset + position.y * cellSize,
      cellSize,
      cellSize,
      red
      );
}
