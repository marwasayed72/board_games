#ifndef SUS_H_INCLUDED
#define SUS_H_INCLUDED

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T>
class SUS_board : public Board<T>
{
private:
    int p1points;
    int p2points;


public:
    SUS_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void initialize_game();
    void display_result(string Splayer , string Uplayer);
    void countpoints(int x, int y, T symbol);
};

template <typename T>
class SUS_player : public Player<T>
{
public:
    SUS_player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class SUS_random_player : public RandomPlayer<T> {
public:
    SUS_random_player(T symbol);
    void getmove(int& x, int& y);
};


template <typename T>
SUS_board<T>::SUS_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    initialize_game();
}


template <typename T>
void SUS_board<T>::initialize_game() {
    p1points = 0;
    p2points = 0;

}


template <typename T>
bool SUS_board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        countpoints(x, y, symbol);
        return true;
    }
    return false;
}


template <typename T>
void SUS_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0)
                cout << "  (" << i << "," << j << ")  |";
            else
                cout << "    " << this->board[i][j] << "    |";
        }
        cout << "\n----------------------------------------";
    }
    cout << endl;
}


template <typename T>
void SUS_board<T>::countpoints(int x, int y, T symbol) {
    static bool checked_conditions[8] = {false, false, false, false, false, false, false, false};


    if (!checked_conditions[0] && this->board[0][0] == 'S' && this->board[0][1] == 'U' && this->board[0][2] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[0] = true;
    }if (!checked_conditions[1] && this->board[1][0] == 'S' && this->board[1][1] == 'U' && this->board[1][2] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[1] = true;
    }
    if (!checked_conditions[2] && this->board[2][0] == 'S' && this->board[2][1] == 'U' && this->board[2][2] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[2] = true;
    }


    if (!checked_conditions[3] && this->board[0][0] == 'S' && this->board[1][0] == 'U' && this->board[2][0] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[3] = true;
    }
    if (!checked_conditions[4] && this->board[0][1] == 'S' && this->board[1][1] == 'U' && this->board[2][1] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[4] = true;
    }
    if (!checked_conditions[5] && this->board[0][2] == 'S' && this->board[1][2] == 'U' && this->board[2][2] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[5] = true;
    }



    if (!checked_conditions[6] && this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[6] = true;
    }


    if (!checked_conditions[7] && this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S') {
        if (symbol == 'S') p1points++;
        else if (symbol == 'U') p2points++;
        checked_conditions[7] = true;
    }

}




template <typename T>
bool SUS_board<T>::is_win() {
    if (this->n_moves == 9) {
        if (p1points != p2points) {
}}
    return false;




template <typename T>
bool SUS_board<T>::is_draw() {
    return ( this->n_moves==9 && !is_win());
}


template <typename T>
bool SUS_board<T>::game_is_over() {
    return this->n_moves == 9;
}


template <typename T>
void SUS_board<T>::display_result(string Splayer, string Uplayer) {
    cout << "\nGame Over!\n";
    cout << "(S)player points : "<< p1points<<endl;
    cout << "(U)player points : " <<p2points <<endl;

    if (p1points > p2points)
        cout << Splayer << " wins!\n";
    else if (p2points > p1points)
        cout << Uplayer << " wins!\n";
    else
        cout << "It's a draw!\n";

}


template <typename T>
SUS_player<T>::SUS_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (x, y) separated by space : ";
    cin >> x >> y;
}


template <typename T>
SUS_random_player<T>::SUS_random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void SUS_random_player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif // SUS_H_INCLUDED
