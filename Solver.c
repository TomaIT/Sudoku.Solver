#include "Sudoku.h"

void exit_error(char *In_string);

static int Pruning(int r,int c,Sudoku a){
    int i,j,imax=r-r%a->sizeOfSubMatrix+a->sizeOfSubMatrix,jmax=c-c%a->sizeOfSubMatrix+a->sizeOfSubMatrix;
    for(i=0;i<a->sizeOfMatrix;i++)
        if((r!=i&&a->matrix[i][c]->value==a->matrix[r][c]->value)||(c!=i&&a->matrix[r][i]->value==a->matrix[r][c]->value))
            return 0;
    for(i=r-r%a->sizeOfSubMatrix;i<imax;i++)
        for(j=c-c%a->sizeOfSubMatrix;j<jmax;j++)
            if((i!=r||j!=c)&&(a->matrix[i][j]->value==a->matrix[r][c]->value))
                return 0;
    return 1;
}

static int BruteForce_Logica(int r,int c,Sudoku a){
    int i;
    if(r>=a->sizeOfMatrix)
        return 1;
    if(a->matrix[r][c]->value==VALUE_NULL){
        for(i=0;i<a->sizeOfMatrix;i++)
            if(a->matrix[r][c]->allowedValue[i]){
                a->matrix[r][c]->value=i+1;
                if(Pruning(r,c,a)){
                    if(c==a->sizeOfMatrix-1){
                        if(BruteForce_Logica(r+1,0,a))
                            return 1;
                    }
                    else
                        if(BruteForce_Logica(r,c+1,a))
                            return 1;
                }
                a->matrix[r][c]->value=VALUE_NULL;
            }
    }
    else{
        if(c==a->sizeOfMatrix-1){
            if(BruteForce_Logica(r+1,0,a))
                return 1;
        }
        else
            if(BruteForce_Logica(r,c+1,a))
                    return 1;
    }
    return 0;
}

void Solver(Sudoku In_sudoku){
    int changed,changedTot,k;
    if(In_sudoku==NULL)
        exit_error("Solver(): In_sudoku==NULL");
    do{
        changedTot=0;
        changedTot=Regola_1(In_sudoku,1);
        if(changedTot){
            InsertSudokuAllowedValueSingle(In_sudoku);
            if(IsSolution(In_sudoku))
                return;
        }
        changed=Regola_3(In_sudoku);
        if(changed){
            InsertSudokuAllowedValueSingle(In_sudoku);
            if(IsSolution(In_sudoku))
                return;
            changedTot+=changed;
        }
        changed=Regola_2(In_sudoku);
        if(changed){
            InsertSudokuAllowedValueSingle(In_sudoku);
            if(IsSolution(In_sudoku))
                return;
            changedTot+=changed;
        }
        changed=Regola_4(In_sudoku);
        if(changed){
            InsertSudokuAllowedValueSingle(In_sudoku);
            if(IsSolution(In_sudoku))
                return;
            changedTot+=changed;
        }

       if(!changedTot){
            for(k=2;k<In_sudoku->sizeOfMatrix&&!changedTot;k++)
                    changedTot=Regola_1(In_sudoku,k);
            if(changedTot){
                InsertSudokuAllowedValueSingle(In_sudoku);
                if(IsSolution(In_sudoku))
                    return;
            }
        }
    }while(changedTot);

    //PrintSudokuAll(stdout,In_sudoku);
    //system("PAUSE");
    BruteForce_Logica(0,0,In_sudoku);
   return;
}
