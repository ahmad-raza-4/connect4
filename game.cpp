#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include "grid.h"
#include "gridposition.h"
#include "player.h"

using namespace std;

class Game {
    private:
        Grid* grid;
        int connectN;
        vector<Player*> players;
        unordered_map<string, int>score;
        int targetScore;
    
    public:
        Game(Grid* gd, int cN, int tS): grid(gd), connectN(cN), targetScore(tS) {
            this->players = vector<Player*> {
                new Player("Player 1", YELLOW),
                new Player("Player 2", RED)
            };

            this->score = unordered_map<string, int>();
            for(Player* player : this->players)
                this->score[player->getName()] = 0;
        }

        void printBoard() {
            cout<<"board:"<<endl;

            vector<vector<int>>grid=this->grid->getGrid();

            for(int i=0;i<grid.size();i++) {
                string row="";
                for(int piece:grid[i]) {
                    if(piece==GridPosition::EMPTY)
                        row+="0 ";
                    else if(piece==GridPosition::YELLOW)
                        row+="Y ";
                    else
                        row+="R ";
                }
                cout<<row<<endl;
            }
            cout<<endl;
        }

        vector<int>playMove(Player* player) {
            printBoard();

            cout << player->getName() << "'s turn" << endl;
            int colCnt = this->grid->getColumnCount();

            cout << "enter col bw 0 and " << (colCnt-1) << " to add piece: ";

            int movcol = 0;
            cin >> movcol;

            int movrow = this->grid->placePiece(movcol, player->getPieceColor());

            return {movrow, movcol};
        }

        Player* playRound() {
            while(true) {
                for(Player* player: this->players) {
                    vector<int> pos = playMove(player);
                    int row = pos[0];
                    int col = pos[1];

                    GridPosition pieceColor = player->getPieceColor();

                    if(this->grid->checkWin(this->connectN, row, col, pieceColor)) {
                        this->score[player->getName()] = this->score[player->getName()] + 1;
                        return player;
                    }
                }
            }
        }

        void play() {
            int maxscore=0;
            Player* winner=nullptr;

            while(maxscore<this->targetScore) {
                winner=playRound();
                cout<<winner->getName()<<" won the round"<<endl;
                maxscore=max(this->score[winner->getName()], maxscore);

                this->grid->initGrid();
            }

            cout<<winner->getName()<<" won the game"<<endl;
        }
};


int main() {
    Grid* grid=new Grid(6,7);
    Game* game=new Game(grid, 4, 10);
    game->play();
    return 0;
}