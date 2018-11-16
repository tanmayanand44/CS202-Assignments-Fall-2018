#include "sat.h"

// Takes a matrix A and fills it with a randomly generated partially filled minimal sudoku.
void generator(int A[9][9])
{
    srand(time(0));
    int visited[9][9];
    memset(visited, 0, sizeof(visited));
    int count = 0, filled=81;
    generateSatInput(A);
    solveSat();
    outputSudoku(A);
    while (count<81 && filled>17) //a minimal sudoku has atleast 17 filled boxed (src: https://www.technologyreview.com/s/426554/mathematicians-solve-minimum-sudoku-problem/)
    {
        int ran = rand() % 81;
        int row = (ran) / 9;
        int col = (ran) % 9;
        if (visited[row][col])
            continue;
        visited[row][col] = 1;
        count++;
        filled--;
        int A_a = A[row][col];
        A[row][col] = -1;
        if (!hasUnique(A)){
            A[row][col] = A_a;
            filled++;
        }
    }
}
int main()
{
    int A[9][9];
    memset(A, -1, sizeof(A));
    generator(A);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(A[i][j]<=0)cout<<".";
            else cout<<A[i][j];
        }
        cout<<endl;
    }
    return 0;
}
