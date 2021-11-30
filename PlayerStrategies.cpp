#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy() : player(nullptr) {}
PlayerStrategy::~PlayerStrategy() {}
void PlayerStrategy::setPlayer(Player* player) {
    this->player = player;
}

