#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>
#define VALUE_NULL 0
/**
Si definisce una dimensione massima per la gestione di variabili di appoggio delle funzioni,
questo ci permette una gestione più efficiente (no malloc).
**/
#define SIZE_MAX_SUBMATRIX 10
#define SIZE_MAX_MATRIX SIZE_MAX_SUBMATRIX*SIZE_MAX_SUBMATRIX

typedef struct Cell_ *Cell;
typedef struct Sudoku_ *Sudoku;

struct Cell_{
    int *allowedValue;
    int value;
};
struct Sudoku_{
    Cell **matrix;
    int sizeOfSubMatrix;
    int sizeOfMatrix;
    //int countOfCellFilled;
};

/**
Gli errori vengono gestiti tramite un funzione interna exit_error(char *),
che forza la chiusura dell'intero processo.
**/
/** GetSudokuInital();
Crea un oggetto sudoku, di dimensione In_sizeOfSubmatrix*In_sizeOfSubMatrix,
inizializza i valori a VALUE_NULL e il vettore allowedValue lo pone tutto a 1 (valori permessi tutti).
**/
Sudoku GetSudokuInitial(int In_sizeOfSubMatrix);
/** GetSudokuFromFile();
Crea un oggetto sudoku, di dimensione In_sizeOfSubmatrix*In_sizeOfSubMatrix,
prende in input i primi valori interi da file *In_file per poter riempire la matrix,
considera come valore nullo VALUE_NULL, e in allowedValue lascia l'unico (o tutti) i valori permessi.
**/
Sudoku GetSudokuFromFile(FILE *In_file,int In_sizeOfSubMatrix);
Sudoku GetSudokuFromFile_1(FILE *In_file,int In_sizeOfSubMatrix);
/**PrintSudokuAll();
Stampa su file *In_file, l'intero oggetto In_sudoku.
**/
Sudoku CopySudoku(Sudoku In_sudoku);
void PrintSudokuAll(FILE *In_file,Sudoku In_sudoku);

void PrintSudoku(FILE *In_file,Sudoku In_sudoku);
/** FreeSudoku();
Libera la memoria, e cancella l'oggetto In_sudoku.
**/
void FreeSudoku(Sudoku In_sudoku);
/** IsSolution();
Verifica se l'oggetto In_sudoku può essere soluzione di un generico schema di partenza,
in questo caso ritorna 1 altrimenti 0.
allowedValue non viene considerato ai fini della valutazione.
**/
int IsSolution(Sudoku In_sudoku);
/** InsertSudokuAllowedValueSingle();
Inserisci definitivamente i valori ammisibili singoli per ogni cella.
Ritorna il numero di inserimenti nuovi eseguiti.
**/
int InsertSudokuAllowedValueSingle(Sudoku In_sudoku);

int Regola_1(Sudoku In_sudoku,int In_K);
int Regola_2(Sudoku In_sudoku);
int Regola_3(Sudoku In_sudoku);
int Regola_4(Sudoku In_sudoku);

void Solver(Sudoku In_sudoku);


#endif // SUDOKU_H
