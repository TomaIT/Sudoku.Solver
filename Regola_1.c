#include "Sudoku.h"



static Sudoku SUDOKU;
static int CHANGED,COL[SIZE_MAX_MATRIX],ROW[SIZE_MAX_MATRIX],ALLOWEDVALUE[SIZE_MAX_MATRIX]={0},K,R,C;
void exit_error(char *In_string);

static void Powerset_SubMatrix_Row(int pos,int c){
    int i,j;
    if(pos==K){
        for(i=0,j=0;i<SUDOKU->sizeOfMatrix;i++)
            if(ALLOWEDVALUE[i]!=0)
                j++;
        if(j==K)
            for(i=0;i<SUDOKU->sizeOfMatrix;i++){
                for(j=0;j<pos;j++)
                    if(COL[j]==i)
                        break;
                if(j==pos)
                    for(j=0;j<SUDOKU->sizeOfMatrix;j++)
                        if(ALLOWEDVALUE[j]!=0&&SUDOKU->matrix[R][i]->allowedValue[j]==1){
                            SUDOKU->matrix[R][i]->allowedValue[j]=0;
                            CHANGED++;
                        }
            }
        return;
    }
    for(i=c;i<SUDOKU->sizeOfMatrix;i++){
        for(j=0;j<SUDOKU->sizeOfMatrix;j++)
            ALLOWEDVALUE[j]+=SUDOKU->matrix[R][i]->allowedValue[j];
        COL[pos]=i;
        Powerset_SubMatrix_Row(pos+1,i+1);
        for(j=0;j<SUDOKU->sizeOfMatrix;j++)
            ALLOWEDVALUE[j]-=SUDOKU->matrix[R][i]->allowedValue[j];
    }
}
static void Powerset_SubMatrix_Col(int pos,int r){
    int i,j;
    if(pos==K){
        for(i=0,j=0;i<SUDOKU->sizeOfMatrix;i++)
            if(ALLOWEDVALUE[i]!=0)
                j++;
        if(j==K)
            for(i=0;i<SUDOKU->sizeOfMatrix;i++){
                for(j=0;j<pos;j++)
                    if(ROW[j]==i)
                        break;
                if(j==pos)
                    for(j=0;j<SUDOKU->sizeOfMatrix;j++)
                        if(ALLOWEDVALUE[j]!=0&&SUDOKU->matrix[i][C]->allowedValue[j]==1){
                            SUDOKU->matrix[i][C]->allowedValue[j]=0;
                            CHANGED++;
                        }
            }
        return;
    }
    for(i=r;i<SUDOKU->sizeOfMatrix;i++){
        for(j=0;j<SUDOKU->sizeOfMatrix;j++)
            ALLOWEDVALUE[j]+=SUDOKU->matrix[i][C]->allowedValue[j];
        ROW[pos]=i;
        Powerset_SubMatrix_Col(pos+1,i+1);
        for(j=0;j<SUDOKU->sizeOfMatrix;j++)
            ALLOWEDVALUE[j]-=SUDOKU->matrix[i][C]->allowedValue[j];
    }
}
static void Powerset_SubMatrix_Block(int pos,int x){
    int i,j,z;
    if(pos==K){
        for(i=0,j=0;i<SUDOKU->sizeOfMatrix;i++)
            if(ALLOWEDVALUE[i]!=0)
                j++;
        if(j==K)
            for(i=R;i<R+SUDOKU->sizeOfSubMatrix;i++)
                for(j=C;j<C+SUDOKU->sizeOfSubMatrix;j++){
                    for(z=0;z<pos;z++)
                        if(ROW[z]==i&&COL[z]==j)
                            break;
                    if(z==pos)
                        for(z=0;z<SUDOKU->sizeOfMatrix;z++)
                            if(ALLOWEDVALUE[z]!=0&&SUDOKU->matrix[i][j]->allowedValue[z]==1){
                                SUDOKU->matrix[i][j]->allowedValue[z]=0;
                                CHANGED++;
                            }
                }
        return;
    }
    for(i=R+x/SUDOKU->sizeOfSubMatrix;i<R+SUDOKU->sizeOfSubMatrix;i++)
        for(j=C+x%SUDOKU->sizeOfSubMatrix;j<C+SUDOKU->sizeOfSubMatrix;j++){
            x++;
            for(z=0;z<SUDOKU->sizeOfMatrix;z++)
                ALLOWEDVALUE[z]+=SUDOKU->matrix[i][j]->allowedValue[z];
            COL[pos]=j;
            ROW[pos]=i;
            Powerset_SubMatrix_Block(pos+1,x);
            for(z=0;z<SUDOKU->sizeOfMatrix;z++)
                ALLOWEDVALUE[z]-=SUDOKU->matrix[i][j]->allowedValue[z];
        }
}

int Regola_1(Sudoku In_sudoku,int In_K){
    int i,j,maxValueOfPartition;
    if(In_sudoku==NULL)
        exit_error("SolutionSudokuRule_1(): In_sudoku==NULL");
    SUDOKU=In_sudoku;
    CHANGED=0;
    ///Sottomatrice di base riga
    for(R=0;R<In_sudoku->sizeOfMatrix;R++){
        for(i=0,maxValueOfPartition=1;i<In_sudoku->sizeOfMatrix&&maxValueOfPartition<In_sudoku->sizeOfMatrix;i++)
            if(In_sudoku->matrix[R][i]->value==VALUE_NULL)
                maxValueOfPartition++;
        if(In_K<maxValueOfPartition){
            K=In_K;
            Powerset_SubMatrix_Row(0,0);
        }
    }
    ///Sottomatrice di base colonna
    for(C=0;C<In_sudoku->sizeOfMatrix;C++){
        for(i=0,maxValueOfPartition=1;i<In_sudoku->sizeOfMatrix&&maxValueOfPartition<In_sudoku->sizeOfMatrix;i++)
            if(In_sudoku->matrix[i][C]->value==VALUE_NULL)
                maxValueOfPartition++;
        if(In_K<maxValueOfPartition){
            K=In_K;
            Powerset_SubMatrix_Col(0,0);
        }
    }
    ///Sottomatrice di base blocco
    for(R=0;R<In_sudoku->sizeOfMatrix;R+=In_sudoku->sizeOfSubMatrix)
        for(C=0;C<In_sudoku->sizeOfMatrix;C+=In_sudoku->sizeOfSubMatrix){
            for(i=R,maxValueOfPartition=1;i<R+In_sudoku->sizeOfSubMatrix&&maxValueOfPartition<In_sudoku->sizeOfMatrix;i++)
                for(j=C;j<C+In_sudoku->sizeOfSubMatrix&&maxValueOfPartition<In_sudoku->sizeOfMatrix;j++)
                    if(In_sudoku->matrix[i][j]->value==VALUE_NULL)
                        maxValueOfPartition++;
            if(In_K<maxValueOfPartition){
                K=In_K;
                Powerset_SubMatrix_Block(0,0);
            }
        }
    return CHANGED;
}
