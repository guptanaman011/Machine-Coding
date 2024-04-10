/*
Build a Tic Tac Toe game
*/

#include <iostream>
#include <bits/stdc++.h>
#include <queue>

using namespace std;

class Constants {
    public:
        static const int BOARD_SIZE = 3;
};

class Player {
    private:
        string name;
    public:
        Player(){}
        Player(string name) {
            this->name = name;
        }
        string getPlayerName() {
            return name;
        }
};

class GameBoard {
    private:
        vector<vector<int>> board;
        queue<Player> players;
        Player winner;
        int chance;

        void initializeBoard() {
            for(int i=0;i<Constants().BOARD_SIZE;i++){
                vector<int> rows;
                for (int j=0;j<Constants().BOARD_SIZE;j++){
                    rows.push_back(-1);
                }
                board.push_back(rows);
            }
        }

        bool isValidInput(int x, int y) {
            if(board[x][y] != -1){
                return false;
            } else if(x > Constants().BOARD_SIZE-1 || y > Constants().BOARD_SIZE){
                return false;
            }
            return true;
        }

        void updateBoard(int x, int y, int chance) {
            board[x][y] = chance;
            printGameBoard();
        }

        void printGameBoard() {
            for(int i=0;i<Constants().BOARD_SIZE;i++) {
                for(int j=0;j<Constants().BOARD_SIZE;j++) {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        }

        bool checkForWin(int x, int y, int chance) {
            // check cols wise
            bool isWin = false;
            for(int col=0;col<Constants().BOARD_SIZE;col++) {
                if(board[x][col] != chance){
                    isWin =  false;
                    break;
                }
                isWin = true;
            }

            if(isWin) return true;

            //check row wise
            for(int row=0;row<Constants().BOARD_SIZE;row++){
                if(board[row][y] != chance) {
                    isWin =  false;
                    break;
                }
                isWin = true;
            }


            if(isWin) return true;

            //check diagonally 
            bool dia1Win = true;
            for(int i=0;i<Constants().BOARD_SIZE;i++) {
                if(board[i][i] != chance) {
                    dia1Win = false;
                    break;
                }
            }

            bool dia2Win = true;
            for(int i=0;i<Constants().BOARD_SIZE;i++) {
                if(board[i][Constants().BOARD_SIZE - 1 - i] != chance) {
                    dia2Win = false;
                    break;
                }
            }

            return dia1Win || dia2Win || isWin;
        }

    public:
        GameBoard(queue<Player> &players) {
            if(players.size() > 2) {    
                cout << "Only two players can play at a time." << endl;
            } else {
                this->players = players;
                this->chance = 0;
                //initalize board
                initializeBoard();
            }
        }

        void startGame() {
            while(players.size() > 1) {
                Player currPlayer = players.front();
                players.pop();
                cout << "Enter Input: ";
                int x,y;
                cin >> x >> y;
                // check for invalid input
                bool validInput = isValidInput(x,y);

                if(validInput){
                    updateBoard(x, y, chance);
                    //check if player win
                    bool isWin =  checkForWin(x,y,chance);

                    cout << "IS WIN " <<  isWin << endl;
                    if(isWin) {
                        winner = currPlayer;
                    } else {
                        players.push(currPlayer);
                    }
                    if(chance == 1) {
                        chance = 0;
                    } else {
                        chance = 1;
                    }
                } else {
                    cout << "Invalid Input!!" << endl;
                    break;
                }
            }
        }

        Player getWinner(){
            return winner;
        }
};

int main() {

    // create players
    Player p1("Naman");
    Player p2("Nipun");

    queue<Player> players;
    
    players.push(p1);
    players.push(p2);

    GameBoard game(players);

    game.startGame();

    Player winner = game.getWinner();

    cout <<  "Winner is " << winner.getPlayerName() << endl;

    cout << "Thanks for Playing!!" << endl;

    return 0;
}