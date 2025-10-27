#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MIN_SIZE 2
#define MAX_SIZE 10

void generateRandomMatrix(int size, int matrix[]);
void rotateMatrixBy90Deg(int size, int matrix[]);
void smoothenMatrix(int size, int matrix[]);
void swapValues(int *top,int *right,int *bottom,int* left);
void printMatrix(int size, int matrix[]);
void assignValues(int **top,int **right,int **bottom,int **left,int matrix[],int offset, int first, int last, int size);
void addValues(int size, int *matrix, int prevRow[],int i);

int main()
{
    int size;
    printf("Enter Matrix size(2-10): ");
    scanf("%d", &size);
    if(size<MIN_SIZE || size>MAX_SIZE)
    {
        printf("Invalid Matrix Size!\n");
        return(1);
    }
    int matrix[size*size];

    generateRandomMatrix(size,matrix);
    printf("The Original matrix is: \n");
    printMatrix(size,matrix);

    rotateMatrixBy90Deg(size,matrix);
    printf("The Rotated matrix is: \n");
    printMatrix(size,matrix);

    smoothenMatrix(size,matrix);
    printf("The Smoothened matrix: \n");
    printMatrix(size,matrix);
}



void generateRandomMatrix(int size, int matrix[])
{
    srand(time(0));

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            *(matrix + i*size + j)=rand() % 256;
        }
    }
}


void rotateMatrixBy90Deg(int size, int matrix[])
{
    for(int layer=0; layer<size/2; layer++)
    {
        int first=layer;
        int last=size-1-layer;

        for(int i=first; i<last; i++)
        {
            int offset=i-first;

            int *top,*right,*bottom,*left;

            assignValues(&top,&right,&bottom,&left,matrix,offset,first,last,size);
            swapValues(top,right,bottom,left);
        }
    }
}


void smoothenMatrix(int size, int matrix[])
{
    int prevRow[size];
    int currRow[size];
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            int sum=0;
            int count=0;
            for(int subMatrixI=-1;subMatrixI<=1;subMatrixI++)
            {
                for(int subMatrixJ=-1;subMatrixJ<=1;subMatrixJ++)
                {
                    int neighborI=i+subMatrixI;
                    int neighborJ=j+subMatrixJ;
                    if(neighborI>=0 && neighborI<size && neighborJ>=0 && neighborJ<size)
                    {
                        sum+=*(matrix+ neighborI*size + neighborJ);
                        count++;
                    }
                }
            }
            int average=sum/count;
            currRow[j]=average;
        }

        if(i>0)
        {
            addValues(size,matrix,prevRow,i);
        }

        
        for(int j=0;j<size;j++)prevRow[j]=currRow[j];        
    }
    addValues(size,matrix,prevRow,size);
}


void printMatrix(int size, int matrix[])
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            printf("%d\t",*(matrix + i*size + j));
        }
        printf("\n");
    }
    printf("\n");

}




void swapValues(int *top,int *right,int *bottom,int* left)
{
    int temp=*top;
    *top=*left;
    *left=*bottom;
    *bottom=*right;
    *right=temp;
}


void assignValues(int **top,int **right,int **bottom,int **left,int matrix[],int offset, int first, int last, int size)
{
    *top = matrix + first*size + (first+offset);
    *right = matrix + (first+offset)*size + last;
    *bottom = matrix + (last)*size + (last-offset);
    *left= matrix + (last-offset)*size + first;
}


void addValues(int size, int *matrix, int prevRow[],int i)
{
    for(int j=0;j<size;j++)
    {
        *(matrix + (i-1)*size + j)=prevRow[j];
    }
}