typedef int ElemType;
//链栈
typedef struct LSNode{
    ElemType data;
    struct LSNode *next;
}LSNode,*LStack;

//进栈
Status Push_LS(LStack &S,ElemType e){
    LSNode *t;
    t=(LSNode*)malloc(sizeof(LSNode));
    if(t==NULL) return OVERFLOW;
    t->data=e;
    t->next=S;
    S=t;
    return OK;
}

//出栈
Status Pop_LS(LStack &S,ElemType &e){
    LSNode *t;
    if(NULL==S) return ERROR;
    t=S;
    e=t->data;
    S=S->next;
    free(t);
    return OK;
}

//链队列

//链队的节点和其指针类型
typedef struct LQNode{
    ElemType data;
    struct LQNode* next;
}LQNode,*QueuePtr;

//链队列
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LQueue;

//链队列的入队
Status EnQueue_LQ(LQueue &Q,ElemType e){
    LQNode *p;
    p=(LQNode*)malloc(sizeof(LQNode));
    if(p==NULL) return ERROR;
    p->data=e;p->next=NULL;
    if(Q.front==NULL)   Q.front=p;
    else    Q.rear->next=p;
    Q.rear=p;
    return OK;
}

//链队列的出队
Status DeQueue_LQ(LQueue &Q,ElemType &e){
    LQNode *p;
    if(Q.front==NULL)   return ERROR;
    p=Q.front;
    e=p->data;
    Q.front=Q.front->next;
    if (p==Q.rear)  Q.rear=NULL;
    free(p);
    return OK;
}

//线性表的链式表示

//----单链表
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

//初始化单链表
Status InitList_L(LinkList &L){
    if((L=(LinkList) malloc(sizeof(LNode)))==NULL)  return OVERFLOW;
    L->next=NULL;
    return OK;
}

//单链表查找元素
LNode* Search(LinkList L,ElemType e){
    LNode *p;
    if(L==NULL) return NULL;
    p=L->next;
    while(p!=NULL && p->data!=e)
        p=p->next;
    return p;
}

//求直接后继
LNode* NextElem_L(LNode *p){
    if(p==NULL) return NULL;
    return p->next;
}

//构造节点
LNode* MakeNode_L(ElemType e){
    LNode *p;
    p=(LNode*)malloc(sizeof(LNode));
    if(p!=NULL){
        p->data=e;
        p->next=NULL;
    }
    return p;
}

//在p后插入q节点
Status InsertAfter_L(LNode *p,LNode *q){
    if(p==NULL || q==NULL)  return ERROR;
    q->next=p->next;
    p->next=q;
    return OK;
}
//在p后插入一个新节点可以调用    InsertAfter_L(p,MakeNode_L(e));

//单链表的删除
Status DeleteAfter_L(LNode *p,ElemType &e){
    LNode *q;
    if(p==NULL || p->next==NULL)    return ERROR;
    q=p->next;
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}

//建立单链表
Status CreateList_L(LinkList &L,int n,ElemType *A){
    LNode *p,*q;
    int i;
    if(InitList_L(L)==0) return OVERFLOW;
    p=L;
    for(i=0;i<n;i++){
        q= MakeNode_L(A[i]);
        InsertAfter_L(p,q);
        p=q;
    }
    return OK;
}

//单链表的逆置
void InverseList(LinkList &L){
    LNode *p,*q;
    if(L->next==NULL || L->next->next==NULL)    return;
    p=L->next;
    L->next=NULL;
    while(p!=NULL){
        q=p->next;  //插入时p的next指针会被修改，所以需要在151提前获取p->next
        InsertAfter_L(L,p);
        p=q;
    }
}