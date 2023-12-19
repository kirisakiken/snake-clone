#include "common.hpp"

#include <raymath.h>

const Color green = {173, 204, 96, 255};
const Color darkGreen = {43, 51, 24, 255};
const Color red = {235, 0, 0, 255};

double lastUpdateTime = 0;
const int cellSize = 30;
const int cellCount = 25; // (750,750) pixel grid
const int offset = 35; // width of the border

bool ElementInDeque(const std::deque<Vector2>& deque, const Vector2& element) {
  for (const Vector2& d : deque) {
    if (Vector2Equals(d, element)) {
      return true;
    }
  }

  return false;
}

bool eventTriggered(double currentTime, double& lastUpdateTime, double interval) {
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }

  return false;
}