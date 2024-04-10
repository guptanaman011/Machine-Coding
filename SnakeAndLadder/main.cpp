/*
Requirements
    - Multiplayer Game
    - Customizable board in terms of snake and ladder placement and board size
    - Customizable in terms of number of dice used
    - When Game board loads it should be
        - Load the configured board size
        - Load the configured snake and ladder
        - Load the configured number of dice
        - Load the number of players who will play the game and all player should be at starting location. 
*/

#include <iostream>
#include <bits/stdc++.h>
#include <map>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

//  All the player related entities will be present inside the player class
class Player {
    private: 
        string playerName;
        int id;
    public:
        Player(string playerName, int id) {
            this->playerName = playerName;
            this->id = id;
        }
        string getPlayerName() {
            return playerName;
        }
};
 
class Dice {
    private:
        int numOfDice;
    public: 
        Dice() {}
        Dice(int numOfDice) {
            this->numOfDice = numOfDice;
        }

        int rollDice() {
            srand(time(0));
            int min = numOfDice * 1;
            int max = numOfDice * 6;
            int randomNumber = rand() % (max - min + 1) + min;
            return randomNumber;
        }

        int getMinValue() {
            return numOfDice;
        }
};




// this class is for ladders and snake 
// startPoint < endPoint (in case of ladder)
// endPoint < startPoint (in case of snake)
class Jumper {
    private:
        map <int, int> ladders;
        map <int, int> snakes;
    public:
        Jumper() {}
        Jumper(map<int, int> ladders, map<int, int> snakes) {
            this->ladders = ladders;
            this->snakes = snakes;
        }

        int isLadderFound(int currPosition) {
            if(ladders.find(currPosition) != ladders.end()) {
                return ladders[currPosition];
            }
            return -1;
        }

        int isSnakeFound(int currPosition) {
            if(snakes.find(currPosition) != snakes.end()) {
                return snakes[currPosition];
            }
            return -1;
        }
        
};

class GameBoard {
    private:
        Dice dice;
        Jumper jumper;
        queue<Player> players;
        map<string, int> playerCurrentPosition;
        int boardSize;

    public:
        GameBoard(Dice &dice, Jumper &jumper, queue<Player> &players, map<string, int> &playerCurrentPosition, int &boardSize) {
            this->dice = dice;
            this->jumper = jumper;
            this->players = players;
            this->playerCurrentPosition = playerCurrentPosition;
            this->boardSize = boardSize;
        }
        void startGame() {
            // Game should continue until and unless only single player is left
            while(players.size() > 1) {
                // take out player from queue
                Player player = players.front();
                players.pop();

                int currentPosition = playerCurrentPosition[player.getPlayerName()];
                int diceValue = dice.rollDice();
                int nextPosition = currentPosition + diceValue;
                
                cout << "NEXT Position " << nextPosition << endl;
                // check if nextposition is out of board size
                if(nextPosition > boardSize) {
                    int minValueOfDice = dice.getMinValue();
                    if((boardSize - currentPosition) < minValueOfDice) {
                        if(diceValue == minValueOfDice) {
                            cout << "Player " << player.getPlayerName() << " Won the GAME!!!" << endl;
                        }
                    } else {
                        players.push(player);
                    }
                } else if(nextPosition == boardSize) {
                    cout << "Player " << player.getPlayerName() << " Won the GAME!!!" << endl;
                } else {
                    int newPosition;
                    // check for the ladder or snake
                    if(jumper.isLadderFound(currentPosition) != -1){
                        cout << "Found Ladder!!!" << endl;
                        newPosition = jumper.isLadderFound(currentPosition);
                    } else if(jumper.isSnakeFound(currentPosition) != -1){
                        cout << "Found SNake!!!!" << endl;
                        newPosition = jumper.isSnakeFound(currentPosition);                     
                    } else{
                        newPosition = nextPosition;
                    }
                    playerCurrentPosition[player.getPlayerName()] = newPosition;
                    players.push(player);
                }
            }
        }

};

int main() {
    srand(time(0));
    Player p1("Naman", 1);
    Player p2("Nipun", 2);
    Player p3("Aastha", 3);
    Player p4("Bhisham", 4);

    queue<Player> players;
    players.push(p1);
    players.push(p2);
    players.push(p3);
    players.push(p4);

    map<string, int> playerCurrentPosition;
    playerCurrentPosition[p1.getPlayerName()] = 0;
    playerCurrentPosition[p2.getPlayerName()] = 0;
    playerCurrentPosition[p3.getPlayerName()] = 0;
    playerCurrentPosition[p4.getPlayerName()] = 0;


    Dice dice(2);

    map<int, int> ladders{
        {2, 20},
        {12, 22},
        {20, 30},
        {25, 40},
        {45, 99}
    };

    map<int, int> snakes{
        {90, 1},
        {80, 23},
        {65, 31},
        {55, 9},
        {30, 11}
    };

    Jumper jumper(ladders, snakes);

    int boardSize = 100;
    GameBoard game(dice, jumper, players, playerCurrentPosition, boardSize);

    game.startGame();

    cout << "Thanks for playing!!" << endl;


    return 0;
}