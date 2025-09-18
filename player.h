#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "gridposition.h"

using namespace std;

class Player {
    private:
        string name;
        GridPosition piece;

    public:
        Player(string nm, GridPosition pc);
        string getName();
        GridPosition getPieceColor();
};

#endif