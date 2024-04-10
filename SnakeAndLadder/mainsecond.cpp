#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <queue>

using namespace std;

class Player {
private:
    string playerName;
    int id;

public:
    Player(string playerName, int id) {
        this->playerName = playerName;
        this->id = id;
    }

    string getPlayerName() const {
        return playerName;
    }

    int getId() const {
        return id;
    }
};

class Dice {
private:
    int numOfDice;

public:
    Dice(int numOfDice) : numOfDice(numOfDice) {}

    int rollDice() const {
        int min = numOfDice * 1;
        int max = numOfDice * 6;
        return rand() % (max - min + 1) + min;
    }

    int getMinValue() {
        return numOfDice;
    }
};

class Jumper {
private:
    map<int, int> ladders;
    map<int, int> snakes;

public:
    Jumper(const map<int, int>& ladders, const map<int, int>& snakes) : ladders(ladders), snakes(snakes) {}

    int isLadderFound(int currPosition) const {
        auto it = ladders.find(currPosition);
        return it != ladders.end() ? it->second : -1;
    }

    int isSnakeFound(int currPosition) const {
        auto it = snakes.find(currPosition);
        return it != snakes.end() ? it->second : -1;
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
    GameBoard(const Dice& dice, const Jumper& jumper, queue<Player> players,
              map<string, int> playerCurrentPosition, int boardSize)
        : dice(dice), jumper(jumper), players(players), playerCurrentPosition(playerCurrentPosition), boardSize(boardSize) {}

    void startGame() {
        srand(time(0)); // Seed the random number generator

        while (players.size() > 1) {
            Player player = players.front();
            players.pop();

            int currentPosition = playerCurrentPosition[player.getPlayerName()];
            int diceValue = dice.rollDice();
            cout << "Previous Position" << currentPosition << endl;
            int nextPosition = currentPosition + diceValue;

            cout << "Next Position " << nextPosition << endl;
            if (nextPosition > boardSize) {
                // if  
                int minValueOfDice = dice.getMinValue();
                if((boardSize - currentPosition) < minValueOfDice) {
                    if(diceValue == minValueOfDice) {
                        cout << "Player " << player.getPlayerName() << " Won the GAME!!!" << endl;
                    }
                } else {
                    players.push(player);
                }
            } else if (nextPosition == boardSize) {
                cout << "Player " << player.getPlayerName() << " Won the GAME!!!" << endl;
            } else {
                int newPosition;
                if ((newPosition = jumper.isLadderFound(nextPosition)) != -1) {
                    cout << "Found Ladder!!!" << endl;
                } else if ((newPosition = jumper.isSnakeFound(nextPosition)) != -1) {
                    cout << "Found Snake!!!" << endl;
                } else {
                    newPosition = nextPosition;
                }

                playerCurrentPosition[player.getPlayerName()] = newPosition;
                players.push(player);
            }
        }
    }
};

int main() {
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
        {90, 2},
        {80, 23},
        {65, 32},
        {55, 10},
        {30, 2}
    };

    Jumper jumper(ladders, snakes);

    int boardSize = 100;
    GameBoard game(dice, jumper, players, playerCurrentPosition, boardSize);

    game.startGame();

    cout << "Thanks for playing!!" << endl;

    return 0;
}
