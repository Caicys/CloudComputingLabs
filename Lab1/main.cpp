#include <cstdio>
#include <cassert>
#include <sys/time.h>
using namespace std;

#include "sudoku.h"

int main()
{
    freopen("test.txt","r",stdin);  
    freopen("out.txt","w",stdout);
    char puzzle[128];
    int board[N];
    while (scanf("%s", puzzle) != EOF)
    {
        // 输入
        for (int cell = 0; cell < N; ++cell)
        {
            board[cell] = puzzle[cell] - '0';
            assert(0 <= board[cell] && board[cell] <= NUM);
        }
        
        if (solve_sudoku_dancing_links(board))
        {
            // 输出解
            for (int i = 0; i < N; ++i)
            {
                printf("%d", board[i]);
            }
        }
        else  // 无解
        {
            printf("No solution: %s", puzzle);
        }
        printf("\n");
	//gettimeofday(&end,NULL);
	//printf("The run time is:%lf ms\n",(double)(end.tv_sec-start.tv_sec));
    }
    return 0;
}
