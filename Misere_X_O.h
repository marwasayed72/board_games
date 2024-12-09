#ifndef MISERE_X_O_H
#define MISERE_X_O_H
#include "BoardGame_Classes.h"

template <typename T>
class Misere_board : public Board<T>{

public:
    Misere_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void play_game ();

};
template <typename T>

class Misere_Player : public Player<T> {
public:
    Misere_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};
template <typename T>
class Misere_Random_Player : public RandomPlayer<T>{
public:
    Misere_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for misere game
template <typename T>
Misere_board<T>::Misere_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T >
bool Misere_board<T>::update_board(int x ,int y ,T mark){
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {

        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    cout << "invalid move . try again" <<endl;
    return false;
}



// Display the board
template <typename T>
void Misere_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j]==0){
            cout << "  (" << i << "," << j << ")  |";}

            else if (this->board[i][j] !=0){
            cout << setw(2) << this->board[i][j] << "   |";}
        }
        cout << "\n------------------------------";
    }
    cout << endl;
}
// Returns true if there is any winner
template <typename T>
bool Misere_board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}
// Return true if 9 moves are done and no winner
template <typename T>
bool Misere_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Misere_board<T>::game_is_over() {
    return is_win() || is_draw();
}
// Constructor for X_O_Player
template <typename T>
Misere_Player<T>::Misere_Player (string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}
// Constructor for X_O_Random_Player
template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
    }  // Seed the random number generator

template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

template <typename T>
void play_game (Misere_board<T>&board , Player <T>&player1 , Player <T>&player2)
{
    int x , y ;
    Player <T>*currentplayer =&player1;
    Player <T>*nextplayer  =& player2;
    while (!board.game_is_over()){
        board.display_board();
      cout <<  currentplayer->getname()<< "'turns"<<endl;
        currentplayer->getmove(x ,y);
        while (!board.update_board(x,y,currentplayer->getsymbol())){
            cout << "invalid move ,please try again "<<endl;
            currentplayer->getmove (x ,y);
        }
        if (board.is_win()){
            cout << nextplayer->getname() << " losses\n" ;
            return ;
        }
        swap(currentplayer ,nextplayer);

    }
    if (board.is_draw()){
        cout << "game is draw " <<endl;
    }

}




#endif // MISERE_X_O_H_INCLUDED
