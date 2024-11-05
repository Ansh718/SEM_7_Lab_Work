#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<vector<int>> &board, int row, int col, int N)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
        {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    return true;
}

bool solver(vector<vector<int>> &board, int row, int N)
{
    if (row >= N)
    {
        return true;
    }
    for (int col = 0; col < N; col++)
    {
        if (isSafe(board, row, col, N))
        {
            board[row][col] = 1;
            if (solver(board, row + 1, N))
            {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}

void printBoard(const vector<vector<int>> &board, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
}

int main()
{
    int N = 0;
    cout << "Enter the number of queens (N): ";
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N, 0));
    bool found = false;
    for (int col = 0; col < N; col++)
    {
        board[0][col] = 1;
        if (solver(board, 1, N))
        {
            found = true;
            break;
        }
        board[0][col] = 0;
    }
    if (found)
    {
        cout << "Solution:\n";
        printBoard(board, N);
    }
    else
    {
        cout << "No solution exists.\n";
    }
    return 0;
}