#include "sfx_player.hpp"

SfxPlayer::SfxPlayer() {
  InitAudioDevice();
  eatSfx = LoadSound("resources/sfx/eat.wav");
  deadSfx = LoadSound("resources/sfx/dead.wav");
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
