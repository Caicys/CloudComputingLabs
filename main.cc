#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include<pthread.h>
#include<unistd.h>
#include<map>

#include "sudoku.h"
char puzzle[128];
int NUM_solved = 0;
int MAX_NUM = 0;
bool (*solve)(int) = solve_sudoku_basic;

std::map<int,char*>map_client;
pthread_mutex_t mutex;
int64_t now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

void* shudu1(void*args)
{
    pthread_mutex_lock(&mutex);
    for(int i=0;i<5;i++){
        input(map_client[i]);
        if (solve(0)) {
            ++NUM_solved;
            if (!solved())  assert(0);
            for(int i=0;i<N-1;i++)
                printf("%d",board[i]);
            printf("%d\n\n",board[N-1]);
        }
        else {
            printf("No: %s", puzzle);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* shudu2(void*args){
    pthread_mutex_lock(&mutex);
    for(int i=5;i<MAX_NUM;i++){
        input(map_client[i]);
        if (solve(0)) {
            ++NUM_solved;
            if (!solved()) assert(0);
            for(int i=0;i<N-1;i++)
                printf("%d",board[i]);
            printf("%d\n\n",board[N-1]);
        }
        else {
            printf("No: %s", puzzle);
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
    init_neighbors();
    FILE* fp = fopen(argv[1], "r");

    int64_t start = now();
    while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
        if (strlen(puzzle) >= N) {
            map_client[MAX_NUM]=puzzle;
            ++MAX_NUM;
        }
    }
    pthread_mutex_init(&mutex, NULL);

    pthread_t th1;
    if(pthread_create(&th1,NULL,shudu1,NULL)!=0){
        perror("pthread_create failed");
        exit(0);
    }

    pthread_t th2;
    if(pthread_create(&th2,NULL,shudu2,NULL)!=0){
        perror("pthread_create failed");
        exit(0);
    }

    pthread_join(th1,NULL); 	
    pthread_join(th2,NULL);
  
    pthread_mutex_destroy(&mutex);

    int64_t end = now();
    double sec = (end-start)/1000000.0;
    printf("%f sec %f ms each %d\n", sec, 1000*sec/MAX_NUM, NUM_solved);

    return 0;
}



