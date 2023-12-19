#include <raylib.h>
#include <raymath.h>

#include "common.hpp"
#include "modules/game.hpp"

int main() {
  InitWindow(
    2 * offset + cellSize * cellCount,
    2 * offset + cellSize * cellCount,
    "Snake Clone"
  );

  SetTargetFPS(60);

  Game game = Game();

  while (!WindowShouldClose()) {
    // restart game input control
    if (IsKeyPressed(KEY_SPACE) && !game.running) {
      game.Restart();
    }

    // snake user input control
    if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
      game.snake.direction = {0, -1};
    } if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
      game.snake.direction = {0, 1};
    } if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
      game.snake.direction = {-1, 0};
    } if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
      game.snake.direction = {1, 0};
    }

    if (eventTriggered(GetTime(), lastUpdateTime, 0.1)) { // used for calling this block every 0.1seconds
      game.Update();
    }

    // ---
    BeginDrawing();
    ClearBackground(green);
    
    // Grid
    DrawRectangleLinesEx(
      Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10},
      5,
      darkGreen
    );

    // Display Title
    DrawText("Snake Clone", offset - 5, 5, 28 , darkGreen);
    // Display Score
    DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 28, darkGreen);
    
    // Display Game Over
    if (!game.running) {
      DrawText("Game Over!", (offset + (cellSize * cellCount)) / 4, (offset + (cellSize * cellCount)) / 2, 70, darkGreen);
      DrawText("Restart: SPACE BAR", (offset + (cellSize * cellCount)) / 4, (offset + (cellSize * cellCount)) / 4, 38, darkGreen);
    }

    game.Draw();

    EndDrawing();
    // ---
  }

  return 0;
}
