/*
    write machine code for single lane bowling Alley System

    Notes 
        - multiple players will play the game on single lane
        - scores will be maintained and shown by the system and winner will be declared at the end of the game

    Rules
        - A game consists of 10 sets.
        - In each set the player has two opportunities to knock down 10 pins.
        - The score for a set is the total number of pins knocked down, plus bonuses for strikes and spares.
        - A spare is when the player knocks down all ten pins in two tries.If there is spare the player gets 5 bonus points.
        - A strike is when the player knocks down all ten pins on his/her first try.If there is a strike the player gets 10 bonus points.
        - In the final set a player who rolls a spare or a strike is allowed to roll the extra balls to complete the set. However only a
          maximum of three balls can be rolled in the final set.

    Input
        - No. of players
        - Score of each shot for the player
        - Input Symbol "/" means spare and "X" means strike and 0-9 has usual meaning

    Output
        Current positions of the running games
    Example
        2

        8
        /
        X
        5

    Output - 
        Scoreboard: 
        P1: 8 
        P2: 0

        Scoreboard:
        P1: 8/ -> 15
        P2: 0

        Scoreboard:
        P1: 8/ -> 15
        P2: X -> 20

        Scoreboard:
        P1: 8/5 -> 20
        P2: X -> 20


*/

/*
    // lets start with the flow


    possibilities in the final set

    case 1 -> Got Strike
        - one more extra chance should be given.
            - case 1: Got strike again -> then end Game;
            - case 2: treated as normal 2 sets
    case 2 -> Got Spare
        - one extra chance given
    case 3 -> normal set
        - no extra chance is given

    - got strike in the first chance -> given one more chance

*/


#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Constants {
    public:
        static const int SPARE_BONUS = 5;
        static const int STRIKE_BONUS = 10;
        static const int TOTAL_SETS = 2;
        static const int TOTAL_PINS = 10;
};

class Player {
    int id;
    string name;
    string scoreBoard;
    int totalScore;
    int lastChanceScore;

    public:
        Player() {}
        Player(int id, string name) {
            this->id = id;
            this->name = name;
            totalScore = 0;
            lastChanceScore = 0;
            scoreBoard = "";
        }
        
        // getter methods
        int getId() {
            return id;
        }
        string getName() {
            return name;
        }

        string getScoreBoard() {
            return scoreBoard;
        }

        int getTotalScore() {
            return totalScore;
        }

        int getLastChanceScore() {
            return lastChanceScore;
        }

        void gotStrike() {
            totalScore += Constants().STRIKE_BONUS;
        }

        void gotSpare() {
            totalScore += Constants().SPARE_BONUS;
        }

        void pointScored(int pins, int chance, char input) {
            totalScore += pins;
            scoreBoard += input;
            if(chance == 1) {
                if(pins == 10) {
                    gotStrike();
                }

                // set lastChanceScore
                lastChanceScore = pins;
            } else if(chance == 2) {

                // check for spare
                if(lastChanceScore + pins == Constants().TOTAL_PINS) {
                    //got spare
                    gotSpare();
                }
                // again reset the lastChanceScore to 0
                lastChanceScore = 0;
            }
        }

};

class Bowling {
    public:
        vector<Player> players;

        Player winner;

        bool isLastSet;
        

        Bowling(vector<Player> players) {
            this->players = players;
            isLastSet = false;
        }

        void displayScore() {
            for(auto it: players) {
                cout << "Scoreboard: " << endl;
                cout << it.getName() << ": " << it.getScoreBoard() << " -> " << it.getTotalScore() << endl;
                // cout << "ID -> " << it.getId() << " Name -> " << it.getName() << " TotalScore -> " << it.getTotalScore() << endl;
            }
        }

        //  Scoreboard:
        // P1: 8/5 -> 20
        // P2: X -> 20

        void playChance(Player* player, int chance, char input) {
            int num = -1;
            bool isNum = isdigit(input); 
            // check if char is digit or not
            if(isNum) {
                //convert it in number
                num = input - '0';
            }

            if(!isNum) {
                if(input == 'X') {
                    player->pointScored(10, chance, input);
                    //if got strike then skip the 2nd chance
                } else if(input == '/') {
                    int calculatedInput = 10 - player->getLastChanceScore();
                    player->pointScored(calculatedInput, chance, input);
                } else {
                    cout << "Invalid Input" << endl;
                }
            } else {
                player->pointScored(num, chance, input);
            }
            // display score on every chance
            displayScore();
        }
        
        void startGame() {
            int noOfPlayers;
            cout << "Enter the Number of Players - ";
            cin >> noOfPlayers;

            for(int sets=0; sets<Constants().TOTAL_SETS ; sets++) {
                if(sets == Constants().TOTAL_SETS-1){
                    isLastSet = true;
                }
                for(int p=0; p<players.size(); p++) {
                    for(int chance=0; chance<2; chance++) {

                        char input;
                        cin >> input;
                        
                        // check if last set
                        playChance(&players[p], chance+1, input);

                        //if got strike then skip the 2nd chance
                        if(!isLastSet && input == 'X') {
                            break;
                        }

                        if(isLastSet) {
                            if(input == 'X') {
                                cout << "Congratulations!! You got Strike in the last set. Two extra chance is given to you." << endl;
                                char extraChance1;
                                cin >> extraChance1;

                                // two possibilities
                                if(extraChance1 == 'X'){
                                    //again get strike then add the score and end the game.
                                    cout << "Again got strike. Game is ended. " << endl;
                                    playChance(&players[p], chance+1, extraChance1);
                                    break;
                                } else {
                                    playChance(&players[p], chance+1, extraChance1);
                                    char extraChance2;
                                    cin >> extraChance2;
                                    playChance(&players[p], chance+2, extraChance2);
                                    break;
                                }
                            } else if(input == '/'){
                                // one more extra chance would be given
                                cout << "Congratulations! You Got SPARE in the last set so one extra chance is given!" << endl;
                                char ExtraInput;
                                cin >> ExtraInput;
                                //if got stike in the finalround then set chance as 1
                                if(ExtraInput == 'X'){
                                    playChance(&players[p], chance, ExtraInput);
                                } else {
                                    playChance(&players[p], chance+1, ExtraInput);
                                }
                                // one extra turn is given
                                break;
                            }   
                        }
                    }
                }       
            }

            // assign 1st player as winner
            winner = players[0];
            // once the game is finished assign winner
            for(int p=0; p<players.size(); p++) {
                if(players[p].getTotalScore() >= winner.getTotalScore()) {
                    winner = players[p];
                } 
            }
        }

};

int main() {

    Player p1(1, "Naman");
    Player p2(2, "Nipun");

    vector<Player> players;
    players.push_back(p1);
    players.push_back(p2); 
    Bowling game(players);

    game.startGame();

    cout << game.winner.getName() << " is the winner with " << game.winner.getTotalScore() << " score" << endl;
    
    return 0;
}



/*
what happen if the total score is same between two or more players.
*/