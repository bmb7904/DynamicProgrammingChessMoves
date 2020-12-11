/**
 * On an M x N chessboard, a king beings its path in the first column, and ends in the
 * last column. If king is allowed only N - 1 moves, how many possible paths can the
 * king take?
 *
 * On an M x N chessboard, represented by a 2D array: board[][], assuming zero-based
 * indexing, a particular cell on the board can be represented by grid[i][j], where i
 * is the index of the row and j the index of the column.
 *
 * For all i !=0, i != m-1, and j != 0, the following recursive relationship is valid:
 * numPaths(board[i][j]) = numPaths(board[i][j-1]) + numPaths(board[i+1][j-1]) + numPaths(board[i-1][j-1])
 *
 * I.E., the number of possible ways to travel to a particular cell can be defined in
 * terms of its neighboring cells. By summing the number of possible ways to travel to
 * all cells in the final column, we can obtain the number of possible paths a king
 * can take from the first file to the final file.
 *
 * Cells in the top row or the bottom row are special cases and they are explicitly
 *  shown below.
 *
 * This calculation can be done much, much faster by using dynamic programming.
 *
 * @Author Brett Bernardi
 * @date September 25, 2020
 */

#include <iostream>

using namespace std;

unsigned long long dynamic_path_counter(int m, int n);

int main()
{
    int rows, cols;
    cout << "Enter chessboard dimensions: ";
    cin >> rows >> cols;

    cout << "Paths from first to last file: " << dynamic_path_counter(rows,cols) << endl;

    return 0;
}

/*
 * Returns the number of possible paths for a King starting in the first column(file)
 * and ending in the final column
 * on a chessboard with dimensions m x n.
 *
 * m - the number of rows in a chessboard
 * n - the number of columns in a chess board
 * return unsigned long long - the number of possible paths from the first column to
 * the last column
 */
unsigned long long dynamic_path_counter(int m, int n)
{
    // board[i][j] stores the number of ways the King can reach cell(i,j)
    unsigned long long board[m][n];

    // the number of total possible paths for the king on this board.
    static unsigned long long numPaths = 0;

    // first fill array with base cases, which is any cell in the first column, with a
    // value of 1.
    // The king begins its path in any one of these cells
    for(int i = 0; i < m; i++)
    {
        board[i][0] = 1;
    }

    // fill up array from the bottom-up
    // this array must be filled up in a column by column fashion. Doing it row by row
    // would lead to problems.
    for(int j = 1; j < n; j++)
    {
        for(int i = 0; i < m; i++)
        {
            // for the first row (special case)
            if(i==0)
            {
                board[i][j] = board[i][j-1] + board[i+1][j-1];
            }

                // for the last row (special case)
            else if(i == (m-1))
            {
                board[i][j] = board[i][j-1] + board[i-1][j-1];
            }
                // finally, for all other cells not on the edges
            else
            {
                board[i][j] = board[i-1][j-1] + board[i][j-1] + board[i+1][j-1];

            }
        }
    }

    // now, we sum up all cells in the final column (where the King finishes). This
    // will be total number of paths.
    // The final file or column has the index (n-1)
    for(int i = 0; i < m; i++)
    {
        numPaths += board[i][n-1];
    }

    return numPaths;
}
