

#ifndef GAMES_CONNECT4_H
#define GAMES_CONNECT4_H

#include "BoardGame_Classes.h"

int ord=0;

template<typename T>
class connect4Board : public Board<T>{
private:
    bool foundPlace(int col);
public:
    connect4Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template<typename T>
class connect4Player : public Player<T>{
public:
    connect4Player(string name, T symbol);
    void getmove(int& x, int& y) ;
};

template<typename T>
class connect4_RandomPlayer : public RandomPlayer<T>{
public:
    connect4_RandomPlayer(T symbol, string name);
    void getmove(int &x, int &y) ;
};


//--------------------------Implementation-------------------------\\

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;


template<typename T>
bool connect4Board<T> ::foundPlace(int col) {
    if(this->board[0][col]==0){
        return true;
    }
    return false;
}

template<typename T>
connect4Board<T> ::connect4Board() {
    this->columns=7;
    this->rows=6;
    this->board= new char*[this->rows];
    for(int i=0; i<this->rows; i++){
        this->board[i]=new char[this->columns];
        for(int j=0; j<this->columns; j++){
            this->board[i][j]=0;
        }
    }
    this->n_moves=0;
}

template<typename T>
void connect4Board<T> ::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            if(this->board[i][j]==0){
                cout << "         |";
            }
            else if(this->board[i][j]!=0){
                cout << "    " << this->board[i][j] << "    |";
            }
        }
        cout << "\n-----------------------------------------------------------------------";}
    cout << "\n     0         1         2         3         4         5         6     ";
    cout<<endl;
}

template<typename T>
bool connect4Board<T> ::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0) && (foundPlace(y))) {
        for(int i=0; i< this->rows; i++){
            if(this->board[i][y]==0){
                x=i;
            }
        }
        this->n_moves++;
        ord= this->n_moves;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

// Returns true if there is any winner
template <typename T>
bool connect4Board<T>::is_win() {
    // vertically
    for(int i=0; i< this->columns; i++){
        if((this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[0][i]!=0)||
                (this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[3][i] == this->board[4][i] && this->board[1][i]!=0)||
                (this->board[2][i] == this->board[3][i] && this->board[3][i] == this->board[4][i] && this->board[4][i] == this->board[5][i] && this->board[2][i]!=0)){
            return true;
        }
    }

    // horizontally
    for(int i=0; i< this->rows; i++){
        if((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][0]!=0)||
            (this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][3] == this->board[i][4] && this->board[i][1]!=0)||
            (this->board[i][2] == this->board[i][3] && this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][2]!=0)||
            (this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][5] == this->board[i][6] && this->board[i][3]!=0)){
            return true;
        }
    }

    // top-left to down-right diagonal
    for(int i=0; i< this->rows; i++){
        for(int j=0; j<this->columns; j++){
            if(!(i+3< this->rows && j+3< this->columns)){
                break;
            }
            else{
                if(this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] && this->board[i+2][j+2] == this->board[i+3][j+3] && this->board[i][j]!=0){
                    return true;
                }
            }
        }
    }


    // up-right to bottom-left diagonal
    for(int i= 0; i< this->rows; i++){
        for(int j= this->columns-1; j>=0; j--){
            if(!(i+3< this->rows && j-3>=0)){
                break;
            }
            else{
                if(this->board[i][j] == this->board[i+1][j-1] && this->board[i+1][j-1] == this->board[i+2][j-2] && this->board[i+2][j-2] == this->board[i+3][j-3] && this->board[i][j]!=0){
                    return true;
                }
            }
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool connect4Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool connect4Board<T>::game_is_over() {
    return is_win() || is_draw();
}


// Constructor for X_O_Player
template <typename T>
connect4Player<T>::connect4Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void connect4Player<T>::getmove(int& x, int& y) {
    if(ord%2==0){
        cout<<"First player turn";
    }else{
        cout<<"Second player turn";
    }
    cout << "\nPlease enter the column you want from 0 to 7 to place the symbol into: ";
    cin >> y;
    x=0;
}

// Constructor for X_O_Random_Player
template <typename T>
connect4_RandomPlayer<T>::connect4_RandomPlayer(T symbol, string name) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void connect4_RandomPlayer<T>::getmove(int& x, int& y) {
    x = 0;
    y = rand() % this->dimension;
}




#endif //GAMES_CONNECT4_H
