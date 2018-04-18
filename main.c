#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int matrixSize=1000;
int **mt,**m1,**m2,**m3;
clock_t startTime, stopTime;

void generateMatrix()
{
    m1 = malloc(matrixSize*sizeof(int*));
    m2 = malloc(matrixSize*sizeof(int*));
    m3 = malloc(matrixSize*sizeof(int*));
    mt = malloc(matrixSize*sizeof(int*));
    for(int i=0;i<matrixSize;i++) {
        m1[i]=malloc(matrixSize*sizeof(int));
        m2[i]=malloc(matrixSize*sizeof(int));
        m3[i]=malloc(matrixSize*sizeof(int));
        mt[i]=malloc(matrixSize*sizeof(int));
    }

    for(int r=0;r<matrixSize;r++)
        for(int c=0;c<matrixSize;c++)
        {
            m1[r][c]=rand()%100;
            m2[r][c]=rand()%100;
        }
}

void zeroMatrix()
{
    for(int w=0;w<matrixSize;w++)
    {
        for(int k=0;k<matrixSize;k++)
        {
            m3[w][k]=0;
        }
    }
}

void multiplyMatrixColAdd()
{
    for (int w = 0; w < matrixSize; ++w)
        for (int k = 0; k < matrixSize; ++k)
            for (int p = 0; p < matrixSize; ++p)
                m3[w][k] += m1[w][p] * m2[p][k];
}

void multiplyMatrixRowAdd()
{
    for (int i = 0; i < matrixSize; i++)
        for (int j = 0; j < matrixSize; j++)
            mt[i][j] = m2[j][i];

    for (int w = 0; w < matrixSize; w++)
        for (int k = 0; k < matrixSize; k++)
            for (int p = 0; p < matrixSize; p++)
            {
                m3[w][k] += m1[w][p] * mt[k][p];
            }
}


void multiplyMatrixColIf()
{
    for (int w = 0; w < matrixSize; ++w)
        for (int k = 0; k < matrixSize; ++k)
            for (int p = 0; p < matrixSize; ++p)
                if(m1[w][p] && m2[p][k])
                {
                    m3[w][k]=1;
                    break;
                }
}

void multiplyMatrixRowIf()
{
    for (int i = 0; i < matrixSize; i++)
        for (int j = 0; j < matrixSize; j++)
            mt[i][j] = m2[j][i];

    for (int w = 0; w < matrixSize; w++)
        for (int k = 0; k < matrixSize; k++)
            for (int p = 0; p < matrixSize; p++)
                if(m1[w][p] && m2[k][p])
                {
                    m3[w][k]=1;
                    break;
                }
}

void printMatrix()
{
    printf("\n");
    for(int c=0;c<matrixSize;c++)
    {
        for(int s=-1;s<matrixSize;s++)
            printf("  ");
        for(int r=0;r<matrixSize;r++)
        {
            printf("%d ",m1[r][c]);
        }
        printf("\n");
    }
    printf("\n");

    for(int c=0;c<matrixSize;c++)
    {
        for(int r=0;r<matrixSize;r++)
        {
            printf("%d ",m2[r][c]);
        }
        printf("  ");
        for(int r=0;r<matrixSize;r++)
        {
            printf("%d ",m3[r][c]);
        }
        printf("\n");
    }
}

double calcTime()
{
    return (double)(stopTime - startTime)/CLOCKS_PER_SEC;
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    if (argc>1) matrixSize=atoi(argv[1]);
    generateMatrix();

    zeroMatrix();
    startTime = clock();
    multiplyMatrixRowIf();
    stopTime = clock();
    printf("\n warunkowa, wiersz-kolumna: %f\n\n",calcTime());

    zeroMatrix();
    startTime = clock();
    multiplyMatrixRowIf();
    stopTime = clock();
    printf("\n warunkowa, wiersz-wiersz: %f\n\n",calcTime());

    zeroMatrix();
    startTime = clock();
    multiplyMatrixColAdd();
    stopTime = clock();
    printf("\n dodawanie, wiersz-kolumna: %f\n\n",calcTime());

    zeroMatrix();
    startTime = clock();
    multiplyMatrixRowAdd();
    stopTime = clock();
    printf("\n dodawanie, wiersz-wiersz: %f\n\n",calcTime());
}
