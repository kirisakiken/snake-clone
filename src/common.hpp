#pragma once

#include <raylib.h>
#include <deque>

extern const Color green;
extern const Color darkGreen;
extern const Color red;

extern double lastUpdateTime;
extern const int cellSize;
extern const int cellCount;
extern const int offset;

extern bool ElementInDeque(const std::deque<Vector2>& deque, const Vector2& element);
extern bool eventTriggered(double currentTime, double& lastUpdateTime, double interval);
