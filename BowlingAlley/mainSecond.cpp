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
#include <vector>

using namespace std;

class Constants {
    public:
        static const int SPARE_BONUS = 5;
        static const int STRIKE_BONUS = 10;
        static const int TOTAL_SETS = 2;
        static const int TOTAL_PINS = 10;
};

class Player {
    private:
        string name;
        int lastScore;
        int totalScore;
        string scoreBoard;
    public:
        Player() {}
        Player(string name){
            this->name = name;
            lastScore = 0;
            totalScore = 0;
            scoreBoard = "";
        }

        //getter methods

        string getName() {
            return name;
        }

        int getLastScore() {
            return lastScore;
        }

        int getTotalScore() {
            return totalScore;
        }

        string getScoreBoard() {
            return scoreBoard;
        }

        void gotSpare() {
            totalScore += Constants().SPARE_BONUS;
        }

        void gotStrike() {
            totalScore += Constants().STRIKE_BONUS;
        }

        void updateScore(int pins, int chance, char input) {
            totalScore += pins;
            scoreBoard += input;

            switch (chance)
            {
            case 1:
                if(pins == 10) {
                    gotStrike();
                }
                //set the lastScore to the current score
                lastScore = pins;
                break;
            
            case 2:
                if(pins + lastScore == Constants().TOTAL_PINS) {
                    gotSpare();
                }
                //once both the sets are done then reset lastScore to 0
                lastScore = 0;
                break;
            
            default:
                cout << "Invalid Chance " << endl;
                break;
            }
        }

        // sort using the totalScore
        bool operator< (const Player &other) const {
            return totalScore < other.totalScore;
        }
};

class Bowling {
    vector<Player> players;
    Player winner;
    bool isLastSet;

    int convertCharToInt(char input) {
        return (input - '0');
    }

    void updatePlayerScore(Player &Player, int pins, int chance, char input) {
        Player.updateScore(pins, chance, input);
        displayScore();
    }

    void playChance(Player &player, int chance, char input) {
        // check if input is digit or not
        bool isNum = isdigit(input);
        int num = -1;
        if(isNum) {
            num = convertCharToInt(input);
            updatePlayerScore(player, num, chance, input);
        } else {
            if(input == 'X') {
                updatePlayerScore(player, 10, chance, input);
            } else if(input == '/') {
                int numOfPins = Constants().TOTAL_PINS - player.getLastScore();
                updatePlayerScore(player, numOfPins, chance, input);
            } else {
                cout << "Invalid Input " << endl;
            }
        }
    }

    void handleSpecialCase(Player &player, char input, int chance) {
        if(input == 'X') {
            cout << "Congratulations!! You got Strike in the last set. Two extra chance is given to you." << endl;
            char extraChance1;
            cin >> extraChance1;

            // two possibilities
            if(extraChance1 == 'X'){
                //again get strike then add the score and end the game.
                cout << "Again got strike. Game is ended. " << endl;
                playChance(player, chance+1, extraChance1);
                return;
            } else {
                playChance(player, chance+1, extraChance1);
                char extraChance2;
                cin >> extraChance2;
                playChance(player, chance+2, extraChance2);
                return;
            }

        } else if( input == '/') {
            // one more extra chance would be given
            cout << "Congratulations! You Got SPARE in the last set so one extra chance is given!" << endl;
            char ExtraInput;
            cin >> ExtraInput;
            //if got stike in the finalround then set chance as 1
            if(ExtraInput == 'X'){
                playChance(player, chance, ExtraInput);
            } else {
                playChance(player, chance+1, ExtraInput);
            }
            // one extra turn is given
            return;
        }
    }

    public:
        Bowling(vector<Player> players) {
            this->players = players;
            isLastSet = false;
        }

        void startGame() {
            for(int set=0;set<Constants().TOTAL_SETS;set++) {
                if(set == Constants().TOTAL_SETS - 1) {
                    isLastSet = true;
                }
                for(int p=0;p<players.size();p++) {
                    for(int chance=0;chance<2;chance++) {
                        char input;
                        cin >> input;
                        playChance(players[p], chance+1, input);

                        if(!isLastSet && input == 'X') {
                            break;
                        }

                        // handle the last set special case
                        if(isLastSet && (input == 'X' || input == '/')) {
                            handleSpecialCase(players[p], input, chance);
                            break;
                        }
                    }
                }
            }
        }


        void displayScore() {
            cout << "ScoreBoard: " << endl;
            for(auto it: players) {
                cout << it.getName() << ": " << it.getScoreBoard() << " -> " << it.getTotalScore() << endl;
            }
        }

        Player getWinner() {
            vector<Player> sortedPlayers = players;
            sort(sortedPlayers.begin(), sortedPlayers.end());
            return sortedPlayers.back();
        }

        
};

int main() {
    int noOfPlayers;
    cout << "No. of players: ";
    cin >> noOfPlayers;

    vector<Player> players;
    // create players
    for(int i=1;i<=noOfPlayers;i++) {
        string s1 = to_string(i);
        string name = "P";
        name += s1;
        Player p1(name);    
        players.push_back(p1);
    }

    Bowling game(players);

    game.startGame();


    Player winner = game.getWinner();

    cout << winner.getName() << " is the winner with " << winner.getTotalScore() << " score" << endl;

    return 0;
}