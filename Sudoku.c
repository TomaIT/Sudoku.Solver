#include "Sudoku.h"

void exit_error(char *In_string){
    printf("Sudoku.h --> %s\n",In_string);
    exit(EXIT_FAILURE);
}


Sudoku GetSudokuInitial(int In_sizeOfSubMatrix){
    Sudoku Out_sudoku;
    int i,j,k;
    if(In_sizeOfSubMatrix<2)
        exit_error("GetSudokuInitial(): In_sizeOfSubMatrix<2");
    if(In_sizeOfSubMatrix>SIZE_MAX_SUBMATRIX)
        exit_error("GetSudokuInitial(): In_sizeOfSubMatrix>SIZE_MAX_SUBMATRIX");
    Out_sudoku=malloc(sizeof(struct Sudoku_));
    if(Out_sudoku==NULL)
        exit_error("GetSudokuInitial(): Out_sudoku==NULL");
    Out_sudoku->sizeOfSubMatrix=In_sizeOfSubMatrix;
    Out_sudoku->sizeOfMatrix=In_sizeOfSubMatrix*In_sizeOfSubMatrix;
    Out_sudoku->matrix=malloc(sizeof(Cell*)*Out_sudoku->sizeOfMatrix);
    if(Out_sudoku->matrix==NULL)
        exit_error("GetSudokuInitial(): Out_sudoku->matrix==NULL");
    for(i=0;i<Out_sudoku->sizeOfMatrix;i++){
        Out_sudoku->matrix[i]=malloc(sizeof(Cell)*Out_sudoku->sizeOfMatrix);
        if(Out_sudoku->matrix[i]==NULL)
            exit_error("GetSudokuInitial(): Out_sudoku->matrix[i]==NULL");
        for(j=0;j<Out_sudoku->sizeOfMatrix;j++){
            Out_sudoku->matrix[i][j]=malloc(sizeof(struct Cell_));
            if(Out_sudoku->matrix[i][j]==NULL)
                exit_error("GetSudokuInitial(): Out_sudoku->matrix[i][j]==NULL");
            Out_sudoku->matrix[i][j]->allowedValue=malloc(sizeof(int)*Out_sudoku->sizeOfMatrix);
            if(Out_sudoku->matrix[i][j]->allowedValue==NULL)
                exit_error("GetSudokuInitial(): Out_sudoku->matrix[i][j]->allowedValue==NULL");
            for(k=0;k<Out_sudoku->sizeOfMatrix;k++)
                Out_sudoku->matrix[i][j]->allowedValue[k]=1;
            Out_sudoku->matrix[i][j]->value=VALUE_NULL;
        }
    }
    return Out_sudoku;
}
Sudoku GetSudokuFromFile(FILE *In_file,int In_sizeOfSubMatrix){
    Sudoku Out_sudoku;
    int i,j,k;
    if(In_file==NULL)
        exit_error("GetSudokuFromFile(): In_file==NULL");
    Out_sudoku=GetSudokuInitial(In_sizeOfSubMatrix);
    for(i=0;i<Out_sudoku->sizeOfMatrix;i++)
        for(j=0;j<Out_sudoku->sizeOfMatrix;j++){
            if(fscanf(In_file,"%d",&Out_sudoku->matrix[i][j]->value)!=1)
                exit_error("GetSudokuFromFile(): fscanf(In_file,%d,&Out_sudoku->matrix[i][j]->value)!=1");
            if(Out_sudoku->matrix[i][j]->value!=VALUE_NULL)
                for(k=0;k<Out_sudoku->sizeOfMatrix;k++)
                    if(Out_sudoku->matrix[i][j]->value!=k+1)
                        Out_sudoku->matrix[i][j]->allowedValue[k]=0;
        }
    return Out_sudoku;
}
Sudoku GetSudokuFromFile_1(FILE *In_file,int In_sizeOfSubMatrix){
    Sudoku Out_sudoku;
    int i,j,k;
    if(In_file==NULL)
        exit_error("GetSudokuFromFile(): In_file==NULL");
    Out_sudoku=GetSudokuInitial(In_sizeOfSubMatrix);
    for(i=0;i<Out_sudoku->sizeOfMatrix;i++)
        for(j=0;j<Out_sudoku->sizeOfMatrix;j++){
            if(i==0&&j==0){
                if(fscanf(In_file,"%d",&Out_sudoku->matrix[i][j]->value)!=1)
                    exit_error("GetSudokuFromFile(): fscanf(In_file,%d,&Out_sudoku->matrix[i][j]->value)!=1");
            }
            else{
                if(fscanf(In_file,".%d",&Out_sudoku->matrix[i][j]->value)!=1)
                    exit_error("GetSudokuFromFile(): fscanf(In_file,%d,&Out_sudoku->matrix[i][j]->value)!=1");
            }
            if(Out_sudoku->matrix[i][j]->value!=VALUE_NULL)
                for(k=0;k<Out_sudoku->sizeOfMatrix;k++)
                    if(Out_sudoku->matrix[i][j]->value!=k+1)
                        Out_sudoku->matrix[i][j]->allowedValue[k]=0;
        }
    return Out_sudoku;
}
Sudoku CopySudoku(Sudoku In_sudoku){
    Sudoku out;
    int i,j,k;
    if(In_sudoku==NULL)
        exit_error("CopySudoku(): In_sudoku==NULL");
    out=GetSudokuInitial(In_sudoku->sizeOfSubMatrix);
    for(i=0;i<In_sudoku->sizeOfMatrix;i++)
        for(j=0;j<In_sudoku->sizeOfMatrix;j++){
            out->matrix[i][j]->value=In_sudoku->matrix[i][j]->value;
            for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                out->matrix[i][j]->allowedValue[k]=In_sudoku->matrix[i][j]->allowedValue[k];
        }
    return out;
}
void FreeSudoku(Sudoku In_sudoku){
    int i,j;
    if(In_sudoku!=NULL){
        if(In_sudoku->matrix!=NULL){
            for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                if(In_sudoku->matrix[i]!=NULL){
                    for(j=0;j<In_sudoku->sizeOfMatrix;j++)
                        if(In_sudoku->matrix[i][j]!=NULL){
                            if(In_sudoku->matrix[i][j]->allowedValue!=NULL)
                                free(In_sudoku->matrix[i][j]->allowedValue);
                            free(In_sudoku->matrix[i][j]);
                        }
                    free(In_sudoku->matrix[i]);
                }
            free(In_sudoku->matrix);
        }
        free(In_sudoku);
    }
}
void PrintSudokuAll(FILE *In_file,Sudoku In_sudoku){
    int i,j,k;
    if(In_file==NULL)
        exit_error("PrintSudokuAll(): In_file==NULL");
    if(In_sudoku==NULL)
        exit_error("PrintSudokuAll(): In_sudoku==NULL");
    fprintf(In_file,"Schema\n");
    for(i=0;i<In_sudoku->sizeOfMatrix;i++){
        for(j=0;j<In_sudoku->sizeOfMatrix;j++){
            fprintf(In_file,"%2d ",In_sudoku->matrix[i][j]->value);
            if(j%In_sudoku->sizeOfSubMatrix==In_sudoku->sizeOfSubMatrix-1)
                fprintf(In_file," ");
        }
        fprintf(In_file,"\n");
        if(i%In_sudoku->sizeOfSubMatrix==In_sudoku->sizeOfSubMatrix-1)
            fprintf(In_file,"\n");
    }
    fprintf(In_file,"\nValori Ammessi\n");
    for(i=0;i<In_sudoku->sizeOfMatrix;i++)
        for(j=0;j<In_sudoku->sizeOfMatrix;j++){
            fprintf(In_file,"<%d,%d>:",i,j);
            for(k=0;k<In_sudoku->sizeOfMatrix;k++)
                if(In_sudoku->matrix[i][j]->allowedValue[k])
                    fprintf(In_file," %d",k+1);
            fprintf(In_file,"\n");
        }
}
void PrintSudoku(FILE *In_file,Sudoku In_sudoku){
     int i,j;
    if(In_file==NULL)
        exit_error("PrintSudoku(): In_file==NULL");
    if(In_sudoku==NULL)
        exit_error("PrintSudoku(): In_sudoku==NULL");
    for(i=0;i<In_sudoku->sizeOfMatrix;i++){
        for(j=0;j<In_sudoku->sizeOfMatrix;j++){
            fprintf(In_file,"%2d ",In_sudoku->matrix[i][j]->value);
            if(j%In_sudoku->sizeOfSubMatrix==In_sudoku->sizeOfSubMatrix-1)
                fprintf(In_file," ");
        }
        fprintf(In_file,"\n");
        if(i%In_sudoku->sizeOfSubMatrix==In_sudoku->sizeOfSubMatrix-1)
            fprintf(In_file,"\n");
    }
}
int IsSolution(Sudoku In_sudoku){
    int i,j,I,J,flag[SIZE_MAX_MATRIX];
    if(In_sudoku==NULL)
        exit_error("IsSolution(): In_sudoku==NULL");
    for(i=0;i<In_sudoku->sizeOfMatrix;i++)
        for(j=0;j<In_sudoku->sizeOfMatrix;j++)
            if(In_sudoku->matrix[i][j]->value==VALUE_NULL)
                return 0;
    for(i=0;i<In_sudoku->sizeOfMatrix;i++){
        /**Analisi insieme di simboli della sottomatrice di base riga**/
        for(j=0;j<In_sudoku->sizeOfMatrix;j++)
            flag[j]=0;
        for(j=0;j<In_sudoku->sizeOfMatrix;j++)
            flag[In_sudoku->matrix[i][j]->value-1]++;
        for(j=0;j<In_sudoku->sizeOfMatrix;j++)
            if(flag[j]!=1)
                return 0;
        /**Analisi insieme di simboli della sottomatrice di base colonna**/
        for(j=0;j<In_sudoku->sizeOfMatrix;j++)
            flag[j]=0;
        for(j=0;j<In_sudoku->sizeOfMatrix;j++)
            flag[In_sudoku->matrix[j][i]->value-1]++;
        for(j=0;j<In_sudoku->sizeOfMatrix;j++)
            if(flag[j]!=1)
                return 0;
    }
    for(I=0;I<In_sudoku->sizeOfMatrix;I+=In_sudoku->sizeOfSubMatrix)
        for(J=0;J<In_sudoku->sizeOfMatrix;J+=In_sudoku->sizeOfSubMatrix){
            /**Analisi insieme di simboli della sottomatrice di base blocco**/
            for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                flag[i]=0;
            for(i=I;i<I+In_sudoku->sizeOfSubMatrix;i++)
                for(j=J;j<J+In_sudoku->sizeOfSubMatrix;j++)
                    flag[In_sudoku->matrix[i][j]->value-1]++;
            for(i=0;i<In_sudoku->sizeOfMatrix;i++)
                if(flag[i]!=1)
                    return 0;
        }
    return 1;
}
int InsertSudokuAllowedValueSingle(Sudoku In_sudoku){
    int i,j,k,c,r,flag=0;
    for(i=0;i<In_sudoku->sizeOfMatrix;i++)
        for(j=0;j<In_sudoku->sizeOfMatrix;j++){
            for(k=0,c=0;k<In_sudoku->sizeOfMatrix;k++)
                if(In_sudoku->matrix[i][j]->allowedValue[k]==1){
                    c++;
                    r=k+1;
                }
            if(c==1){
                if(In_sudoku->matrix[i][j]->value==VALUE_NULL)
                    flag++;
                In_sudoku->matrix[i][j]->value=r;
            }
        }
    return flag;
}
