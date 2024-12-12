#include <iostream>
#include "BoardGame_Classes.h"
//#include "MinMaxPlayer.h"
#include "3x3X_O.h.h"
#include "connect4.h"
#include "Misere_X_O.h"
#include "X_Ogame.h"
#include "ultimate.h"
#include "SUS.h"
#include "Pyramic.h"

using namespace std;

int main() {
    cout<<"** Welcome to games app **"<<endl;
    while (true){
        cout<<"1- Numerical tic tac toe"<<endl;
        cout<<"2- Connect 4"<<endl;
        cout <<"3- Misere Tic Tac Toe"<< endl;
        cout <<"4- 5 x 5 Tic Tac Toe"<<endl;
        cout<< "5- Ultimate Tic Tac Toe"<<endl;
        cout << "6-SUS Tic Tac Toe"<< endl;
        cout<< "7- Exit"<<endl;
        cout<<"Enter your choice: "<<endl;
        string ccc ;
        cin>>ccc;
        while(ccc!="1"&&ccc!="2"&&ccc!="3" &&ccc!="4" && ccc!="5" && ccc!="6" &&ccc!="7" ){
            cout<<"Invalid input, please, try again: "<<endl;
            cin>>ccc;
        }

        if(ccc=="1"){
            Player<int>* players[2];
            Board<int>* B = new X_O_Board<int>;
            string playerXName, player2Name;

            cout << "Welcome to numerical X-O Game. \n";

            // Set up player 1
            cout << "Enter the odd Player name: ";
            cin >> playerXName;
            cout << "Choose the odd Player type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            string choice;
            cin >> choice;

            while(choice!="1" && choice!="2" && choice!="3"){
                cout << "Invalid choice for Player 1. Please try again: \n";
                cin>>choice;
            }
            if(choice =="1"){
                players[0] = new X_O_Player<int>(playerXName, 0);
            }
            else if(choice == "2"){
                players[0] = new X_O_Random_Player<int>(0, playerXName);
            }
            else {
//                players[0] = new X_O_MinMax_Player<int>(0);
//                players[0]->setBoard(B);
            }

            // Set up player 2
            cout << "Enter the even Player name: ";
            cin >> player2Name;
            cout << "Choose the even Player type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            while(choice!="1" && choice!="2" && choice!="3"){
                cout << "Invalid choice for Player 1. Please try again: \n";
                cin>>choice;
            }
            if(choice =="1"){
                players[1] = new X_O_Player<int>(player2Name, 0);
            }
            else if(choice == "2"){
                players[1] = new X_O_Random_Player<int>(0, player2Name);
            }
            else {
//              players[1] = new X_O_MinMax_Player<int>(0);
//              players[1]->setBoard(B);
            }

            // Create the game manager and run the game
            GameManager<int> x_o_game(B, players);
            x_o_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if(ccc=="2"){
            Player<char>* players[2];
            connect4Board<char>* cb = new connect4Board<char>();
            cout << "Welcome to connect 4 Game. :)\n";
            string playerXName, playerOName;
            cout << "Enter the X Player name: ";
            cin >> playerXName;
            cout << "Choose the odd Player type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            string choice;
            cin >> choice;

            while(choice!="1" && choice!="2" && choice!="3"){
                cout << "Invalid choice for Player 1. Please try again: \n";
                cin>>choice;
            }
            if(choice =="1"){
                players[0] = new connect4Player<char>(playerXName, 'X');
            }
            else if(choice == "2"){
                players[0] = new connect4_RandomPlayer<char>('X', playerXName);
            }
            else {
//            players[0] = new X_O_MinMax_Player<int>('X');
//            players[0]->setBoard(cb);
            }

            cout << "Enter the O Player name: ";
            cin >> playerOName;
            cout << "Choose the even Player type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> choice;

            while(choice!="1" && choice!="2" && choice!="3"){
                cout << "Invalid choice for Player 1. Please try again: \n";
                cin>>choice;
            }
            if(choice =="1"){
                players[1] = new connect4Player<char>(playerOName, 'O');
            }
            else if(choice == "2"){
                players[1] = new connect4_RandomPlayer<char>('O', playerOName);
            }
            else {
//            players[1] = new X_O_MinMax_Player<int>(0);
//            players[1]->setBoard(cb);
            }


            GameManager<char> connect4Game(cb, players);
            connect4Game.run();


            delete cb;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

        }
        else if (ccc == "3"){
            Player<char>* players[2];
            Misere_board<char>* B = new Misere_board<char>();
            Misere_board<char> board;
            cout << "===== Welcome to Misere XO Game ======\n";
            string playerXName, playerOName;
            cout << "Enter the name of the first player: ";
            cin >> playerXName;
            string  choice1 ,choice2;
            cout << "Select type for Player 1: \n1. Human player\n2. Random player: "<<endl;
            cin >> choice1;
            cout << "Enter the name of the second player: ";
            cin >> playerOName;
            cout << "Select one option for Player 2:\n1. Human player\n2. Random player: "<< endl;
            cin >> choice2;


            if (choice1 == "1"){
                players[0] = new Misere_Player<char>(playerOName, 'X');
            }
            else if (choice1 == "2"){
                players[0] = new Misere_Random_Player<char>('X',playerOName);
            }

            // set player 2

            if (choice2 == "1"){
                players[1] = new Misere_Player<char>(playerXName, 'O');
            }
            else if (choice2 == "2"){
                players[1] = new Misere_Random_Player<char>('O',playerXName);}

            GameManager<char>Misere_board(B,players);
            Misere_board.run();


            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

        }
        else if (ccc =="4"){
            Player<char>* players[2];
            X_Ogame_board<char>* B = new X_Ogame_board<char>();

            cout << "===== Welcome to 5x5 X_O Game ======\n";

            string name1, name2;
            cout << "Enter the name of the first player: ";
            cin >> name1;

            int choice;
            cout << "Select type for Player 1: \n1. Human player\n2. Random player: "<<endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new X_Ogame_player<char>(name1, 'X');
                    break;
                case 2:
                    players[0] = new X_Ogame_random_player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            cout << "Enter the name of the second player: ";
            cin >> name2;

            cout << "Select one option for Player 2:\n1. Human player\n2. Random player: "<< endl;
            cin >> choice;

            switch (choice) {
                case 1:
                    players[1] = new X_Ogame_player<char>(name2, 'O');
                    break;
                case 2:
                    players[1] = new X_Ogame_random_player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> x_o_game(B, players);
            x_o_game.run();
            B->display_result(name1 ,name2);


            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

        }
        else if(ccc=="5"){
            Player<char>* players[2];
            ultimateBoard<char>* B = new ultimateBoard<char>();
            cout << "===== Welcome to Misere XO Game ======\n";
            string playerXName, playerOName;
            cout << "Enter the name of the first player: ";
            cin >> playerXName;
            string  choice1 ,choice2;
            cout << "Select type for Player 1: \n1. Human player\n2. Random player: "<<endl;
            cin >> choice1;
            cout << "Enter the name of the second player: ";
            cin >> playerOName;
            cout << "Select one option for Player 2:\n1. Human player\n2. Random player: "<< endl;
            cin >> choice2;


            if (choice1 == "1"){
                players[0] = new ultimatePlayer<char>(playerXName, 'X');
            }
            else if (choice1 == "2"){
                players[0] = new ultimatRandomPlayer<char>('X',playerXName);
            }

            // set player 2

            if (choice2 == "1"){
                players[1] = new ultimatePlayer<char>(playerOName, 'O');
            }
            else if (choice2 == "2"){
                players[1] = new ultimatRandomPlayer<char>('O',playerOName);}

            GameManager<char>ultimate_board(B,players);
            ultimate_board.run();


            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (ccc =="6"){
            Player<char>* players[2];
    SUS_board<char>* B = new SUS_board<char>();

    cout << "===== Welcome to SUS Game ======\n";

    string name1, name2;
    cout << "Enter the name of the first player: ";
    cin >> name1;

    int choice;
    cout << "Select type for Player 1: \n1. Human player\n2. Random player: "<<endl;
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new SUS_player<char>(name1, 'S');
            break;
        case 2:
            players[0] = new SUS_random_player<char>('S');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    cout << "Enter the name of the second player: ";
    cin >> name2;

    cout << "Select one option for Player 2:\n1. Human player\n2. Random player: "<< endl;
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new SUS_player<char>(name2, 'U');
            break;
        case 2:
            players[1] = new SUS_random_player<char>('U');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    B->display_result(name1 ,name2);


    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

        }
        else{
            exit(0);
        }

    }
}
