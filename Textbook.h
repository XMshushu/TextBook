#include <stdarg.h>
#define maxSize 50
#define ERROR false;
#define FALSE false;
#define TRUE true;
#define OK true;
#define OVERFLOW false;
typedef char TElemType;
typedef bool Status;
typedef int KeyType;
typedef struct RcdType{
    KeyType key;
}RecordType,RcdType;
//顺序二叉树
typedef struct{
    TElemType *data;
    int lastIndex;  //储存最后一个元素的索引
}SqBiTree;

typedef struct{
    RcdType *rcd;   //储存空间基址
    int length;     //当前长度
    int size;       //储存容量
}RcdSqList;         //记录的链表
//二叉链表
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lChild;
    struct BiTNode *rChild;
}BiTNode,*BiTree;
typedef BiTree QueueData;
//三叉链表
typedef struct TriTNode{
    TElemType data;
    struct TriTNode *parent,*lChild,*rChild;
}TriTNode,*TriTNodep;

//判断顺序储存的二叉树中序号v是不是序号u的子孙
bool is_descendant(SqBiTree T,int u,int v){
    if(u<1 || u>T.lastIndex || v<1 || v>T.lastIndex || v<=u)
        return false;
    while(v>u){
        v=v/2;
        if(u==v)
            return true;
    }
    return false;
}

//创建二叉树
BiTree makeBiTree(TElemType e, BiTree l, BiTree r){
    BiTree root;
    root=(BiTree)malloc(sizeof(BiTNode));
    if(root==NULL)
        return NULL;
    root->data=e;
    root->lChild=l;
    root->rChild=r;
    return root;
}

//替换左子树
bool replaceLeft(BiTree &root,BiTree &l){
    if(root==NULL)
        return false;
    BiTree temp=root->rChild;
    root->rChild=l;
//    l=temp;
    return true;
}

//中序遍历
bool inOrderTraverse(BiTree r){
    if(r==NULL)
        return false;
    else{
        inOrderTraverse(r->lChild);
        printf("%c",r->data);
        inOrderTraverse(r->rChild);
    }
}

//使用栈实现非递归中序遍历
void inOrderTraverse2(BiTree root){
    BiTree Stack[maxSize];
    int top=-1;
    BiTree r=root;
    while(top!=-1 || r!=NULL){
        while(r!=NULL){
                Stack[++top] = r;
                r= r->lChild;
        }
        if(top!=-1){
            r=Stack[top--];
            printf("%c",r->data);
            r=r->rChild;
        }
    }
}

//三叉链表遍历
bool preOrderTraverse(TriTNodep T){
    TriTNodep p,pr;
    if(T!=NULL){
        p=T;
        while(p!=NULL){
            printf("%c",p->data);
            if(p->lChild!=NULL)
                p=p->lChild;
            else if(p->rChild!=NULL)
                p=p->rChild;
            else{
               do{
                   pr=p;
                   p=p->parent;
                } while(p!=NULL && (p->rChild==pr || NULL==p->rChild));     //pr是表示上一个节点，p为父节点，父节点的有孩子不能等于pr，父节点的有孩子也不能为NULL
               if(p!=NULL) p=p->rChild;
            }
        }
    }
    return true;
}

//层序遍历
typedef struct SqlQueue{
    BiTree data[maxSize]={NULL};
    int front,rear;
}SqlQueue;
//初始化队列
void initSqlQueue(SqlQueue &q){
    q.front=q.rear=0;
}
//判断队空
bool isQueueEmpty(SqlQueue q){
    if(q.rear==q.front)
        return true;
    else
        return false;
}
//进队
bool enQueue(SqlQueue &q,QueueData data){
    if((q.rear+1)%maxSize==q.front)
        return false;
    q.rear=(q.rear+1)%maxSize;
    q.data[q.rear]=data;
    return true;
}
//出队
bool deQueue(SqlQueue &q,QueueData &data){
    if(isQueueEmpty(q))
        return false;
    q.front=(q.front+1)%maxSize;
    data=q.data[q.front];
    return true;
}
void LevelOrderTraverse(BiTree T){
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
    }
}

//求二叉树深度
int BiTreeDepth(BiTree T){
    int leftDepth,rightDepth;
    if(T!=NULL){
        leftDepth=BiTreeDepth(T->lChild);
        rightDepth=BiTreeDepth(T->rChild);
        return 1+(leftDepth>rightDepth?leftDepth:rightDepth);
    }else
        return 0;
}

//二叉树的叶子节点计数
void CountLeaf(BiTree T,int &count){
    if(T!=NULL){
        if(T->lChild==NULL&&T->rChild==NULL) count++;
        CountLeaf(T->lChild,count);
        CountLeaf(T->rChild,count);
    }
}

//先序构造二叉树
BiTree CreateBiTree(char *defBT,int &i){
    BiTree T;
    TElemType e;
    e=defBT[i++];
    if(e=='#') T=NULL;
    else{
        T=makeBiTree(e,NULL,NULL);
        T->lChild=CreateBiTree(defBT,i);
        T->rChild=CreateBiTree(defBT,i);
    }
    return T;
}


//堆
typedef struct{
    RcdType *rcd;   //堆的基址，0号闲置
    int n;
    int size;
    int tag;
    int (*prior)(KeyType,KeyType);  //函数变量，用于关键字优先级比较
}Heap;

//比较值的优先级
int greatPrior(int x,int y){ return (x>=y); };
int lessPrior(int x,int y){ return (x<=y); }

Status swapHeapElem(Heap &H,int i,int j){
    RcdType tmp;
    if(i<=0 || i>H.n || j<=0 || j>H.n) return ERROR;
    tmp=H.rcd[i];H.rcd[i]=H.rcd[j];H.rcd[j]=tmp;
    return OK;
}

//堆的筛选操作，对堆中位置为pos的节点作筛选，将以pos为根的子树调整为子堆
void ShiftDown(Heap &H,int pos){
    int c,rc;
    while(pos<=H.n/2){
        c=pos*2;
        rc=pos*2+1;
        if(rc<H.n && H.prior(H.rcd[rc].key,H.rcd[c].key))
            c=rc;
        if(H.prior(H.rcd[pos].key,H.rcd[c].key)) return;
        swapHeapElem(H,pos,c);
        pos=c;
    }
}

//堆的插入
Status InsertHeap(Heap &H,RcdType e){
    if(H.n>=H.size-1) return ERROR;
    int curr=++H.n;H.rcd[curr]=e;
    while(curr!=1 && H.prior(H.rcd[curr].key,H.rcd[curr/2].key)){
        swapHeapElem(H,curr,curr/2);
        curr=curr/2;
    }
    return OK;
}

//删除堆顶节点
Status RemoveFirstHeap(Heap &H,RcdType &e){
    if(H.n<=0) return ERROR;
    e=H.rcd[1];
    swapHeapElem(H,1,H.n);
    H.n--;
    if(H.n>1) ShiftDown(H,1);
    return OK;
}

//建堆
void MakeHeap(Heap &H,RcdType *E,int n,int size,int tag,int(*prior)(KeyType,KeyType)){
    int i;
    H.rcd=E;H.n=n;H.size=size;H.tag=tag;H.prior=prior;
    for(i=n/2;i>0;i--) ShiftDown(H,i);
}

void HeapSort(RcdSqList &L){
    Heap H;
    RcdType e;
    int i;
    MakeHeap(H,L.rcd,L.length,L.size,1,greatPrior);
    for (i = H.n;  i>0 ; i--) {
        RemoveFirstHeap(H,e);
        printf("%i\n",e.key);
    }
}

//Binary Search Tree二叉查找树

//二叉查找树的二叉链表存储结构定义
typedef struct BSTNode{
    RcdType data;
    BSTNode *lchild,*rchild;
}BSTNode,*BSTree;

//二叉查找树的查找，查找二叉查找树树中值为Key的节点
//存在则返回该节点指针不存在则返回NULL

//二叉查找树的递归实现
BSTree SearchBST(BSTree T,KeyType key){
    if(T==NULL) return NULL;    //查找失败
    if(T->data.key==key) return T;
    else if(T->data.key>key)
        return SearchBST(T->lchild,key);
    return SearchBST(T->rchild,key);
}

//二叉查找树的非递归实现
BSTree SearchBST_I(BSTree T,KeyType key){
    while(T!=NULL){
        if(T->data.key==key) return T;
        else if(T->data.key>key)
            T=T->lchild;
        else
            T=T->rchild;
    }
    return NULL;
}

//二叉查找树的插入
Status InsertBST(BSTree &T,RcdType e){
    if(T==NULL){
        BSTNode* s=(BSTNode*) malloc(sizeof(BSTNode));
        if(s==NULL) return OVERFLOW;
        s->data=e;s->rchild=NULL;s->lchild=NULL;    //写的时候忘记把左右子树设置为NULL导致了错误，需要注意
        T=s;
        return true;
    }
    if(T->data.key>e.key) return InsertBST(T->lchild,e);
    if(T->data.key<e.key) return  InsertBST(T->rchild,e);
    else return FALSE;
}

//二叉查找树的删除
void DeleteNode(BSTree &p);
Status DeleteBST(BSTree &T,KeyType e){
    if(T==NULL) return FALSE;
    if(T->data.key==e){
        DeleteNode(T);
        return TRUE;
    }
    if(T->data.key>e)
        return DeleteBST(T->lchild,e);
    return DeleteBST(T->rchild,e);
}
//删除节点的操作
void DeleteNode(BSTree &p){
    BSTNode *q,*s;
    q=p;
    if(p->rchild==NULL){
        p=p->lchild;
        free(q);
    }else if(p->lchild==NULL){
        p=p->rchild;
        free(q);
    }else{
        s=p->lchild;
        while(s->rchild!=NULL){
            q=s;s=s->rchild;
        }
        p->data=s->data;
        if(q==p)
            p->lchild=s->lchild;
        else
            p->rchild=s->lchild;
        free(s);
    }
}

//二叉查找树的删除
Status InsertBST1(BSTree &T,RcdType e){
    if(T==NULL){
        BSTNode* s=(BSTNode*) malloc(sizeof(BSTNode));
        if(s==NULL) return OVERFLOW;
        s->data=e;s->rchild=NULL;s->lchild=NULL;    //写的时候忘记把左右子树设置为NULL导致了错误，需要注意
        T=s;
        return true;
    }
    if(T->data.key>e.key) return InsertBST(T->lchild,e);
    if(T->data.key<e.key) return InsertBST(T->rchild,e);
    else return FALSE;
}

//删除节点操作
void DeteleNode(BSTree &p){
    BSTNode *q,*s;
    q=p;
    if(p->rchild==NULL){
        p=p->lchild;
        free(q);
    }else if(p->lchild=NULL){
        p=p->rchild;
        free(q);
    }else{
        s=p->lchild;
        while (s->rchild!=NULL){
            q=s;s=s->rchild;
        }
        p->data=s->data;
        if(p=q)
            p->lchild=s->lchild;
        else
            q->rchild=s->lchild;
        free(s);
    }
}

//平衡二叉树
typedef struct BBSTNode{
    RcdType data;
    int bf;                 //平衡因子
    struct BBSTNode *lchild,*rchild;
}*BBSTree;

//面对LL型最小失衡子树，进行的右旋操作
void R_Rotate(BBSTree &p){
    BBSTNode *lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}

//面对RR型最小失衡子树，进行的左旋操作
void L_Rotate(BBSTree &p){
    BBSTNode *rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}

//平衡二叉树的插入（难点）
#define LH 1    //左子树高于右子树
#define EH 0    //左子树等于右子树
#define RH -1   //右子树高于左子树

//左平衡处理
//左旋->右旋->调整根节点,根节点的左孩子,根节点左孩子的右孩子的平衡因子
void LeftBalance(BBSTree &T){
    BBSTree lc,rd;
    lc=T->lchild;
    switch (lc->bf) {
        case LH: T->bf=lc->bf=EH; R_Rotate(T); break;
        case RH:
            rd=lc->rchild;
            switch (rd->bf) {
                case LH: lc->bf=EH; T->bf=RH; break;
                case EH: lc->bf=T->bf=EH; break;    //EH的情况出现在,子树以下的子树经过平衡之后EH的情形,所以需要考虑EH的情况
                case RH: lc->bf=LH; T->bf=EH; break;
            }
        rd->bf=EH;
        L_Rotate(T->lchild);
        R_Rotate(T);
        break;
    }
};

//右平衡处理
//左旋->右旋->调整根节点,根节点的左孩子,根节点左孩子的右孩子的平衡因子
void RightBalance(BBSTree &T){
    BBSTree rc,ld;
    rc=T->rchild;
    switch (rc->bf) {
        case RH: T->bf=rc->bf=EH; L_Rotate(T); break;
        case LH:
            ld=rc->lchild;
            switch (ld->bf) {
                case LH: rc->bf=RH; T->bf=EH; break;
                case EH: rc->bf=T->bf=EH; break;
                case RH: rc->bf=EH; T->bf=LH; break;
            }
            ld->bf=EH;
            R_Rotate(T->rchild);
            L_Rotate(T);
            break;
    }
};

//平衡插入操作(主程序)
Status InsertAVL(BBSTree &T,RcdType e,Status &taller){
    //taller是用来判断平衡树有没有插入成功，插入成功之后需要进行平衡操作。
    if(T==NULL){
        T=(BBSTree)malloc(sizeof(BBSTNode));
        T->data=e;T->rchild=NULL;T->lchild=NULL;T->bf=EH;taller=TRUE;
    }else if(T->data.key==e.key){
        taller=FALSE;
        return FALSE;
    }else if(T->data.key>e.key){
        if(InsertAVL(T->lchild,e,taller)==false) return FALSE;
        if(taller==true){
            switch (T->bf) {
                case LH:LeftBalance(T); taller= false; break;
                case EH:T->bf=LH; taller=TRUE; break;
                case RH:T->bf=EH; taller= FALSE; break;
            }
        }
    }else{
        if(InsertAVL(T->rchild,e,taller)==false) return FALSE;
        if(taller==true){
            switch (T->bf) {
                case RH:RightBalance(T); taller= false; break;
                case EH:T->bf=RH; taller=TRUE; break;
                case LH:T->bf=EH; taller= FALSE; break;
            }
        }
    }
    return TRUE;
}




//树
//双亲表示法
typedef struct PTNode{
    TElemType data;
    int parent;
}PTNode;
typedef struct PTree{
    PTNode *nodes;
    int r,nodeNum;      //r是根位置，nodeNum节点数
}PTree;

//双亲孩子表示法
typedef struct ChildNode{
    int childIndex;
    struct ChildNode *nextChild;
}ChildNode;
typedef struct PCTreeNode{
    TElemType data;
    int parent;
    struct ChildNode *firstChild;
}PCTreeNode;
typedef struct PCTree{
    struct PCTreeNode *nodes;
    int r,nodeNum;
}PCTree;

//孩子兄弟表示法
 typedef struct CSTNode{
     TElemType data;
     struct CSTNode *firstChild,*nextSibling;
 }CSTNode,*CSTree,*CSForest;

// 创建根节点E和N棵子树的树
CSTree MakeTree(TElemType e,int n,...){
    int i;
    CSTree t,p,pi;
    va_list argptr;
    t=(CSTree)malloc(sizeof(CSTree));
    if(t==NULL) return NULL;
    t->data=e;
    t->firstChild=t->nextSibling=NULL;
    if(n<=0)    return t;
    va_start(argptr, n);
    p=va_arg(argptr, CSTree);
    t->firstChild=p;
    pi=p;
    for(i=1;i<n;i++){
        p=va_arg(argptr, CSTree);
        pi->nextSibling=p;
        pi=p;
    }
    va_end(argptr);
    return t;
}

//插入第i棵子树
Status InsertChild(CSTree &T,int i,CSTree c){
    int j;
    CSTree p;
    if(T==NULL || i<1)  return ERROR;
    if(i==1){
        c->nextSibling=T->firstChild;
        T->firstChild=c;
    }else{
        p=T->firstChild;
        for(j=2;p!=NULL && j<i;j++) p=p->nextSibling;
        if(j==i){
            c->nextSibling=p->nextSibling;
            p->nextSibling=c;
        }else
            return ERROR;
    }
    return OK;
}








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
