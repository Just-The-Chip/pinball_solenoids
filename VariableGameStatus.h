#pragma once
#include "Interfaces.h"

class VariableGameStatus : public GameStatus {
  public: 
    VariableGameStatus();
    virtual bool isGameActive();
    void setGameActive(bool isActive);

  protected:
    bool gameActive;
};