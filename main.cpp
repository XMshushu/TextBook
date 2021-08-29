#include <iostream>
#include "Textbook.h"

int main() {
    CSTree c3=MakeTree('A',0);
    CSTree c4=MakeTree('4',0);
    CSTree c2=MakeTree('2',0);
    CSTree c1=MakeTree('1',2,c2,c4);
//    char *data="ABD##E##CF##G##";
//    int i=0;
//    BiTree T=CreateBiTree(data,i);
//    int a=BiTreeDepth1(T);
//    BBSTree T=NULL;
//    RcdType r1={88};RcdType r2={29};RcdType r3={91};RcdType r4={19};RcdType r5={47};RcdType r6={32};
//    Status taller=false;
//    InsertAVL(T,r1,taller);
//    InsertAVL(T,r2,taller);
//    InsertAVL(T,r3,taller);
//    InsertAVL(T,r4,taller);
//    InsertAVL(T,r5,taller);
//    InsertAVL(T,r6,taller);
//
//    RcdSqList r={};
//    RcdType E[10]={0,98,86,58,42,42};
//    r.rcd=E;
//    r.length=6;
//    r.size=10;
//    HeapSort(r);
//    Heap H={};
//    RcdType E[10]={0,42,58,68,98,86,42};
//    MakeHeap(H,E,6,10,1, greatPrior);
//    InsertHeap(H,100);
//    RcdType a=0;
//    RemoveFirstHeap(H,a);
//    BiTree aD=(BiTree)malloc(sizeof(BiTNode));
//    aD->data='1';
//    BiTree a1=(BiTree)malloc(sizeof(BiTNode));
//    a1->data='2';
//    BiTree a2=(BiTree)malloc(sizeof(BiTNode));
//    BiTree a11=(BiTree)malloc(sizeof(BiTNode));
//    a11->data='A';
//    BiTree a22=(BiTree)malloc(sizeof(BiTNode));
//    a22->data='B';
//    a1->lChild=a11;
//    a1->rChild=a22;
//    a2->lChild=NULL;
//    a2->rChild=NULL;
//    a11->lChild=NULL;
//    a11->rChild=NULL;
//    a22->lChild=NULL;
//    a22->rChild=NULL;
//    a2->data='3';
//    aD->lChild=a1;
//    aD->rChild=a2;
//    int count=0;
//    CountLeaf(aD,count);
//    int d=0;
//    char *def="ABD##E##C##";
//    BiTree ss=CreateBiTree(def,d);
    return 0;
}
