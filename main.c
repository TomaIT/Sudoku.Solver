#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sudoku.h"

#define WINDOWS



int main(){
    FILE *f=fopen("Sudoku_9x9_Complete.txt","r");
    clock_t start;
    Sudoku a;
    int i,time=0,t,imax=0,tmax=-1,x=0;
    for(i=0;i<1000000;i++){
        a=GetSudokuFromFile_1(f,3);
        start=clock();
        Solver(a);
        t=clock()-start;
        time+=t;
        if(tmax<t){
            imax=i;
            tmax=t;
        }
        if(IsSolution(a))
            x++;
        printf("\rSudoku risolti: %d/%d %.3f%% Tempo medio: %.3f ms Tempo max: %ld ms (%d)",
           x,i+1,(float)x*100/(i+1),(double)(time)/((i+1))/CLOCKS_PER_SEC*1000,(long int)(tmax)*1000/CLOCKS_PER_SEC,imax+1);
        FreeSudoku(a);
    }
    #ifdef WINDOWS
    system("pause");
    #endif // WINDOWS
    return 0;
}
