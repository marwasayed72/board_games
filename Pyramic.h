#ifndef PYRAMIC_H
#define PYRAMIC_H


#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

template <typename T>
class Pyramic_Board:public Board<T> {
public:
    Pyramic_Board ();
    bool update_board (int x , int y, T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Pyramic_Player : public Player<T> {
public:
    Pyramic_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Pyramic_Random_Player : public RandomPlayer<T>{
public:
    Pyramic_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

using namespace std;

// Constructor for Pyramic_Board
template <typename T>
Pyramic_Board<T>::Pyramic_Board() {
    this->rows = 3 ;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Pyramic_Board<T>::update_board(int x, int y, T symbol) {
    if (((x == 0 && y == 2) ||
         (x == 1 && y >= 1 && y <= 3) ||
         (x == 2 && y >= 0 && y <= 4)) && this->board[x][y]==0) {
        this->n_moves++;
        this->board[x][y] = symbol;
        return true;
    }
    return false; // Invalid move
}



// Display the board and the pieces on it
template <typename T>
void Pyramic_Board<T>::display_board() {
    cout << endl;
    cout << setw(28) << "|(0, 2) " << this->board[0][2] << " |" << endl;
    cout << "----------------------------------------------------------" << endl;

    for (int i = 1; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if ( (i == 1 && j < 4 && j > 0) || (i == 2)) {
                cout << "|(" << i << ", " << j << ") " << this->board[i][j] << " ";
            }
            else if (j == 4){
                continue;
            }
            else{
                cout << setw(12);
            }
        }

        cout << "|" << endl;
        cout << "----------------------------------------------------------" << endl;
    }
}



template <typename T>
bool Pyramic_Board<T>::is_win() {
    for (int i = 0; i < 3; ++i) {
        if ((this->board[2][i] == this->board[2][i+1] && this->board[2][i] ==
                                                         this->board[2][i+2] && this->board[2][i] !=0 ) || (this->board[1][i] == this->board[1][i+1] &&
                                                                                                            this->board[1][i] == this->board[1][i+2] && this->board[1][i] !=0)) {
            return true;
        }
    }
    if (((this->board[0][2] == this->board[1][2] && this->board[0][2] == this->board[2][2]) ||
         (this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0]) ||
         (this->board[0][2] == this->board[1][3] && this->board[0][2] == this->board[2][4])) &&
        (this->board[0][2] !=0)){
        return true;
    }
    return false;

}






// Return true if 9 moves are done and no winner
template <typename T>
bool Pyramic_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramic_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//////////////////////////////////////

// Constructor for Pyramic_Player
template <typename T>
Pyramic_Player<T>::Pyramic_Player(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void Pyramic_Player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (x, y) separated by space : ";
    cin >> x >> y;
}



// Constructor for X_O_Random_Player
template <typename T>
Pyramic_Random_Player<T>::Pyramic_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}



// getmove
template <typename T>
void Pyramic_Random_Player<T>::getmove(int& x, int& y) {
    if (this->dimension > 0) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    } else {
        x = 0;
        y = 0;
    }
}


#endif // PYRAMIC_H









