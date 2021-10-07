#include "Textbook.h"

//图

typedef struct{
    VexType *vexs;      //顶点数组
    int **arc;          //邻接矩阵
    int n,e;            //n顶点数，e边数
    GraphKind kind;     //图的类型
    int *tags;           //标志数组，标记顶点访问与否
}MGraph;

//边/弧的信息
typedef struct{
    VexType v,w;    //边、弧的顶点
    int info;       //带权图的权值
}ArcInfo;

//查找顶点
int LocateVex_M(MGraph G,VexType v){
    int i;
    for (i=0;i<G.n;i++)
        if(v==G.vexs[i])    return i;
    return -1;
}

Status CreateUDG_M(MGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);
Status CreateUDN_M(MGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);
Status CreateDN_M(MGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);
Status CreateDG_M(MGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);

//创建图的邻接数组结构
Status CreateGraph_M(MGraph &G,GraphKind kind,VexType *vexs,int n,ArcInfo *arcs,int e){
    if(n<0 || e<0 || (n>0 && NULL==vexs) || (e>0 && NULL==arcs))
        return ERROR;
    G.kind=kind;
    switch (G.kind){
        case UDG:return CreateUDG_M(G,vexs,n,arcs,e);break;
        case DG:return CreateDG_M(G,vexs,n,arcs,e);break;
        case UDN:return CreateUDN_M(G,vexs,n,arcs,e);break;
        case DN:return CreateDN_M(G,vexs,n,arcs,e);break;
        default:return ERROR;
    }
}

//初始化含n个顶点且无边的图G的邻接数组储存结构
int InitGraph_M(MGraph &G,GraphKind kind,VexType *vexs,int n){
    int i,j,info;
    if(n<0 || (n>0 && vexs==NULL))  return ERROR;
    if(kind==DG || kind==UDG)   info=0;
    else if (kind==DN || kind==UDN) {
        info=INFINITY;
    }
    else return ERROR;
    G.kind=kind;
    if (n==0)   return OK;
    if(NULL==(G.vexs=(VexType*) malloc(n*sizeof(VexType))))  return OVERFLOW;
    for(i=0;i<G.n;i++)  G.vexs[i]=vexs[i];
    if(NULL==(G.arc=(int**) malloc(n*sizeof(int*))))    return OVERFLOW;
    for(i=0;i<G.n;i++)
        if(NULL==(G.arc[i]=(int*) malloc(n*sizeof(int))))
            return OVERFLOW;
    if(NULL==(G.tags=(int*) malloc(n * sizeof(int))))    return OVERFLOW;
    for(i=0;i<G.n;i++){
        G.tags[i] == UNVISITED;
        for(j=0;j<G.n;j++)  G.arc[i][j]=info;
    }
    return OK;
}

//创建无向图的邻接数组存储结构
Status CreateUDG_M(MGraph &G,VexType *vexs,int n,ArcInfo *arcs,int e){
    int i,j,k;
    VexType v,w;
    if(InitGraph_M(G,G.kind,vexs,n)!=true) return ERROR;
    G.e=e;
    for(k=0;k<G.e;k++){
        v=arcs[k].v;
        w=arcs[k].w;
        i= LocateVex_M(G,v);
        j= LocateVex_M(G,w);
        if(i<0 || j<0) return ERROR;
        G.arc[i][j]=G.arc[j][i]=1;
    }
    return OK;
}

//求第一个邻接顶点
int FirstAdjVex_M(MGraph G,int k){
    int i;
    if(k<0 || k>G.n) return -1;
    for(i=0;i<G.n;i++)
        if((G.kind==DG || G.kind==UDG) && G.arc[k][i]!=0) return i;
        else if((G.kind==DN || G.kind==UDN) && G.arc[k][i]!=99999) return i;
    return -1;
}

//求下一个邻接顶点
int NextAdjVex_M(MGraph G,int k,int m){
    int i;
    if(k<0 || k>G.n || m<0 || m>G.n) return -1;
    for(i=m;i<G.n;i++)
        if((G.kind==DG || G.kind==UDG) && G.arc[k][i]!=0) return i;
        else if((G.kind==DN || G.kind==UDN) && G.arc[k][i]!=99999) return i;
        else return -1;
}
//邻接表
typedef struct AdjVexNode{
    int adjvex;
    struct AdjVexNode *nextArc;
    int info;
}AdjVexNode,*AdjVexNodeP;   //邻接链表节点

typedef struct VexNode{
    VexType data;
    struct AdjVexNode *firstArc;
}VexNode;   //邻接数组元素

typedef struct{
    VexNode *vexs;
    int n,e;
    GraphKind kind;
    int *tags;
}ALGraph;   //邻接表的类型

Status CreateUDG_AL(ALGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);
Status CreateUDN_AL(ALGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);
Status CreateDN_AL(ALGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);
Status CreateDG_AL(ALGraph &G,VexType *ves,int n,ArcInfo *arcs,int e);

//查找顶点
int LocateVex_AL(ALGraph G,VexType v){
    int i;
    for (i=0;i<G.n;i++)
        if(v==G.vexs[i].data)    return i;
    return -1;
}

//创建图的邻接表结构
Status CreateGraph_AL(ALGraph &G,GraphKind kind,VexType *vexs,int n,ArcInfo *arcs,int e){
    if(n<0 || e<0 || (n>0 && NULL==vexs) || (e>0 && NULL==arcs))
        return ERROR;
    G.kind=kind;
    switch (G.kind){
        case UDG:return CreateUDG_AL(G,vexs,n,arcs,e);break;
        case DG:return CreateDG_AL(G,vexs,n,arcs,e);break;
        case UDN:return CreateUDN_AL(G,vexs,n,arcs,e);break;
        case DN:return CreateDN_AL(G,vexs,n,arcs,e);break;
        default:return ERROR;
    }
}

//创建有向图的邻接表结构
Status CreateDG_AL(ALGraph &G,VexType *vexs,int n,ArcInfo *arcs,int e){
    int i,j,k;
    VexType v,w;
    AdjVexNodeP p;
    G.n=n;G.e=e;
    G.vexs=(VexNode*) malloc(n*sizeof(VexNode));
    G.tags=(int*) malloc(n*sizeof(int));
    for(i=0;i<G.n;i++){
        G.tags[i]=UNVISITED;
        G.vexs[i].data=vexs[i];
        G.vexs[i].firstArc=NULL;
    }
    for(k=0;k<G.e;k++){
        v=arcs[k].v;w=arcs[k].w;
        i= LocateVex_AL(G,v); j= LocateVex_AL(G,w);
        if(i<0 || j<0) return ERROR;
        p=(AdjVexNodeP) malloc(sizeof(AdjVexNode));
        if(p==NULL) return OVERFLOW;
        p->adjvex=j;
        p->nextArc=G.vexs[i].firstArc;
        G.vexs[i].firstArc=p;
    }
    return OK;
}

//插入弧或边
Status AddArc_AL(ALGraph &G,int k,int m,int info){
    AdjVexNodeP p;
    if(k<0 || k>G.n || m<0 || m>G.n) return ERROR;
    if((G.kind==UDG || G.kind==DG) && info!=1) return ERROR;    //图的类型和权值不匹配
    p=G.vexs[k].firstArc;
    while(p!=NULL){     //判断弧是否存在
        if(m==p->adjvex)  return ERROR;
        p=p->nextArc;
    }
    p=(AdjVexNodeP) malloc(sizeof(AdjVexNode));
    if(p==NULL) return OVERFLOW;
    p->adjvex=m;p->info=info;
    p->nextArc=G.vexs[k].firstArc;
    G.vexs[k].firstArc=p;
    if(G.kind==UDN || G.kind==DN){
        p=(AdjVexNodeP) malloc(sizeof(AdjVexNode));
        if(p==NULL) return OVERFLOW;
        p->adjvex=k;p->info=info;
        p->nextArc=G.vexs[m].firstArc;
        G.vexs[m].firstArc=p;
    }
    G.e++;
    return OK;
}

//求第一个邻接顶点
int FirstAdjVex_AL(ALGraph G,int k,AdjVexNodeP &p){
    if(k<0 || k>G.n) return -1;
    p=G.vexs[k].firstArc;
    if(p!=NULL) return p->adjvex;
    else return -1;
}

//求下一个邻接顶点
int NextAdjVex_AL(ALGraph G,int k,AdjVexNodeP &p){
    if(k<0 || k>G.n) return -1;
    if(p==NULL) return -1;
    p=p->nextArc;
    if(p!=NULL) return p->adjvex;
    else return -1;
}

//求K顶点的所有邻接顶点
Status visitAllAdjVex(ALGraph G,int k,Status (*visit)(int)){
    int i;AdjVexNodeP p=NULL;
    if(k<0 || k>G.n) return ERROR;
    for (i= FirstAdjVex_AL(G,k,p);i>=0;i= NextAdjVex_AL(G,k,p)) {
        if(visit(i)== false) return ERROR;
    }
    return OK;
}

//广度优先遍历
Status BSFTraverse_AL(ALGraph G,Status(*visit)(int)){
    int i,j,k;
    AdjVexNodeP p;
    LQueue Q;InitQueue(Q);
    for(i=0;i<G.n;i++) G.tags[i]=UNVISITED;
    for(i=0;i<G.n;i++)
        if(UNVISITED==G.tags[i]){
            if(visit(i)== false) return ERROR;
            G.tags[i]=VISITED;EnQueue_LQ(Q,i);
            while(DeQueue_LQ(Q,k)==OK){
                for(j= FirstAdjVex_AL(G,k,p);j>0;j= NextAdjVex_AL(G,k,p)){
                    if(G.tags[j]==UNVISITED){
                        if(visit(j)== false) return ERROR;
                        G.tags[j]=VISITED;EnQueue_LQ(Q,j);
                    }
                }
            }
        }
}

//连通图的深度优先遍历
Status DFS_M(MGraph G,int k,Status(*visit)(int)){
    int i;
    if(ERROR==visit(k)) return ERROR;
    G.tags[k]=VISITED;
    for(i= FirstAdjVex_M(G,k);i>0;i=NextAdjVex_M(G,k,i)){
        if(UNVISITED==G.tags[i])
            if(false==DFS_M(G,i,visit)) return ERROR;
    }
    return OK;
}

//图的深度优先遍历
Status DFSTraverse_M(MGraph G,Status(*visit)(int)){
    int i;
    for(i=0;i<G.n;i++)  G.tags[i]=UNVISITED;
    for(i=0;i<G.n;i++)
        if(UNVISITED==G.tags[i])
            if(false==DFS_M(G,i,visit)) return ERROR;
    return OK;
}

//遍历的应用
//判断图中是否有从s到t的路径
Status isReachable_DFS(MGraph G,int s,int t){
    int i;
    Status found=FALSE;
    G.tags[s]=VISITED;
    if(s==t) return TRUE;
    for(i= FirstAdjVex_M(G,s);i>=0;i= NextAdjVex_M(G,s,i)){
        if(G.tags[i]==UNVISITED)
            found=isReachable_DFS(G,i,t);
    }
    return found;
}

void ShortestPathLength_BFS(ALGraph G,int s,int *D){
    int i,j;
    AdjVexNodeP p;
    LQueue Q;InitQueue_LQ(Q);
    for(i=0;i<G.n;i++) G.tags[i]=INFINITY;
    D[s]=0;
    G.tags[s]=VISITED;EnQueue_LQ(Q,s);
    while (true==DeQueue(Q,i)){
        for(j= FirstAdjVex_AL(G,i,p);j>=0;j= NextAdjVex_AL(G,i,p))
            if(UNVISITED==G.tags[j]){
                D[j]=D[i]+1;
                G.tags[j]=VISITED;
                EnQueue(Q,j);
            }
    }
}

