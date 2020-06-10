// Copyright 2019, Nawin

#include "Workspace.h"

#include <iostream>

void Game::run() {
  start();
  while (!have_winner()) {
    take_turn();
    std::cout << "Player " << get_winner() << " wins.\n";
  }
}