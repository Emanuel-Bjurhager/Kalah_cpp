#include <iomanip>
#include <ios>

#include <iostream>
#include <string>

using namespace std; 



class KalahBoard{
public:
    int Player1Houses[6];
    int Player1Store;
    int Player2Houses[6];
    int Player2Store;

    //Init board
    KalahBoard(int seeds) 
        :Player1Store(0), Player2Store(0)
    {
        for(int i = 0; i != 6; i++){
            Player1Houses[i] = seeds;
        }
        for(int i = 0; i != 6; i++){
            Player2Houses[i] = seeds;
        }
        
    }

    //Prints current status of board to console
    void printBoard(){
        
        string topAndBottom = "";
        string row1 = "";
        string row2 = "";
        string row3 = "";


        //Add player1 store
        row2 = "* " + to_string(Player1Store) + ' ';
        int row2StartLength = row2.length();
        

        row1 = '*';
        //Add appropiate number of spaces to row1
        for(int i = 0; i != row2StartLength; i++ ){
            row1 += ' ';
        }
        //Add values to row 1
        for(int i = 0; i != 6; i++ ){
            row1 += '(' + to_string(i+1) + ')' + " - " + to_string(Player1Houses[i]) + "  ";
        }



        //Add spaces to row 2
        for(int i = 0; i != row1.length()-row2StartLength-1; i++ ){
            row2 += ' ';
        }
        //Add player2 store
        row2 += ' '+ to_string(Player2Store) + " *";




        //Add spaces and * to row1
        int currentLength = row1.length();
        for(int i = 0; i != row2.length()-currentLength-1; i++ ){
            row1 += ' ';
        }
            row1 += '*';





        row3 = '*';
        //Add appropiate number of spaces to row3
        for(int i = 0; i != row2StartLength; i++ ){
            row3 += ' ';
        }
        //Add values to row 3
        for(int i = 0; i != 6; i++ ){
            row3 += '(' + to_string(i+1) + ')' + " - " + to_string(Player2Houses[i]) + "  ";
        }

        //Add spaces and * to row3
        currentLength = row3.length();
        for(int i = 0; i != row2.length()-currentLength-1; i++ ){
            row3 += ' ';
        }
            row3 += '*';

        
        for(int i = 0; i != row2.length(); i++){
            topAndBottom += '*';
        }

        cout << topAndBottom <<endl;
        cout << row1 <<endl;
        cout << row2 <<endl;
        cout << row3 <<endl;
        cout << topAndBottom <<endl;
    }


    int Player1Move(int index){
        //Pick up all seeds
        int numberOfSeeds = Player1Houses[index];
        Player1Houses[index] = 0;
        //For keeping track of hand
        int currentHouse = index-1;
        bool Player2Side = false;
        

        //Put in appropiate houses
        while(numberOfSeeds != 0){
            //If we are in store
            if(currentHouse == -1){
                Player1Store++;
                currentHouse = 0;
                Player2Side = true;
                numberOfSeeds--;
            }

            //Our side
            if(Player2Side == false){
                while(currentHouse != -1 && numberOfSeeds != 0){
                    Player1Houses[currentHouse]++;  //Add one seed to house
                    numberOfSeeds--;
                    currentHouse--;                 //Move to next house
                }

            }
            //Opponents side
            else{
                if(currentHouse == 5){
                    Player2Houses[currentHouse]++;
                    Player2Side = false;
                    numberOfSeeds--;
                }
                while(currentHouse != 5 && numberOfSeeds != 0){
                    Player2Houses[currentHouse]++;  //Add one seed to house
                    currentHouse++;                 //Move to next house
                    numberOfSeeds--;
                }
            }

        }
        return currentHouse;
    }


    int Player2Move(int index){
        //Pick up all seeds
        int numberOfSeeds = Player2Houses[index];
        Player2Houses[index] = 0;
        //For keeping track of hand
        int currentHouse = index+1;
        bool Player1Side = false;
        

        //Put in appropiate houses
        while(numberOfSeeds != 0){
            //If we are in store
            if(currentHouse == 6){
                Player2Store++;
                currentHouse = 5;
                Player1Side = true;
                numberOfSeeds--;
            }

            //Our side
            if(Player1Side == false){
                while(currentHouse != 6 && numberOfSeeds != 0){
                    Player2Houses[currentHouse]++;  //Add one seed to house
                    numberOfSeeds--;
                    currentHouse++;                 //Move to next house
                }

            }
            //Opponent side
            else{
                if(currentHouse == 0){
                    Player1Houses[currentHouse]++;
                    Player1Side = false;
                    numberOfSeeds--;
                }
                while(currentHouse != 0 && numberOfSeeds != 0){
                    Player1Houses[currentHouse]++;  //Add one seed to house
                    currentHouse--;                 //Move to next house
                    numberOfSeeds--;
                }
            }

        }
        return currentHouse;
    }






    
};

int main(){ 


    KalahBoard board(6);
    int index, currentHouse;

    while(1){
        //Player 1's turn
        while(1){
            board.printBoard();
            cout << "Player 1 moves: " << endl;
            cin >> index;
            if (index < 1 || index > 6){
                cout << "Illegal move, try again!" << endl;
            }
            else{
                currentHouse = board.Player1Move(index-1);
                cout << currentHouse << endl;
                if (currentHouse != 0){
                    break;
                }
            }
        }
        //Player 2's turn
        while(1){
            board.printBoard();
            cout << "Player 2 moves: " << endl;
            cin >> index;
            if (index < 1 || index > 6){
                cout << "Illegal move, try again!" << endl;
            }
            else{
                currentHouse = board.Player2Move(index-1);
                cout << currentHouse << endl;
                if (currentHouse != 5){
                    break;
                }
            }
        }
        
        
    }
    


    return 0;
}
