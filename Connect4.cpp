#include <bits/stdc++.h>
using namespace std;

void initialise(int board[6][7])
{
	for(int i = 0; i < 6; ++i)
		for(int j = 0; j < 7; ++j)
			board[i][j] = 0;
}
void show(int board[6][7])
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
}
bool legal_move(int board[6][7], int move)
{
	if(move < 0 or move > 6) return false;
	if(board[0][move] != 0) return false;

	return true;
}
void makemove(int board[6][7], int move, int stone)
{
	for (int i=1; i<6; i++)
	{
	    if (board[i][move] != 0)
	    {
	        board[i-1][move] = stone;
	        return;
	    }
    }
    board[5][move] = stone;
}
void undomove(int board[6][7], int move, int stone)
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
bool ismoveleft(int board[6][7])
{
	for(int i = 0; i < 6; ++i)
		for(int j = 0; j < 7; ++j)
			if(board[i][j] == 0)
				return true;
	return false;
}
int GetBoard(int board[6][7], int row, int col)
{
	if(col < 0 or col > 6 or row < 0 or row > 5)
		return -2;
	return board[row][col];
}
int checkforwin(int board[6][7], int movecol)
{
   	int moverow;
    int length;
    int color;
    int delta;
    
    for (moverow=0; moverow <10 && GetBoard(board,moverow,movecol) == 0; moverow++);
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
int swap(int color)
{
	if(color == 1)
		return 2;
	else return 1;
}
int piece1(int board[6][7], int x, int y, int color)
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
int half_piece2(int board[6][7], int x, int y, int color)
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
int piece2(int board[6][7], int x, int y, int color)
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
int half_piece3(int board[6][7], int x, int y, int color)
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
int piece3(int board[6][7], int x, int y, int color)
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
int piece4(int board[6][7], int x, int y, int color)
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
int evaluate(int board[6][7])
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
         
    return ((piece1_2 + half_piece2_2*3 + piece2_2*9+half_piece3_2*20+
     piece3_2*100+piece4_2*1000) - (piece1_1 + half_piece2_1*3 + piece2_1*9+half_piece3_1*20+
        piece3_1*100+piece4_1*1000));
}
int minimax(int board[6][7], int move, int depth, bool isMax, int alpha, int beta)
{
	if(ismoveleft(board) == false)
	{
		return 0;
	}
	if(depth == 4)
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
				makemove(board, i, 2);

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
				makemove(board, i, 1);

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
int bestmove(int board[6][7])
{
	int val = INT_MIN;
	int res;
	int depth = 0;

	for(int i = 0; i <7; ++i)
	{
		if(legal_move(board, i))
		{
			makemove(board, i, 2);

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
int main_util(int board[6][7])
{
	int player = 0;
	int move;
	int total_move = 0;
	int res;

	show(board);

	while(1)
	{
		if(player == 0)
		{
			do
			  {
				cout << "Make your move: ";
				cin >> move;
			  }while(legal_move(board, move) == false);
		}
		else
		{
			move = bestmove(board);
		}
		makemove(board, move, player + 1);
		show(board);

		if(ismoveleft(board) == false)
		{
			return 0;
		}
		int res = checkforwin(board, move);
		if(res != 0)
		{
			return res;
		}
		
		player = (player + 1)%2;
	}
}
int main()
{
	int board[6][7];
	initialise(board);

	int res = main_util(board);

	if(res == 0)
		cout << "DRAW\n";
	else if(res == 1)
		cout << "BOT wins\n";
	else 
		cout << "YOU win\n";

	return 0;
}