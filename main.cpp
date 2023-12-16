#include <deque>
#include <raylib.h>
#include <raymath.h>

const Color green = {173, 204, 96, 255};
const Color darkGreen = {43, 51, 24, 255};
const Color red = {235, 0, 0, 255};


// Configuration
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

class SfxPlayer {
private:
  Sound deadSfx;
  Sound eatSfx;
public:
  SfxPlayer();
  ~SfxPlayer();
  void PlayEatSfx();
  void PlayDeadSfx();
};

SfxPlayer::SfxPlayer() {
  InitAudioDevice();
  eatSfx = LoadSound("sfx/eat.wav");
  deadSfx = LoadSound("sfx/dead.wav");
}

SfxPlayer::~SfxPlayer() {
  UnloadSound(eatSfx);
  UnloadSound(deadSfx);
  CloseAudioDevice();
}

void SfxPlayer::PlayEatSfx() {
  PlaySound(eatSfx);
}

void SfxPlayer::PlayDeadSfx() {
  PlaySound(deadSfx);
}

class Snake {
public:
  std::deque<Vector2> body{Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  Vector2 direction = {1, 0};
  bool addSegment = false;
  void Draw();
  void Update();
};

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

class Food {
public:
  Food(const std::deque<Vector2>& snakeBody);
  Vector2 position;
  void Draw();
  Vector2 GenerateRandomPosition(const std::deque<Vector2>& snakeBody);
};

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