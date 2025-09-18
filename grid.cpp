#include <iostream>
#include <stdexcept>
#include "grid.h"

using namespace std;

Grid::Grid(int r, int c): rows(r), cols(c) {
    initGrid();
}

void Grid::initGrid() {
    this->grid=vector<vector<int>>(rows, vector<int>(cols, GridPosition::EMPTY));
}

vector<vector<int>> Grid::getGrid() {
    return this->grid;
}

int Grid::getRowCount() {
    return this->rows;
}

int Grid::getColumnCount() {
    return this->cols;
}

int Grid::placePiece(int col, GridPosition piece) {
    if(col<0 || col>=this->cols)
        throw runtime_error("don't try to break my code bro");
    
    if(piece==GridPosition::EMPTY)
        throw runtime_error("bro, you can't place an empty piece");

    // use the lowest empty row in the given col
    for(int i=this->rows-1;i>=0;i--) {
        if(this->grid[i][col]==GridPosition::EMPTY) {
            this->grid[i][col]=piece;
            return i;
        }
    }
    return -1; // col full
}

        bool Grid::checkWin(int connectN, int row, int col, GridPosition piece) {
    // horizontal check
    int count=0;
    for(int j=0;j<this->cols;j++) {
        if(this->grid[row][j]==piece)
            count++;
        else 
            count=0;
        if(count==connectN)
            return true;
    }

    // vertical check
    count=0;
    for(int i=0;i<this->rows;i++) {
        if(this->grid[i][col]==piece)
            count++;
        else   
            count=0;
        if(count==connectN)
            return true;
    }
    
    // diagonal check 
    count=0;
    for(int i=0;i<this->rows;i++) {
        int j=row+col-i;
        if(j>=0 && j<this->cols && this->grid[i][j]==piece)
            count++;
        else
            count=0;
        if(count==connectN)
            return true;
    }

    // anti diagonal check
    count=0;
    for(int i=0;i<this->rows;i++) {
        int j=col-row+i;
        if(j>=0 && j<this->cols && this->grid[i][j]==piece)
            count++;
        else
            count=0;
        if(count==connectN)
            return true;
    }

    return false;
}