#include <bits/stdc++.h>
using namespace std;

int board[4][4];
int dirCol[] = {1, 0, -1, 0};
int dirRow[] = {0, 1, 0, -1};
bool lose = false;
bool won = false;

void newGame();
void printGame();
pair<int, int> generateRandom();
void applymove();
void addpiece();

void newGame()
{
    won = false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = 0;

    addpiece();
}

void printGame()
{
    system("cls");

    for (int i = 0; i < 4; i++)
    {
        cout << "------------------------\n";
        cout << "|";

        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] != 0)
                cout << setw(4) << board[i][j] << "|";
            else
                cout << setw(4) << " "
                     << "|";
            cout << " ";

            if (board[i][j] == 2048)
                won = 1;
        }
        cout << endl;
    }
    cout << "------------------------\n";
}

pair<int, int> generateRandom()
{
    int occupied = 1;
    int row, col;
    while (occupied)
    {
        row = rand() % 4;
        col = rand() % 4;
        if (board[row][col] == 0)
            occupied = 0;
    }
    return {row, col};
}

void applyMove(int direction)
{
    /*
    Up: rowStart = 0, rowMove = 1;
    Down: rowStart = 3, rowMove = -1;
    Left: colStart = 0, colMove = 1;
    Right: colStart = 3, colMove = -1;
    */
    bool possible = false;
    lose = true;
    int rowStart = 0, colStart = 0, rowMove = 1, colMove = 1;
    if (direction == 1)
    {
        colStart = 3, colMove = -1;
    }

    if (direction == 2)
    {
        rowStart = 3, rowMove = -1;
    }

    if (direction == 1 || direction == 3)
    {
        for (int i = rowStart; i < 4 && i >= 0; i += rowMove)
        {
            int prev = colStart;
            for (int j = colStart; j < 4 && j >= 0; j += colMove)
            {
                if (board[i][j] != 0)
                {
                    if (j != prev)
                    {
                        if (board[i][j] == board[i][prev])
                        {
                            board[i][prev] *= 2;
                            board[i][j] = 0;
                            prev += colMove;
                            possible = true;
                            lose = false;
                        }
                        else if (board[i][prev] == 0)
                        {
                            board[i][prev] = board[i][j];
                            board[i][j] = 0;
                            possible = true;
                            lose = false;
                        }
                        else
                        {
                            prev += colMove;
                            j -= colMove;
                        }
                    }
                }
                else
                    lose = false;
            }
        }
    }

    else
    {
        for (int j = colStart; j < 4 && j >= 0; j += colMove)
        {
            int prev = rowStart;
            for (int i = rowStart; i < 4 && i >= 0; i += rowMove)
            {
                if (board[i][j] != 0)
                {
                    if (i != prev)
                    {
                        if (board[i][j] == board[prev][j])
                        {
                            board[prev][j] *= 2;
                            board[i][j] = 0;
                            prev += rowMove;
                            possible = true;
                            lose = false;
                        }
                        else if (board[prev][j] == 0)
                        {
                            board[prev][j] = board[i][j];
                            board[i][j] = 0;
                            possible = true;
                            lose = false;
                        }
                        else
                        {
                            prev += rowMove;
                            i -= rowMove;
                        }
                    }
                }
                else
                    lose = false;
            }
        }
    }

    if (lose)
    {
    }
    if (possible)
        addpiece();
}

void addpiece()
{
    auto pos = generateRandom();
    int piece = rand() % 2;
    board[pos.first][pos.second] = 2 * (piece + 1);
}

int main()
{
    srand(time(0));
    newGame();
    while (true)
    {
        printGame();
        if (won)
            cout << "YOU WON\n\n\n";
        if (lose)
        {
            int i = 0;
            while (i < 4 && lose)
            {
                applyMove(i);
                i++;
            }
            if (lose)
                cout << "YOU LOSE\n\n\n";
        }

        cout << "n: New Game \t w: up, d: right, s: down, a: left \t q: quit" << endl;
        char command;
        int currentDirection;
        cin >> command;
        if (command == 'n')
            newGame();
        else if (command == 'q')
            break;
        else
        {
            if (command == 'w')
                currentDirection = 0;
            else if (command == 'd')
                currentDirection = 1;
            else if (command == 's')
                currentDirection = 2;
            else if (command == 'a')
                currentDirection = 3;
            else
                continue;
            applyMove(currentDirection);
        }
    }
}