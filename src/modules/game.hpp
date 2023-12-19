#pragma once

#include "sfx_player.hpp"
#include "../models/snake.hpp"
#include "../models/food.hpp"

class Game {
public:
  Game();

  Snake snake;
  Food food;
  bool running = true;
  int score = 0;

  SfxPlayer sfxPlayer;

  void Restart();
  void Draw();
  void Update();

private:
  void CheckSnakeFoodCollision();
  void CheckSnakeWindowCollision();
  void CheckSnakeSelfCollision();
  void GameOver();
};
