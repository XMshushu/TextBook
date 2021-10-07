#include <iostream>
#include "Textbook.h"
#include "Linear.h"
Status visit(TElemType e){
    printf("%c\n",e);
    return true;
}
int main() {
    LQueue l;
    l.rear=l.front=NULL;
    EnQueue_LQ(l,2);
    EnQueue_LQ(l,3);
    return 0;
}