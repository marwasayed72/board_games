#ifndef X_OGAME_H
#define X_OGAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T>
class X_Ogame_board : public Board<T> {
private:
    int p1turns, p2turns;

public:
    X_Ogame_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void intialization();
    void display_result(string playerx , string playero);
    int count_successful_turns(int x, int y, T symbol);
};

template <typename T>
class X_Ogame_player : public Player<T> {
public:
    X_Ogame_player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_Ogame_random_player : public RandomPlayer<T> {
public:
    X_Ogame_random_player(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
X_Ogame_board<T>::X_Ogame_board() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    intialization();
}

template <typename T>
void X_Ogame_board<T>::intialization() {
    p1turns = 0;
    p2turns = 0;
}

template <typename T>
bool X_Ogame_board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void X_Ogame_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 0)
                cout << "  (" << i << "," << j << ")  |";
            else
                cout << "    " << this->board[i][j] << "    |";
        }
        cout << "\n---------------------------------------------------";
    }
    cout << endl;
}

template <typename T>
int X_Ogame_board<T>::count_successful_turns(int x, int y, T symbol) {
    int count = 0;

    if (y + 2 < 5 && this->board[x][y] == symbol && this->board[x][y + 1] == symbol && this->board[x][y + 2] == symbol)
        count++;
    if (x + 2 < 5 && this->board[x][y] == symbol && this->board[x + 1][y] == symbol && this->board[x + 2][y] == symbol)
        count++;
    if (x + 2 < 5 && y + 2 < 5 && this->board[x][y] == symbol && this->board[x + 1][y + 1] == symbol && this->board[x + 2][y + 2] == symbol)
        count++;
    if (x + 2 < 5 && y - 2 >= 0 && this->board[x][y] == symbol && this->board[x + 1][y - 1] == symbol && this->board[x + 2][y - 2] == symbol)
        count++;

    return count;
}

template <typename T>
bool X_Ogame_board<T>::is_win() {
    p1turns = p2turns = 0;
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->columns; y++) {
            if (this->board[x][y] == 'X')
                p1turns += count_successful_turns(x, y, 'X');
            else if (this->board[x][y] == 'O')
                p2turns += count_successful_turns(x, y, 'O');
        }
    }
    return false;
}

template <typename T>
bool X_Ogame_board<T>::is_draw() {
    return (this->n_moves == 24 && p1turns == p2turns);
}

template <typename T>
bool X_Ogame_board<T>::game_is_over() {
    return( this->n_moves==24);
}

template <typename T>
void X_Ogame_board<T>::display_result(string playerx ,string playero) {
    cout << "\nGame Over!\n";
    cout << "(X) Player successful formations: " << p1turns << endl;
    cout << "(O) Player successful formations: " << p2turns << endl;
    if (p1turns > p2turns)
        cout <<playerx<< " wins!\n";
    else if (p2turns > p1turns)
        cout << playero<<" wins!\n";
    else
        cout << "It's a draw!\n";
}

template <typename T>
X_Ogame_player<T>::X_Ogame_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_Ogame_player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (x, y) separated by space : ";
    cin >> x >> y;
}

template <typename T>
X_Ogame_random_player<T>::X_Ogame_random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_Ogame_random_player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
