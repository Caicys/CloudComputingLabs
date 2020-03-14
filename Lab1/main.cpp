#include <cstdio>
#include <cassert>
using namespace std;

#include "sudoku.h"

int main()
{
    char puzzle[128];
    int board[N];
    while (scanf("%s", puzzle) != EOF)
    {
        for (int cell = 0; cell < N; ++cell)
        {
            board[cell] = puzzle[cell] - '0';
            assert(0 <= board[cell] && board[cell] <= NUM);
        }
        assert(solve_sudoku_dancing_links(board));
        for (int i = 0; i < N; ++i)
        {
            printf("%d", board[i]);
        }
        printf("\n");
    }
    return 0;
}
