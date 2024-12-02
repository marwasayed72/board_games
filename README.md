# board_games
#include <iostream>
#include "BoardGame_Classes.h"
#include "X_Ogame.h"

using namespace std;

int main() {
    Player<char>* players[2];
    X_Ogame_board<char>* B = new X_Ogame_board<char>();

    cout << "===== Welcome to X_O Game ======\n";

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

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}

