#include "player.h"

Player::Player(string nm, GridPosition pc): name(nm), piece(pc) {}

string Player::getName() {
    return this->name;
}

GridPosition Player::getPieceColor() {
    return this->piece;
}