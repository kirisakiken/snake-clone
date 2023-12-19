#include "game.hpp"

#include "../common.hpp"
#include <raymath.h>

Game::Game() : snake(Snake()), food(Food(snake.body)), sfxPlayer(SfxPlayer()) {}

void Game::Restart() {
  if (running) {
    return;
  }

  snake.body.clear();
  snake.body.push_back(Vector2{6, 9});
  snake.body.push_back(Vector2{5, 9});
  snake.body.push_back(Vector2{4, 9});
  snake.direction = {1, 0};
  running = true;
}

void Game::Draw() {
  food.Draw();
  snake.Draw();
}

void Game::Update() {
  if (!running) {
    return;
  }

  snake.Update();

  CheckSnakeFoodCollision();
  CheckSnakeWindowCollision();
  CheckSnakeSelfCollision();
}

void Game::CheckSnakeFoodCollision() {
  if (Vector2Equals(snake.body.front(), food.position)) {
    food.position = food.GenerateRandomPosition(snake.body);

    // grow the snake
    snake.addSegment = true;
    ++score;
    sfxPlayer.PlayEatSfx();
  }
}

void Game::CheckSnakeWindowCollision() {
  Vector2 head = snake.body.front();

  // X axis check
  if (head.x == cellCount || head.x == -1) {
    GameOver();
  }
  // Y axis check
  if (head.y == cellCount || head.y == -1) {
    GameOver();
  }
}

void Game::CheckSnakeSelfCollision() {
  std::deque<Vector2> cp(snake.body.begin() + 1, snake.body.end());
  if (ElementInDeque(cp, snake.body.front())) {
    GameOver();
  }
}

void Game::GameOver() {
  running = false;
  score = 0;
  sfxPlayer.PlayDeadSfx();
}