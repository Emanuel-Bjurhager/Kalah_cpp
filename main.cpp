#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "TextTable.h"

using namespace std;

class KalahBoard{
public:
    vector<int> Player1Houses;
    int Player1Store;
    vector<int> Player2Houses;
    int Player2Store;

    // Init board
    KalahBoard(int seeds)
        : Player1Houses(6, seeds), Player1Store(0), Player2Houses(6, seeds), Player2Store(0){}


    // Prints current status of board to console
    void printBoard(){

        TextTable table('-', '|', '+');

        // Button row
        table.add(" Button:  ");
        for (int i = 0; i != 6; i++){
            table.add("   " + to_string(i + 1) + "   ");
        }
        table.add("");
        table.endOfRow();

        // Player 1 row
        table.add("");
        for (int i = 0; i != 6; i++){
            table.add("   " + to_string(Player1Houses[i]));
        }
        table.add("");
        table.endOfRow();

        // Stores
        table.add("    " + to_string(Player1Store));
        for (int i = 0; i != 6; i++){
            table.add("");
        }
        table.add("    " + to_string(Player2Store) + "    ");
        table.endOfRow();

        // Player 2 row
        table.add("");
        for (int i = 0; i != 6; i++){
            table.add("   " + to_string(Player2Houses[i]));
        }
        table.add("");
        table.endOfRow();

        std::cout << table;
    }

    int Player1Move(int index){
        // Pick up all seeds
        int numberOfSeeds = Player1Houses[index];
        Player1Houses[index] = 0;
        // For keeping track of hand
        int currentHouse = index - 1;
        bool Player2Side = false;

        // Put in appropiate houses
        while (numberOfSeeds != 0){
            // If we are in store
            if (currentHouse == -1){
                Player1Store++;
                currentHouse = 0;
                Player2Side = true;
                numberOfSeeds--;
                // If we are out of seeds in our store
                if (numberOfSeeds == 0){
                    return -2;
                }
            }

            // Our side
            if (Player2Side == false){
                while (currentHouse != -1 && numberOfSeeds != 0){
                    Player1Houses[currentHouse]++; // Add one seed to house
                    numberOfSeeds--;
                    currentHouse--; // Move to next house
                }
            }
            // Opponents side
            else{
                if (currentHouse == 5){
                    Player2Houses[currentHouse]++;
                    Player2Side = false;
                    numberOfSeeds--;
                }
                while (currentHouse != 5 && numberOfSeeds != 0){
                    Player2Houses[currentHouse]++; // Add one seed to house
                    currentHouse++;                // Move to next house
                    numberOfSeeds--;
                }
            }
        }
        return currentHouse;
    }

    int Player2Move(int index){
        // Pick up all seeds
        int numberOfSeeds = Player2Houses[index];
        Player2Houses[index] = 0;
        // For keeping track of hand
        int currentHouse = index + 1;
        bool Player1Side = false;

        // Put in appropiate houses
        while (numberOfSeeds != 0){
            // If we are in store
            if (currentHouse == 6){
                Player2Store++;
                currentHouse = 5;
                Player1Side = true;
                numberOfSeeds--;
                // If we are out of seeds in our store
                if (numberOfSeeds == 0){
                    return -2;
                }
            }

            // Our side
            if (Player1Side == false){
                while (currentHouse != 6 && numberOfSeeds != 0){
                    Player2Houses[currentHouse]++; // Add one seed to house
                    numberOfSeeds--;
                    currentHouse++; // Move to next house
                }
            }
            // Opponent side
            else{
                if (currentHouse == 0){
                    Player1Houses[currentHouse]++;
                    Player1Side = false;
                    numberOfSeeds--;
                }
                while (currentHouse != 0 && numberOfSeeds != 0){
                    Player1Houses[currentHouse]++; // Add one seed to house
                    currentHouse--;                // Move to next house
                    numberOfSeeds--;
                }
            }
        }
        return currentHouse;
    }

    int playerHasEmptyHouses(){
        if (all_of(Player1Houses.begin(), Player1Houses.end(), [](int i){ return i == 0; })){
            return 1;
        }
        else if (all_of(Player2Houses.begin(), Player2Houses.end(), [](int i){ return i == 0; })){
            return 2;
        }
        else{
            return 0;
        }
    }

    bool isHouseEmpty(int player, int index){
        if (player == 1){
            if (Player1Houses[index] == 0){
                return true;
            }else{
                return false;
            }
        }else{
            if (Player2Houses[index] == 0){
                return true;
            }else{
                return false;
            }
        }
    }
};

int main(){

    KalahBoard board(6);
    int index, currentHouse;

    while (1){
        // Player 1's turn
        while (1){
            if (board.playerHasEmptyHouses() == 1){
                if (board.Player1Store > board.Player2Store){
                    cout << "Player 1 won!" << endl;
                    return 1;
                }else if (board.Player1Store == board.Player2Store){
                    cout << "Draw :|" << endl;
                    return 0;
                }
            }else{
                board.printBoard();
                cout << "Player 1 moves: " << endl;
                cin >> index;
                if (index < 1 || index > 6 || board.isHouseEmpty(1, index - 1) == true){
                    cout << "Illegal move, try again!" << endl;
                }else{
                    currentHouse = board.Player1Move(index - 1);
                    if (currentHouse != -2){
                        break;
                    }
                }
            }
        }
        // Player 2's turn
        while (1){
            if (board.playerHasEmptyHouses() == 2){
                if (board.Player1Store < board.Player2Store){
                    cout << "Player 2 won!" << endl;
                    return 2;
                }else if (board.Player1Store == board.Player2Store){
                    cout << "Draw :|" << endl;
                    return 0;
                }
            }else{
                board.printBoard();
                cout << "Player 2 moves: " << endl;
                cin >> index;
                //index = rand() % 6 + 1;
                cout << index <<endl;
                if (index < 1 || index > 6 || board.isHouseEmpty(2, index - 1) == true){
                    cout << "Illegal move, try again!" << endl;
                }else{
                    currentHouse = board.Player2Move(index - 1);
                    if (currentHouse != -2){
                        break;
                    }
                }
            }
        }
    }

    return -1;
}
