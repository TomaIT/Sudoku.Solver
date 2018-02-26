#include "Sudoku.h"

void exit_error(char *In_string);

int Regola_3(Sudoku In_sudoku){
    int i,j,I,J,k,changed=0,allowedValueBlock[SIZE_MAX_MATRIX],allowedValue[SIZE_MAX_MATRIX];
    if(In_sudoku==NULL)
        exit_error("Regola_3(): In_sudoku==NULL");
    for(I=0;I<In_sudoku->sizeOfMatrix;I+=In_sudoku->sizeOfSubMatrix)
        for(J=0;J<In_sudoku->sizeOfMatrix;J+=In_sudoku->sizeOfSubMatrix){
            for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                allowedValueBlock[i]=0;
            ///Conteggio elementi possibili nel blocco
            for(i=I;i<I+In_sudoku->sizeOfSubMatrix;i++)
                for(j=J;j<J+In_sudoku->sizeOfSubMatrix;j++)
                    for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                        allowedValueBlock[k]+=In_sudoku->matrix[i][j]->allowedValue[k];
            ///Analisi righe del blocco
            for(i=I;i<I+In_sudoku->sizeOfSubMatrix;i++){
                for(j=0;j<In_sudoku->sizeOfMatrix;j++)
                    allowedValue[j]=0;
                for(j=J;j<J+In_sudoku->sizeOfSubMatrix;j++)
                    for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                        allowedValue[k]+=In_sudoku->matrix[i][j]->allowedValue[k];
                for(j=0;j<In_sudoku->sizeOfMatrix;j++)
                    if(allowedValue[j]==allowedValueBlock[j]){
                        ///Eliminazione da riga fuori dal blocco
                        for(k=J-1;k>=0;k--)
                            if(In_sudoku->matrix[i][k]->allowedValue[j]==1){
                                In_sudoku->matrix[i][k]->allowedValue[j]=0;
                                changed++;
                            }
                        for(k=J+In_sudoku->sizeOfSubMatrix;k<In_sudoku->sizeOfMatrix;k++)
                            if(In_sudoku->matrix[i][k]->allowedValue[j]==1){
                                In_sudoku->matrix[i][k]->allowedValue[j]=0;
                                changed++;
                            }
                    }
            }
            ///Analisi colonne del blocco
            for(j=J;j<J+In_sudoku->sizeOfSubMatrix;j++){
                for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                    allowedValue[i]=0;
                for(i=I;i<I+In_sudoku->sizeOfSubMatrix;i++)
                    for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                        allowedValue[k]+=In_sudoku->matrix[i][j]->allowedValue[k];
                for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                    if(allowedValue[i]==allowedValueBlock[i]){
                        ///Eliminazione da colonna fuori dal blocco
                        for(k=I-1;k>=0;k--)
                            if(In_sudoku->matrix[k][j]->allowedValue[i]==1){
                                In_sudoku->matrix[k][j]->allowedValue[i]=0;
                                changed++;
                            }
                        for(k=I+In_sudoku->sizeOfSubMatrix;k<In_sudoku->sizeOfMatrix;k++)
                            if(In_sudoku->matrix[k][j]->allowedValue[i]==1){
                                In_sudoku->matrix[k][j]->allowedValue[i]=0;
                                changed++;
                            }
                    }
            }
        }
    return changed;
}
