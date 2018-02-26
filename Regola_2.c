#include "Sudoku.h"

static Sudoku SUDOKU;
static int index[SIZE_MAX_MATRIX][SIZE_MAX_MATRIX][2];
static int cambiamenti=0;
static int cella_riga;
static int cella_colonna;

static int trova_rip_cella(int k, int start_riga, int start_col){
    int cont=0, i, j;
    for (i=0; i<SUDOKU->sizeOfSubMatrix; i++){
        for (j=0; j<SUDOKU->sizeOfSubMatrix; j++)
        {
            if ((SUDOKU->matrix[i+start_riga][j+start_col]->allowedValue[k]==1)/*&& (SUDOKU->matrix[i+start_riga][j+start_col]->value==VALUE_NULL)*/){
                index[k][cont][0]=i+start_riga;
                index[k][cont++][1]=j+start_col;
            }
        }
    }
    return cont;
}

static int trova_rip_riga(int k, int riga){
    int cont=0, i;
    for (i=0; i<SUDOKU->sizeOfMatrix; i++){
        if (SUDOKU->matrix[riga][i]->allowedValue[k]==1){
            index[k][cont][0]=riga;
            index[k][cont++][1]=i;
        }
    }
    return cont;
}

static int trova_rip_colonna(int k, int colonna){
    int cont=0, i;
    for (i=0; i<SUDOKU->sizeOfMatrix; i++){
        if (SUDOKU->matrix[i][colonna]->allowedValue[k]==1){
            index[k][cont][0]=i;
            index[k][cont++][1]=colonna;
        }
    }
    return cont;
}

static int confronta_index(int k, int m, int nrip){
    int i;
    for (i=0; i<nrip; i++){
        if ((index[k][i][0]!=index[m][i][0]) || (index[k][i][1]!=index[m][i][1])){
            //printf("a\n");
            return 0;
        }
    }
    return 1;
}

//k: valore possibile
//uguali: altri valori possibili
//n: numero di valori possibili
//index: vettore con gli indici
static void setToZero(int *uguali, int n, int k){
    int i, j;
    //setto a 0 tutti
    for (i=0; i<SUDOKU->sizeOfMatrix; i++){
        for (j=0; j<n; j++){
            if (SUDOKU->matrix[index[k][j][0]][index[k][j][1]]->allowedValue[i]==1){
                cambiamenti++;
                SUDOKU->matrix[index[k][j][0]][index[k][j][1]]->allowedValue[i]=0;
            }
        }
    }
    //printf("%d\t%d\n", cambiamenti, n);
    cambiamenti-=n*n;
    //if(cambiamenti>0) printf("a\n");
    //printf("%d\n", cambiamenti);
    //risetto a 1 solo quelli con gli stessi indici
    for (i=0; i<n; i++){
        for (j=0; j<n; j++)
            SUDOKU->matrix[index[k][i][0]][index[k][i][1]]->allowedValue[uguali[j]]=1;
    }
}

static void trova_uguali(int *nrip){
    int i, cont, k, checked[SIZE_MAX_MATRIX], uguali[SIZE_MAX_MATRIX], flag;

    for (k=0; k<SUDOKU->sizeOfMatrix; k++) checked[k]=0;

    for (k=0; k<SUDOKU->sizeOfMatrix; k++){
        cont=0;
        if (!checked[k]){
            checked[k]++;
            uguali[cont++]=k;
            if (nrip[k]>0 && SUDOKU->matrix[index[k][0][0]][index[k][0][1]]->value==VALUE_NULL){
                for (i=k+1; i<SUDOKU->sizeOfMatrix; i++){
                    flag=0;
                    if (nrip[k]==nrip[i]){
                        flag=confronta_index(k, i, nrip[k]);
                        if (flag==1){
                            uguali[cont++]=i;
                            checked[i]++;
                        }
                    }
                }
                //confronta il numero di ripetizioni del numero con il numero di elementi con gli stessi indici e stesse ripetizioni
                if (nrip[k]==cont){
                    //funzione: metto a 0 tutti gli altri
                    setToZero(uguali, cont, k);
                }
            }
        }
    }
}

static void regola_2_cella(int start_riga, int start_col){
    int nrip[SIZE_MAX_MATRIX], k;

    for (k=0; k<SUDOKU->sizeOfMatrix; k++) nrip[k]=0;
    for (k=0; k<SUDOKU->sizeOfMatrix; k++){
        nrip[k]=trova_rip_cella(k, start_riga, start_col);
    }
    trova_uguali(nrip);

}

static void regola_2_riga(int riga){
    int nrip[SIZE_MAX_MATRIX], k;

    for (k=0; k<SUDOKU->sizeOfMatrix; k++) nrip[k]=0;
    for (k=0; k<SUDOKU->sizeOfMatrix; k++){
        nrip[k]=trova_rip_riga(k, riga);
    }
    trova_uguali(nrip);
}

static void regola_2_colonna(int colonna){
    int nrip[SIZE_MAX_MATRIX], k;

    for (k=0; k<SUDOKU->sizeOfMatrix; k++) nrip[k]=0;
    for (k=0; k<SUDOKU->sizeOfMatrix; k++){
        nrip[k]=trova_rip_colonna(k, colonna);
    }
    trova_uguali(nrip);
}

int Regola_2(Sudoku In_sudoku)
{
    SUDOKU=In_sudoku;
    int i, j,  riga, colonna;
    //inizializzazione numero di ripetizioni
    for (i=0; i<SUDOKU->sizeOfMatrix; i++){
        for (j=0; j<SUDOKU->sizeOfMatrix; j++){
            index[i][j][0]=-1000;
            index[i][j][1]=-1000;
        }
    }

    cambiamenti=0;

    for (cella_riga=0; cella_riga<SUDOKU->sizeOfSubMatrix; cella_riga++){
        for (cella_colonna=0; cella_colonna<SUDOKU->sizeOfSubMatrix; cella_colonna++){
            regola_2_cella(cella_riga*SUDOKU->sizeOfSubMatrix, cella_colonna*SUDOKU->sizeOfSubMatrix);
        }
    }

    for (riga=0; riga<SUDOKU->sizeOfMatrix; riga++){
        regola_2_riga(riga);
    }

    for (colonna=0; colonna<SUDOKU->sizeOfMatrix; colonna++){
        regola_2_colonna(colonna);
    }

    return cambiamenti;
}
