#define w 4
//折叠法
int Hash_s(long long int key){
    int i,j=1;
    long long int sum=0,re;
    for (i=0;i<w;++i)   j*=10;
    while(key!=0){
        re=key%j;
        sum+=re;
        key/=j;
    }
    return sum;
}

//平方取中法
int Hash_3(int key){
    long long int temp;
    temp=key*key/100;
    if(temp>=1000) temp-=temp/1000*1000;
    return temp;
}