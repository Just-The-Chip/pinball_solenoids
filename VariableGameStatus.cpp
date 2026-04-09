#include "VariableGameStatus.h"

VariableGameStatus::VariableGameStatus() {
  gameActive = false;
}

bool VariableGameStatus::isGameActive() {
  return gameActive;
}

void VariableGameStatus::setGameActive(bool isActive) {
  gameActive = isActive;
}