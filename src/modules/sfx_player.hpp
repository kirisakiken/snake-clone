#pragma once

#include <raylib.h>

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
