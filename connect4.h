#ifndef CONNECT4_H
#define CONNECT4_H

#include <QMainWindow>
#include <bits/stdc++.h>
using namespace std;

namespace Ui {
class Connect4;
}

class Connect4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Connect4(QWidget *parent = 0);
    ~Connect4();

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Connect4 *ui;
    int board[6][7];
    void show_message(int );
    void show_stone(int, int, int);
    void initialise(int board[6][7]);
    void print(int board[6][7]);
    bool legal_move(int board[6][7], int move);
    int  makemove(int board[6][7], int move, int stone);
    void undomove(int board[6][7], int move, int stone);
    bool ismoveleft(int board[6][7]);
    int GetBoard(int board[6][7], int row, int col);
    int checkforwin(int board[6][7], int movecol);
    int swap(int color);
    int piece1(int board[6][7], int x, int y, int color);
    int half_piece2(int board[6][7], int x, int y, int color);
    int piece2(int board[6][7], int x, int y, int color);
    int half_piece3(int board[6][7], int x, int y, int color);
    int piece3(int board[6][7], int x, int y, int color);
    int piece4(int board[6][7], int x, int y, int color);
    int evaluate(int board[6][7]);
    int minimax(int board[6][7], int move, int depth, bool isMax, int alpha, int beta);
    int bestmove(int board[6][7]);

};

#endif // CONNECT4_H
