#include "Sudoku.h"

void exit_error(char *In_string);

int Regola_4(Sudoku In_sudoku){
    int i,j,I,J,k,z,changed=0,allowedValueIntersectionBlock[SIZE_MAX_MATRIX],allowedValue[SIZE_MAX_MATRIX];
    if(In_sudoku==NULL)
        exit_error("Regola_4(): In_sudoku==NULL");
    ///Analisi righe
    for(I=0;I<In_sudoku->sizeOfMatrix;I+=In_sudoku->sizeOfSubMatrix)
        for(i=I;i<I+In_sudoku->sizeOfSubMatrix;i++){
            ///azzera conteggio elementi in riga
            for(j=0;j<In_sudoku->sizeOfMatrix;j++)
                allowedValue[j]=0;
            ///Conta elementi in riga
            for(j=0;j<In_sudoku->sizeOfMatrix;j++)
                for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                    allowedValue[k]+=In_sudoku->matrix[i][j]->allowedValue[k];
            ///analizza intersezione blocco-riga
            for(J=0;J<In_sudoku->sizeOfMatrix;J+=In_sudoku->sizeOfSubMatrix){
                ///azzera conteggio elementi in intersezione
                for(j=0;j<In_sudoku->sizeOfMatrix;j++)
                    allowedValueIntersectionBlock[j]=0;
                ///conta elementi in intersezione
                for(j=J;j<J+In_sudoku->sizeOfSubMatrix;j++)
                    for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                        allowedValueIntersectionBlock[k]+=In_sudoku->matrix[i][j]->allowedValue[k];
                ///controlla la veridicita della regola
                for(j=0;j<In_sudoku->sizeOfMatrix;j++)
                    if(allowedValue[j]==allowedValueIntersectionBlock[j]){
                        ///Eliminazione righe esterne all'intersezione, internamente al blocco
                        for(k=i-1;k>=I;k--)
                            for(z=J;z<J+In_sudoku->sizeOfSubMatrix;z++)
                                if(In_sudoku->matrix[k][z]->allowedValue[j]==1){
                                    In_sudoku->matrix[k][z]->allowedValue[j]=0;
                                    changed++;
                                }
                        for(k=i+1;k<I+In_sudoku->sizeOfSubMatrix;k++)
                            for(z=J;z<J+In_sudoku->sizeOfSubMatrix;z++)
                                if(In_sudoku->matrix[k][z]->allowedValue[j]==1){
                                    In_sudoku->matrix[k][z]->allowedValue[j]=0;
                                    changed++;
                                }
                    }
            }
        }
    ///Analisi colonne
    for(J=0;J<In_sudoku->sizeOfMatrix;J+=In_sudoku->sizeOfSubMatrix)
        for(j=J;j<J+In_sudoku->sizeOfSubMatrix;j++){
            ///azzera conteggio elementi in colonna
            for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                allowedValue[i]=0;
            ///Conta elementi in colonna
            for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                    allowedValue[k]+=In_sudoku->matrix[i][j]->allowedValue[k];
            ///analizza intersezione blocco-colonna
            for(I=0;I<In_sudoku->sizeOfMatrix;I+=In_sudoku->sizeOfSubMatrix){
                ///azzera conteggio elementi in intersezione
                for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                    allowedValueIntersectionBlock[i]=0;
                ///conta elementi in intersezione
                for(i=I;i<I+In_sudoku->sizeOfSubMatrix;i++)
                    for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                        allowedValueIntersectionBlock[k]+=In_sudoku->matrix[i][j]->allowedValue[k];
                ///controlla la veridicita della regola
                for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                    if(allowedValue[i]==allowedValueIntersectionBlock[i]){
                        ///Eliminazione colonne esterne all'intersezione, internamente al blocco
                        for(k=j-1;k>=J;k--)
                            for(z=I;z<I+In_sudoku->sizeOfSubMatrix;z++)
                                if(In_sudoku->matrix[z][k]->allowedValue[i]==1){
                                    In_sudoku->matrix[z][k]->allowedValue[i]=0;
                                    changed++;
                                }
                        for(k=j+1;k<J+In_sudoku->sizeOfSubMatrix;k++)
                            for(z=I;z<I+In_sudoku->sizeOfSubMatrix;z++)
                                if(In_sudoku->matrix[z][k]->allowedValue[i]==1){
                                    In_sudoku->matrix[z][k]->allowedValue[i]=0;
                                    changed++;
                                }
                    }
            }
        }
    return changed;
}

