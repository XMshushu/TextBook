typedef int KeyType;

//记录类型
typedef struct {
    KeyType key;
}RecordType,RcdType;

//记录的顺序表
typedef struct {
    RcdType *rcd;
    int length;
    int size;
}RcdSqList;


//直接插入排序
void InsertSort(RcdSqList &L){
    int i,int j;
    for(i=1;i<L.length;i++){
        if(L.rcd[i+1].key<L.rcd[i].key){
            L.rcd[0]=L.rcd[i+1];
            j=i+1;
            do{
                --j;
                L.rcd[j+1]=L.rcd[j];
            }while (L.rcd[0].key<L.rcd[j-1].key)
        }
    }
}