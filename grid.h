#ifndef GRID_H
#define GRID_H

#include <vector>
#include "gridposition.h"

using namespace std;

class Grid {
    private:
        int rows;
        int cols;
        vector<vector<int>>grid;
    
    public:
        Grid(int r, int c);
        void initGrid();
        vector<vector<int>>getGrid();
        int getRowCount();
        int getColumnCount();
        int placePiece(int col, GridPosition piece);
        bool checkWin(int connectN, int row, int col, GridPosition piece);
};

#endif