#include "connect4.h"
#include "ui_connect4.h"
#include <QMessageBox>

Connect4::Connect4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Connect4)
{
    ui->setupUi(this);
    initialise(board);
}

Connect4::~Connect4()
{
    delete ui;
}
void Connect4::initialise(int board[6][7])
{
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 7; ++j)
            board[i][j] = 0;
}
/*void Connect4::print(int board[6][7])
{
    system("clear");
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(i == 0 or j == 0 or i == 7 or j == 8)
                cout <<"* ";
            else
                cout << board[i-1][j-1] << " ";
        }
        cout << "\n";
    }
    cout << "* ";
    for(int i = 0; i < 7; ++i)
        cout << i << " ";
    cout << "* ";
    cout << endl;
}*/
bool Connect4::legal_move(int board[6][7], int move)
{
    if(move < 0 or move > 6) return false;
    if(board[0][move] != 0) return false;

    return true;
}
int Connect4::makemove(int board[6][7], int move, int stone)
{
    for (int i=1; i<6; i++)
    {
        if (board[i][move] != 0)
        {
            board[i-1][move] = stone;
            return (i-1);
        }
    }
    board[5][move] = stone;
    return 5;

}
void Connect4::undomove(int board[6][7], int move, int stone)
{
    for (int i=0; i<6; i++)
    {
        if (board[i][move] != 0)
        {
            board[i][move] = 0;
            return;
        }
    }
}
bool Connect4::ismoveleft(int board[6][7])
{
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 7; ++j)
            if(board[i][j] == 0)
                return true;
    return false;
}
int Connect4::GetBoard(int board[6][7], int row, int col)
{
    if(col < 0 or col > 6 or row < 0 or row > 5)
        return -2;
    return board[row][col];
}
int Connect4::checkforwin(int board[6][7], int movecol)
{
    int moverow;
    int length;
    int color;
    int delta;

    for (moverow=0; moverow <6 && GetBoard(board,moverow,movecol) == 0; moverow++);
    if (GetBoard(board,moverow,movecol) == 0) return 0;

    color = board[moverow][movecol];
    length = 0;
    delta = 0;

    while (GetBoard(board,moverow+delta,movecol) == color)
    {
    length++;
    delta++;
    }
    if (length >= 4)
    {
        if(color == 1)
            return -1;
        return 1;
    }
    length = 0;
    delta = 0;
    while (GetBoard(board,moverow,movecol+delta) == color)
    {
    length++;
    delta++;
    }
    delta = 1;
    while (GetBoard(board,moverow,movecol-delta) == color)
    {
    length++;
    delta++;
    }
    if (length >= 4)
    {
        if(color == 1)
            return -1;
        return 1;
    }
    delta = 0;
    length = 0;

    while (GetBoard(board,moverow+delta,movecol+delta) == color)
    {
    length++;
    delta++;
    }
    delta = 1;
    while (GetBoard(board,moverow-delta,movecol-delta) == color)
    {
    length++;
    delta++;
    }

    if (length >= 4)
    {
        if(color == 1)
            return -1;
        return 1;
    }

    delta = 0;
    length = 0;

    while (GetBoard(board,moverow+delta,movecol-delta) == color)
    {
    length++;
    delta++;
    }
    delta = 1;
    while (GetBoard(board,moverow-delta,movecol+delta) == color)
    {
    length++;
    delta++;
    }
    if (length >= 4)
    {
        if(color == 1)
            return -1;
        return 1;
    }

    return 0;
}
int Connect4::swap(int color)
{
    if(color == 1)
        return 2;
    else return 1;
}
int Connect4::piece1(int board[6][7], int x, int y, int color)
{
    int total = 0;
    if (board[x][y] == 0)
    return 0;
    if ((GetBoard(board,x,y)==color) &&
    (GetBoard(board,x-1,y) == 0) && (GetBoard(board,x+1,y) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x,y-1) == 0) && (GetBoard(board,x,y+1) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y-1) == 0) && (GetBoard(board,x+1,y+1) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y+1) == 0) && (GetBoard(board,x+1,y-1) == 0))
    total++;
    return total;
}
int Connect4::half_piece2(int board[6][7], int x, int y, int color)
{
    int total = 0;
    if (board[x][y] == 0)
    return 0;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x-1,y) == swap(color) ||
     (GetBoard(board,x-1,y) == -2)) &&
    (GetBoard(board,x+1,y) == color) &&
     (GetBoard(board,x+2,y) == 0)))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x,y-1) == swap(color)) ||
     (GetBoard(board,x,y-1) == -2)) &&
    (GetBoard(board,x,y+1) == color) &&
    (GetBoard(board,x,y+2) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x-1,y-1) == swap(color)) ||
     (GetBoard(board,x-1,y-1) == -2)) &&
    (GetBoard(board,x+1,y+1) == color) &&
    (GetBoard(board,x+2,y+2) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x-1,y+1) == swap(color)) ||
     (GetBoard(board,x-1,y+1) == -2)) &&
    (GetBoard(board,x+1,y-1) == color) &&
    (GetBoard(board,x+2,y-2) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y) == 0) &&
    (GetBoard(board,x+1,y) == color) &&
    ((GetBoard(board,x+2,y) == swap(color)) ||
     (GetBoard(board,x+2,y) == -2)))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x,y-1) == 0) &&
    (GetBoard(board,x,y+1) == color) &&
    ((GetBoard(board,x,y+2) == swap(color)) ||
     (GetBoard(board,x,y+2) == -2)))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y-1) == 0) &&
    (GetBoard(board,x+1,y+1) == color) &&
    ((GetBoard(board,x+2,y+2) == swap(color)) ||
     (GetBoard(board,x+2,y+2) == -2)))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y+1) == 0) &&
    (GetBoard(board,x+1,y-1) == color) &&
    ((GetBoard(board,x+2,y-2) == swap(color)) ||
     (GetBoard(board,x+2,y-2) == -2)))
    total++;
    return total;
}
int Connect4::piece2(int board[6][7], int x, int y, int color)
{
    int total = 0;
    if (board[x][y] == 0)
    return 0;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y) == 0) &&
    (GetBoard(board,x+1,y) == color) &&
     (GetBoard(board,x+2,y) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x,y-1) == 0) &&
    (GetBoard(board,x,y+1) == color) &&
    (GetBoard(board,x,y+2) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y-1) == 0) &&
    (GetBoard(board,x+1,y+1) == color) &&
    (GetBoard(board,x+2,y+2) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y+1) == 0) &&
    (GetBoard(board,x+1,y-1) == color) &&
    (GetBoard(board,x+2,y-2) == 0))
    total++;
    return total;
}
int Connect4::half_piece3(int board[6][7], int x, int y, int color)
{
    int total = 0;
    if (board[x][y] == 0)
    return 0;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x-1,y) == swap(color)) ||
     (GetBoard(board,x-1,y) == -2)) &&
    (GetBoard(board,x+1,y) == color) &&
    (GetBoard(board,x+2,y) == color) &&
    (GetBoard(board,x+3,y) ==0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x,y-1) == swap(color)) ||
     (GetBoard(board,x,y-1) == -2)) &&
    (GetBoard(board,x,y+1) == color) &&
    (GetBoard(board,x,y+2) == color) &&
    (GetBoard(board,x,y+3) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x-1,y-1) == swap(color)) ||
     (GetBoard(board,x-1,y-1) == -2)) &&
    (GetBoard(board,x+1,y+1) == color) &&
    (GetBoard(board,x+2,y+2) == color) &&
    (GetBoard(board,x+3,y+3) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    ((GetBoard(board,x-1,y+1) == swap(color)) ||
     (GetBoard(board,x-1,y+1) == -2)) &&
    (GetBoard(board,x+1,y-1) == color) &&
    (GetBoard(board,x+2,y-2) == color) &&
    (GetBoard(board,x+3,y-3) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y) == 0) &&
    (GetBoard(board,x+1,y) == color) &&
    (GetBoard(board,x+2,y) == color) &&
    ((GetBoard(board,x+3,y) == swap(color)) ||
     (GetBoard(board,x+3,y) == -2)))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x,y-1) == 0) &&
    (GetBoard(board,x,y+1) == color) &&
    (GetBoard(board,x,y+2) == color) &&
    ((GetBoard(board,x,y+3) == swap(color)) ||
     (GetBoard(board,x,y+3) == -2)))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y-1) == 0) &&
    (GetBoard(board,x+1,y+1) == color) &&
    (GetBoard(board,x+2,y+2) == color) &&
    ((GetBoard(board,x+3,y+3) == swap(color)) ||
     (GetBoard(board,x+3,y+3) == -2)))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y+1) == 0) &&
    (GetBoard(board,x+1,y-1) == color) &&
    (GetBoard(board,x+2,y-2) == color) &&
    ((GetBoard(board,x+3,y-3) == swap(color)) ||
     ((GetBoard(board,x+3,y-3) == -2))))
    total++;
    return total;
}
int Connect4::piece3(int board[6][7], int x, int y, int color)
{
    int total = 0;
    if (board[x][y] == 0)
    return 0;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y) == 0) &&
    (GetBoard(board,x+1,y) == color) &&
    (GetBoard(board,x+2,y) == color) &&
    (GetBoard(board,x+3,y) ==0) )
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x,y-1) == 0) &&
    (GetBoard(board,x,y+1) == color) &&
    (GetBoard(board,x,y+2) == color) &&
    (GetBoard(board,x,y+3) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y-1) == 0) &&
    (GetBoard(board,x+1,y+1) == color) &&
    (GetBoard(board,x+2,y+2) == color) &&
    (GetBoard(board,x+3,y+3) == 0))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x-1,y+1) == 0) &&
    (GetBoard(board,x+1,y-1) == color) &&
    (GetBoard(board,x+2,y-2) == color) &&
    (GetBoard(board,x+3,y-3) == 0))
    total++;
    return total;
}
int Connect4::piece4(int board[6][7], int x, int y, int color)
{
     int total = 0;
    if (board[x][y] == 0)
    return 0;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x+1,y) == color) &&
    (GetBoard(board,x+2,y) == color) &&
    (GetBoard(board,x+3,y) == color))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x,y+1) == color) &&
    (GetBoard(board,x,y+2) == color) &&
    (GetBoard(board,x,y+3) == color))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x+1,y+1) == color) &&
    (GetBoard(board,x+2,y+2) == color) &&
    (GetBoard(board,x+3,y+3) == color))
    total++;
    if ((GetBoard(board,x,y) == color) &&
    (GetBoard(board,x+2,y-2) == color) &&
    (GetBoard(board,x+3,y-3) == color) &&
    (GetBoard(board,x+4,y-4) == color))
    total++;
    return total;
}
int Connect4::evaluate(int board[6][7])
{
    int i;
    int j;

    int piece1_1 = 0;
    int piece1_2 = 0;
    int half_piece2_1 = 0;
    int half_piece2_2 = 0;
    int piece2_1 = 0;
    int piece2_2 = 0;
    int half_piece3_1 = 0;
    int half_piece3_2 = 0;
    int piece3_1 = 0;
    int piece3_2 = 0;
    int piece4_1 = 0;
    int piece4_2 = 0;

    for (i=0;i<6;i++)
    for (j=0;j<7;j++)
    {
        piece1_1 = piece1_1 + piece1(board,i,j,1);
        piece1_2 = piece1_2 + piece1(board,i,j,2);
        half_piece2_1 = half_piece2_1 + half_piece2(board,i,j,1);
        half_piece2_2 = half_piece2_2 + half_piece2(board,i,j,2);
        piece2_1 = piece2_1 + piece2(board,i,j,1);
        piece2_2 = piece2_2 + piece2(board,i,j,2);

        half_piece3_1 = half_piece3_1 + half_piece3(board,i,j,1);
        half_piece3_2 = half_piece3_2 + half_piece3(board,i,j,2);
        piece3_1 = piece3_1 + piece3(board,i,j,1);
        piece3_2 = piece3_2 + piece3(board,i,j,2);
        piece4_1 = piece4_1 + piece4(board,i,j,1);
        piece4_2 = piece4_2 + piece4(board,i,j,2);
    }

    return ((piece1_2 + half_piece2_2*3 + piece2_2*9+half_piece3_2*20 +
            piece3_2*100+piece4_2*1000) - (piece1_1 + half_piece2_1*3 +
            piece2_1*9+half_piece3_1*20+piece3_1*100+piece4_1*1000));
}
int Connect4::minimax(int board[6][7], int move, int depth, bool isMax, int alpha, int beta)
{
    if(ismoveleft(board) == false)
    {
        return 0;
    }
    if(depth == 6)
    {
        return evaluate(board);
    }

    if(isMax)
    {
        int best = INT_MIN;
        for(int i = 0; i < 7; ++i)
        {
            if(legal_move(board, i))
            {
               int row =  makemove(board, i, 2);

                best = max(best, minimax(board, i, depth+1, false, alpha, beta));
                alpha = max(alpha, best);

                undomove(board, i, 2);

                if(beta <= alpha)
                    break;

            }
        }
        return best;
    }
    else
    {
        int best = INT_MAX;
        for(int i = 0; i < 7; ++i)
        {
            if(legal_move(board, i))
            {
                int row = makemove(board, i, 1);

                best = min(best, minimax(board, i,depth+1, true, alpha, beta));
                beta = min(beta, best);
                undomove(board, i, 1);

                if(beta <= alpha)
                    break;
            }
        }
        return best;
    }

}
int Connect4::bestmove(int board[6][7])
{
    int val = INT_MIN;
    int res;
    int depth = 0;

    for(int i = 0; i <7; ++i)
    {
        if(legal_move(board, i))
        {
            int row = makemove(board, i, 2);

            int temp_val = minimax(board, i, depth, false, INT_MIN, INT_MAX);

            undomove(board, i, 2);

            if(val < temp_val)
            {
                res = i;
                val = temp_val;
            }
        }
    }
    return res;
}
void Connect4::show_stone(int row, int move, int player)
{
    if(player == 1)
    {
        QPixmap pix(":/Files/Pics/yellow.png");
        if(row == 0)
        {
            if(move == 0)
                ui->labelr_11->setPixmap(pix);
            else if(move == 1)
                ui->labelr_12->setPixmap(pix);
            else if(move == 2)
                ui->labelr_13->setPixmap(pix);
            else if(move == 3)
                ui->labelr_14->setPixmap(pix);
            else if(move == 4)
                ui->labelr_15->setPixmap(pix);
            else if(move == 5)
                ui->labelr_16->setPixmap(pix);
            else if(move == 6)
                ui->labelr_17->setPixmap(pix);

        }
        if(row == 1)
        {
            if(move == 0)
                ui->labelr_21->setPixmap(pix);
            else if(move == 1)
                ui->labelr_22->setPixmap(pix);
            else if(move == 2)
                ui->labelr_23->setPixmap(pix);
            else if(move == 3)
                ui->labelr_24->setPixmap(pix);
            else if(move == 4)
                ui->labelr_25->setPixmap(pix);
            else if(move == 5)
                ui->labelr_26->setPixmap(pix);
            else if(move == 6)
                ui->labelr_27->setPixmap(pix);

        }
        if(row == 2)
        {
            if(move == 0)
                ui->labelr_31->setPixmap(pix);
            else if(move == 1)
                ui->labelr_32->setPixmap(pix);
            else if(move == 2)
                ui->labelr_33->setPixmap(pix);
            else if(move == 3)
                ui->labelr_34->setPixmap(pix);
            else if(move == 4)
                ui->labelr_35->setPixmap(pix);
            else if(move == 5)
                ui->labelr_36->setPixmap(pix);
            else if(move == 6)
                ui->labelr_37->setPixmap(pix);

        }
        if(row == 3)
        {
            if(move == 0)
                ui->labelr_41->setPixmap(pix);
            else if(move == 1)
                ui->labelr_42->setPixmap(pix);
            else if(move == 2)
                ui->labelr_43->setPixmap(pix);
            else if(move == 3)
                ui->labelr_44->setPixmap(pix);
            else if(move == 4)
                ui->labelr_45->setPixmap(pix);
            else if(move == 5)
                ui->labelr_46->setPixmap(pix);
            else if(move == 6)
                ui->labelr_47->setPixmap(pix);

        }
        if(row == 4)
        {
            if(move == 0)
                ui->labelr_51->setPixmap(pix);
            else if(move == 1)
                ui->labelr_52->setPixmap(pix);
            else if(move == 2)
                ui->labelr_53->setPixmap(pix);
            else if(move == 3)
                ui->labelr_54->setPixmap(pix);
            else if(move == 4)
                ui->labelr_55->setPixmap(pix);
            else if(move == 5)
                ui->labelr_56->setPixmap(pix);
            else if(move == 6)
                ui->labelr_57->setPixmap(pix);

        }
        if(row == 5)
        {
            if(move == 0)
                ui->labelr_61->setPixmap(pix);
            else if(move == 1)
                ui->labelr_62->setPixmap(pix);
            else if(move == 2)
                ui->labelr_63->setPixmap(pix);
            else if(move == 3)
                ui->labelr_64->setPixmap(pix);
            else if(move == 4)
                ui->labelr_65->setPixmap(pix);
            else if(move == 5)
                ui->labelr_66->setPixmap(pix);
            else if(move == 6)
                ui->labelr_67->setPixmap(pix);

        }
    }

    else if(player == 2)
    {
        QPixmap pix(":/Files/Pics/red.png");
        if(row == 0)
        {
            if(move == 0)
                ui->labelr_11->setPixmap(pix);
            else if(move == 1)
                ui->labelr_12->setPixmap(pix);
            else if(move == 2)
                ui->labelr_13->setPixmap(pix);
            else if(move == 3)
                ui->labelr_14->setPixmap(pix);
            else if(move == 4)
                ui->labelr_15->setPixmap(pix);
            else if(move == 5)
                ui->labelr_16->setPixmap(pix);
            else if(move == 6)
                ui->labelr_17->setPixmap(pix);

        }
        if(row == 1)
        {
            if(move == 0)
                ui->labelr_21->setPixmap(pix);
            else if(move == 1)
                ui->labelr_22->setPixmap(pix);
            else if(move == 2)
                ui->labelr_23->setPixmap(pix);
            else if(move == 3)
                ui->labelr_24->setPixmap(pix);
            else if(move == 4)
                ui->labelr_25->setPixmap(pix);
            else if(move == 5)
                ui->labelr_26->setPixmap(pix);
            else if(move == 6)
                ui->labelr_27->setPixmap(pix);

        }
        if(row == 2)
        {
            if(move == 0)
                ui->labelr_31->setPixmap(pix);
            else if(move == 1)
                ui->labelr_32->setPixmap(pix);
            else if(move == 2)
                ui->labelr_33->setPixmap(pix);
            else if(move == 3)
                ui->labelr_34->setPixmap(pix);
            else if(move == 4)
                ui->labelr_35->setPixmap(pix);
            else if(move == 5)
                ui->labelr_36->setPixmap(pix);
            else if(move == 6)
                ui->labelr_37->setPixmap(pix);

        }
        if(row == 3)
        {
            if(move == 0)
                ui->labelr_41->setPixmap(pix);
            else if(move == 1)
                ui->labelr_42->setPixmap(pix);
            else if(move == 2)
                ui->labelr_43->setPixmap(pix);
            else if(move == 3)
                ui->labelr_44->setPixmap(pix);
            else if(move == 4)
                ui->labelr_45->setPixmap(pix);
            else if(move == 5)
                ui->labelr_46->setPixmap(pix);
            else if(move == 6)
                ui->labelr_47->setPixmap(pix);

        }
        if(row == 4)
        {
            if(move == 0)
                ui->labelr_51->setPixmap(pix);
            else if(move == 1)
                ui->labelr_52->setPixmap(pix);
            else if(move == 2)
                ui->labelr_53->setPixmap(pix);
            else if(move == 3)
                ui->labelr_54->setPixmap(pix);
            else if(move == 4)
                ui->labelr_55->setPixmap(pix);
            else if(move == 5)
                ui->labelr_56->setPixmap(pix);
            else if(move == 6)
                ui->labelr_57->setPixmap(pix);

        }
        if(row == 5)
        {
            if(move == 0)
                ui->labelr_61->setPixmap(pix);
            else if(move == 1)
                ui->labelr_62->setPixmap(pix);
            else if(move == 2)
                ui->labelr_63->setPixmap(pix);
            else if(move == 3)
                ui->labelr_64->setPixmap(pix);
            else if(move == 4)
                ui->labelr_65->setPixmap(pix);
            else if(move == 5)
                ui->labelr_66->setPixmap(pix);
            else if(move == 6)
                ui->labelr_67->setPixmap(pix);

        }
    }


}

void Connect4::show_message(int player)
{
    if(player == 0)
        QMessageBox::information(0, QObject::tr("Notification"), QObject::tr("Match draw!!"));
    else if(player == 1)
        QMessageBox::information(0, QObject::tr("Notification"), QObject::tr("Bot Win!!"));
    else
        QMessageBox::information(0, QObject::tr("Notification"), QObject::tr("You Win!!"));

    QApplication::quit();
}

void Connect4::on_pushButton_1_clicked()
{

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    int move = 0;
    int row = makemove(board, move, 1);
    show_stone(row, move, 1);
    int res = checkforwin(board, move);
    if(res != 0)
        show_message(res);

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    move = bestmove(board);
    row = makemove(board, move, 2);
    show_stone(row, move, 2);
    res = checkforwin(board, move);
    if(res != 0)
        show_message(res);
}

void Connect4::on_pushButton_2_clicked()
{
    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    int move = 1;
    int row = makemove(board, move, 1);
    show_stone(row, move, 1);
    int res = checkforwin(board, move);
    if(res != 0)
        show_message(res);

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    move = bestmove(board);
    row = makemove(board, move, 2);
    show_stone(row, move, 2);
    res = checkforwin(board, move);
    if(res != 0)
        show_message(res);
}

void Connect4::on_pushButton_3_clicked()
{
    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    int move = 2;
    int row = makemove(board, move, 1);
    show_stone(row, move, 1);
    int res = checkforwin(board, move);
    if(res != 0)
        show_message(res);

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    move = bestmove(board);
    row = makemove(board, move, 2);
    show_stone(row, move, 2);
    res = checkforwin(board, move);
    if(res != 0)
        show_message(res);
}

void Connect4::on_pushButton_4_clicked()
{
    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    int move = 3;
    int row = makemove(board, move, 1);
    show_stone(row, move, 1);
    int res = checkforwin(board, move);
    if(res != 0)
        show_message(res);

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    move = bestmove(board);
    row = makemove(board, move, 2);
    show_stone(row, move, 2);
    res = checkforwin(board, move);
    if(res != 0)
        show_message(res);
}

void Connect4::on_pushButton_5_clicked()
{
    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    int move = 4;
    int row = makemove(board, move, 1);
    show_stone(row, move, 1);
    int res = checkforwin(board, move);
    if(res != 0)
        show_message(res);

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    move = bestmove(board);
    row = makemove(board, move, 2);
    show_stone(row, move, 2);
    res = checkforwin(board, move);
    if(res != 0)
        show_message(res);
}

void Connect4::on_pushButton_6_clicked()
{
    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    int move = 5;
    int row = makemove(board, move, 1);
    show_stone(row, move, 1);
    int res = checkforwin(board, move);
    if(res != 0)
        show_message(res);

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    move = bestmove(board);
    row = makemove(board, move, 2);
    show_stone(row, move, 2);
    res = checkforwin(board, move);
    if(res != 0)
        show_message(res);
}

void Connect4::on_pushButton_7_clicked()
{
    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    int move = 6;
    int row = makemove(board, move, 1);
    show_stone(row, move, 1);
    int res = checkforwin(board, move);
    if(res != 0)
        show_message(res);

    if(ismoveleft(board) == false)
    {
        show_message(0);
    }
    move = bestmove(board);
    row = makemove(board, move, 2);
    show_stone(row, move, 2);
    res = checkforwin(board, move);
    if(res != 0)
        show_message(res);
}
