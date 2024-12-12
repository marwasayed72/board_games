
#ifndef GAMES_ULTIMATE_H
#define GAMES_ULTIMATE_H


#include "BoardGame_Classes.h"
using namespace std;

char implicitBoard[3][3]= {{0, 0, 0},
                           {0, 0, 0},
                           {0, 0, 0}};

int turns=0;
short move00=0, move01=0, move02=0, move10=0, move11=0, move12=0, move20=0, move21=0, move22=0;



template<typename T>
class ultimateBoard : public Board<T>{

public:
    ultimateBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};


template<typename T>
class ultimatePlayer : public Player<T>{
public:
    ultimatePlayer(string name, T symbol);
    void getmove(int& x, int& y) ;
};


template<typename T>
class ultimatRandomPlayer : public RandomPlayer<T>{
public:
    ultimatRandomPlayer(T symbol, string name);
    void getmove(int& x, int& y);
};


/////////////////////////////Implemetation\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

template<typename T>
ultimateBoard<T> :: ultimateBoard(){
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


template<typename T>
void ultimateBoard<T> ::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            if(this->board[i][j]==0){
                cout << "  (" << i << "," << j << ")  |";
            }
            else if(this->board[i][j]!=0){
                cout << "    " << this->board[i][j] << "    |";
            }
        }
        cout << "\n-------------------------------------------------------------------------------------------";
    }
    cout << endl;
}


template<typename T>
bool ultimateBoard<T> ::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        if(x<3 && y<3){
            if(implicitBoard[0][0]==0){
                move00++;
            }else{
                return false;
            }
        }
        else if(2<y && y<6 && x<3){
            if(implicitBoard[0][1]==0){
                move01++;
            }else{
                return false;
            }
        }

        else if(5<y && y<9 && x<3){
            if(implicitBoard[0][2]==0){
                move02++;
            }else{
                return false;
            }
        }
        else if(y<3 && 2<x && x<6){
            if(implicitBoard[1][0]==0){
                move10++;
            }else{
                return false;
            }
        }
        else if(y<6 && 2<y && x<6 && x>2){
            if(implicitBoard[1][1]==0){
                move11++;
            }else{
                return false;
            }
        }
        else if(5<y && y<9 && x<6 && x>2){
            if(implicitBoard[1][2]==0){
                move12++;
            }else{
                return false;
            }
        }
        else if(x>5 && x<9 && y<3){
            if(implicitBoard[2][0]==0){
                move20++;
            }else{
                return false;
            }
        }
        else if(x>5 && x<9 && 2<y && y<6){
            if(implicitBoard[2][1]==0){
                move21++;
            }else{
                return false;
            }
        }
        else if(x>5 && x<9 && 5<y && y<9){
            if(implicitBoard[2][2]==0){
                move22++;
            }else{
                return false;
            }
        }
        this->n_moves++;
        turns= this->n_moves;
        this->board[x][y] = mark;
        return true;
    }
    return false;
}


template<typename T>
bool ultimateBoard<T> ::is_win() {
    // Check rows and columns of small square 0 0
    for (int i = 0; i < 3; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i]  && this->board[0][i] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[0][0]='O';
            }else{
                implicitBoard[0][0]='X';
            }
            move00=9;
        }
    }
    // Check diagonals of small square 0 0
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[0][0]='O';
        }else{
            implicitBoard[0][0]='X';
        }
        move00=9;
    }

    // Check rows and columns of small square 0 1
    for (int i = 0; i < 3; i++) {
        if ((this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][3] != 0) ||
            (this->board[0][i+3] == this->board[1][i+3] && this->board[1][i+3] == this->board[2][i+3]  && this->board[0][i+3] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[0][1]='O';
            }else{
                implicitBoard[0][1]='X';
            }
            move01=9;
        }
    }
    // Check diagonals of small square 0 1
    if ((this->board[0][3] == this->board[1][4] && this->board[1][4] == this->board[2][5] && this->board[0][3] != 0) ||
        (this->board[0][5] == this->board[1][4] && this->board[1][4] == this->board[2][3] && this->board[0][5] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[0][1]='O';
        }else{
            implicitBoard[0][1]='X';
        }
        move01=9;
    }
    // Check rows and columns of small square 0 2
    for (int i = 0; i < 3; i++) {
        if ((this->board[i][6] == this->board[i][7] && this->board[i][7] == this->board[i][8] && this->board[i][6] != 0) ||
            (this->board[0][i+6] == this->board[1][i+6] && this->board[1][i+6] == this->board[2][i+6]  && this->board[0][i+6] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[0][2]='O';
            }else{
                implicitBoard[0][2]='X';
            }
            move02=9;
        }
    }
    // Check diagonals of small square 0 2
    if ((this->board[0][6] == this->board[1][7] && this->board[1][7] == this->board[2][8] && this->board[0][6] != 0) ||
        (this->board[0][8] == this->board[1][7] && this->board[1][7] == this->board[2][6] && this->board[0][8] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[0][2]='O';
        }else{
            implicitBoard[0][2]='X';
        }
        move02=9;
    }
    // Check rows and columns of small square 1 0
    for (int i = 3; i < 6; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[3][i-3] == this->board[4][i-3] && this->board[4][i-3] == this->board[5][i-3]  && this->board[3][i-3] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[1][0]='O';
            }else{
                implicitBoard[1][0]='X';
            }
            move10=9;
        }
    }
    // Check diagonals of small square 1 0
    if ((this->board[3][0] == this->board[4][1] && this->board[4][1] == this->board[5][2] && this->board[3][0] != 0) ||
        (this->board[3][2] == this->board[4][1] && this->board[4][1] == this->board[5][0] && this->board[3][2] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[1][0]='O';
        }else{
            implicitBoard[1][0]='X';
        }
        move10=9;
    }
    // Check rows and columns of small square 1 1
    for (int i = 3; i < 6; i++) {
        if ((this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][3] != 0) ||
            (this->board[3][i] == this->board[4][i] && this->board[4][i] == this->board[5][i]  && this->board[3][i] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[1][1]='O';
            }else{
                implicitBoard[1][1]='X';
            }
            move11=9;
        }
    }
    // Check diagonals of small square 1 1
    if ((this->board[3][3] == this->board[4][4] && this->board[4][4] == this->board[5][5] && this->board[3][3] != 0) ||
        (this->board[3][5] == this->board[4][4] && this->board[4][4] == this->board[5][3] && this->board[3][5] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[1][1]='O';
        }else{
            implicitBoard[1][1]='X';
        }
        move11=9;
    }
    // Check rows and columns of small square 1 2
    for (int i = 3; i < 6; i++) {
        if ((this->board[i][6] == this->board[i][7] && this->board[i][7] == this->board[i][8] && this->board[i][6] != 0) ||
            (this->board[3][i+3] == this->board[4][i+3] && this->board[4][i+3] == this->board[5][i+3]  && this->board[3][i+3] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[1][2]='O';
            }else{
                implicitBoard[1][2]='X';
            }
            move12=9;
        }
    }
    // Check diagonals of small square 1 2
    if ((this->board[3][6] == this->board[4][7] && this->board[4][7] == this->board[5][8] && this->board[3][6] != 0) ||
        (this->board[3][8] == this->board[4][7] && this->board[4][7] == this->board[5][6] && this->board[3][8] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[1][2]='O';
        }else{
            implicitBoard[1][2]='X';
        }
        move12=9;
    }
    // Check rows and columns of small square 2 0
    for (int i = 6; i < 9; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[6][i-6] == this->board[7][i-6] && this->board[7][i-6] == this->board[8][i-6]  && this->board[6][i-6] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[2][0]='O';
            }else{
                implicitBoard[2][0]='X';
            }
            move20=9;
        }
    }
    // Check diagonals of small square 2 0
    if ((this->board[6][0] == this->board[7][1] && this->board[7][1] == this->board[8][2] && this->board[6][0] != 0) ||
        (this->board[6][2] == this->board[7][1] && this->board[7][1] == this->board[8][0] && this->board[6][2] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[2][0]='O';
        }else{
            implicitBoard[2][0]='X';
        }
        move20=9;
    }
    // Check rows and columns of small square 2 1
    for (int i = 6; i < 9; i++) {
        if ((this->board[i][3] == this->board[i][4] && this->board[i][4] == this->board[i][5] && this->board[i][3] != 0) ||
            (this->board[6][i-3] == this->board[7][i-3] && this->board[7][i-3] == this->board[8][i-3]  && this->board[6][i-3] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[2][1]='O';
            }else{
                implicitBoard[2][1]='X';
            }
            move21=9;
        }
    }
    // Check diagonals of small square 2 1
    if ((this->board[6][3] == this->board[7][4] && this->board[7][4] == this->board[8][5] && this->board[6][3] != 0) ||
        (this->board[6][5] == this->board[7][4] && this->board[7][4] == this->board[8][3] && this->board[6][5] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[2][1]='O';
        }else{
            implicitBoard[2][1]='X';
        }
        move21=9;
    }
    // Check rows and columns of small square 2 2
    for (int i = 6; i < 9; i++) {
        if ((this->board[i][6] == this->board[i][7] && this->board[i][7] == this->board[i][8] && this->board[i][6] != 0) ||
            (this->board[6][i] == this->board[7][i] && this->board[7][i] == this->board[8][i]  && this->board[6][i] != 0)){
            if(this->n_moves %2 == 0){
                implicitBoard[2][2]='O';
            }else{
                implicitBoard[2][2]='X';
            }
            move22=9;
        }
    }
    // Check diagonals of small square 2 2
    if ((this->board[6][6] == this->board[7][7] && this->board[7][7] == this->board[8][8] && this->board[6][6] != 0) ||
        (this->board[6][8] == this->board[7][7] && this->board[7][7] == this->board[8][6] && this->board[6][8] != 0)) {
        if(this->n_moves %2 == 0){
            implicitBoard[2][2]='O';
        }else{
            implicitBoard[2][2]='X';
        }
        move22=9;
    }


    //check winner of the whole board
    for (int i = 0; i < 3; i++) {
        if ((implicitBoard[i][0] == implicitBoard[i][1] && implicitBoard[i][1] == implicitBoard[i][2] && implicitBoard[i][0] != 0) ||
            (implicitBoard[0][i] == implicitBoard[1][i] && implicitBoard[1][i] == implicitBoard[2][i]  && implicitBoard[0][i] != 0)){
            for(int k=0; k<3; k++){
                for(int l=0; l<3; l++){
                    implicitBoard[k][l]=0;
                }
            }
            turns=0;
            move00=0, move01=0, move02=0, move10=0, move11=0, move12=0, move20=0, move21=0, move22=0;
            return true;
        }
    }
    // Check diagonals of small square 0 0
    if ((implicitBoard[0][0] == implicitBoard[1][1] && implicitBoard[1][1] == implicitBoard[2][2] && implicitBoard[0][0] != 0) ||
        (implicitBoard[0][2] == implicitBoard[1][1] && implicitBoard[1][1] == implicitBoard[2][0] && implicitBoard[0][2] != 0)) {
        for(int k=0; k<3; k++){
            for(int l=0; l<3; l++){
                implicitBoard[k][l]=0;
            }
        }
        turns=0;
        move00=0, move01=0, move02=0, move10=0, move11=0, move12=0, move20=0, move21=0, move22=0;
        return true;
    }
    return false;
}

template<typename T>
bool ultimateBoard<T> ::is_draw() {
    if((move00+move01+move02+move10+move11+move12+move20+move21+move22==81) && !is_win()){
        for(int k=0; k<3; k++){
            for(int l=0; l<3; l++){
                implicitBoard[k][l]=0;
            }
        }
        turns=0;
        move00=0, move01=0, move02=0, move10=0, move11=0, move12=0, move20=0, move21=0, move22=0;
    }
    return ((move00+move01+move02+move10+move11+move12+move20+move21+move22==81) && !is_win());
}

template<typename T>
bool ultimateBoard<T> ::game_is_over() {
    return (is_win() || is_draw());
}


template<typename T>
ultimatePlayer<T> ::ultimatePlayer(string name, T symbol) : Player<T>(name, symbol){}

template<typename T>
void ultimatePlayer<T> ::getmove(int &x, int &y) {
    if(turns%2==0){
        cout<<"First player turn";
    }else{
        cout<<"Second player turn";
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: "<<endl;
    cin >> x >> y;
}


template<typename T>
ultimatRandomPlayer<T> ::ultimatRandomPlayer(T symbol, string name) : RandomPlayer<T>(symbol){
    this->dimension = 9;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void ultimatRandomPlayer<T> ::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
