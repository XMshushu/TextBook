typedef int KeyType;
typedef int KeysType;

////记录类型
//typedef struct {
//    KeyType key;
//}RecordType,RcdType;
//
////记录的顺序表
//typedef struct {
//    RcdType *rcd;
//    int length;
//    int size;
//}RcdSqList;

//基数排序中的记录类型
typedef struct{
    KeysType *keys;
}KeysRcdType;

//顺序表类型
typedef struct{
    KeysRcdType *rcd;
    int length;
    int size;
    int digitNum;
    int radix;
}KeysSqList;

//直接插入排序
void InsertSort(RcdSqList &L){
    int i,j;
    for(i=1;i<L.length;i++){
        if(L.rcd[i+1].key<L.rcd[i].key){
            L.rcd[0]=L.rcd[i+1];
            j=i+1;
            do{
                --j;
                L.rcd[j+1]=L.rcd[j];
            }while (L.rcd[0].key<L.rcd[j-1].key);
        }
    }
}

//一趟希尔排序
void ShellInsert(RcdSqList &L,int dk){
    int i,j;
    for(i=0;i<L.length-dk;++i)
        if(L.rcd[dk+i].key<L.rcd[i].key){
            j=i+dk;
            L.rcd[0]=L.rcd[i+dk];
            do{
                j-=dk;
                L.rcd[j+dk]=L.rcd[j];
            } while (j-dk>0 && L.rcd[0].key<L.rcd[j-dk].key);
            L.rcd[j]=L.rcd[0];
        }
}
//希尔排序
void ShellSort(RcdSqList &L,int d[],int t){
    for (int k = 0; k < t; ++k)
        ShellInsert(L,d[k]);
}

//一趟基数排序
void RadixPass(KeysRcdType rcd[],KeysRcdType rcd1[],int n,int i,
               int count[],int pos[],int radix){
    int k,j;
    for(k=1;k<=n;++k)   count[rcd[k].keys[i]]++;
    pos[0]=1;
    for(j=1;j<radix;++j)    pos[j]=count[j-1]+pos[j-1];
    for(k=1;k<=n;++k){
        j=rcd[k].keys[i];
        rcd1[pos[j]++]=rcd[k];
    }
}

//计数基数排序
Status RadixSort(KeysSqList &L){
    KeysRcdType *rcd1;
    int i=0,j;
    int *count,*pos;
    count=(int*)malloc(L.radix*sizeof(int));
    pos=(int*)malloc(L.radix*sizeof(int));
    rcd1=(KeysRcdType*)malloc((L.length+1)*sizeof(KeysRcdType));
    if(count==NULL || pos==NULL || rcd1==NULL) return OVERFLOW;
    while (i<L.digitNum){
        for(j=0;j<L.radix;++j)   count[j]==0;
        if(i%2==0)
            RadixPass(L.rcd,rcd1,L.length,i++,count,pos,L.radix);
        else
            RadixPass(rcd1,L.rcd,L.length,i++,count,pos,L.radix);
    }
    if(L.digitNum%2==1)
        for(j=0;j<L.length;++j)
            L.rcd[j]=rcd1[j];
    free(count);free(pos);free(rcd1);
}