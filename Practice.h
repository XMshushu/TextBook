#include "Textbook.h"


//以下为课后习题

//11.寻找顺序储存结构的完全二叉树中编号i和j最近的共同祖先节点
int GetSharedAncestor(SqBiTree T,int i,int j){
    if(i<1 || j<1 || i==j || i>T.lastIndex || j>T.lastIndex) return FALSE;
    while (i>1 && j>1){
        i=i/2;
        j=j/2;
        if(i==j)
            return i;
    }
}

//12.求二叉链表存储的完全二叉树的最后一层的最后一个节点
BiTNode* GetLastBiNode(BiTree T){
    if(T!=NULL){
        BiTree p;
        SqlQueue q;
        initSqlQueue(q);
        enQueue(q,T);
        printf("%c",T->data);
        while (true==deQueue(q,p)){
            if(p->lChild!=NULL) {
                printf("%c",p->lChild->data);
                enQueue(q, p->lChild);
            }
            if(p->rChild!=NULL) {
                printf("%c",p->rChild->data);
                enQueue(q, p->rChild);
            }
        }
        return p;
    }
}
//助研 树
//P122-1
int BiTreeDepth1(BiTree T){
    int depthLeft,depthRight;
    if(T==NULL)return 0;
    else{
        depthLeft= BiTreeDepth1(T->lChild);
        depthRight= BiTreeDepth1(T->rChild);
        return (depthLeft>depthRight?depthLeft:depthRight)+1;
    }
}
