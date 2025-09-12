#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#define INT 0
#define FLOAT 1
#define DOUBLE 2
#define STUDENT 3

typedef struct STU
{
    char  id[20];
    char  name[20];
    float score[5];
    float total;
}STU;

typedef int ElemType;	//int  float double  STU

void SelectSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *));

void Swap(ElemType *A, int i, int j);

#endif // SORT_H_INCLUDED
