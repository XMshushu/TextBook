#include <iostream>
#include "Textbook.h"
#include "Linear.h"
#include "Hash.h"

Status visit(TElemType e){
    printf("%c\n",e);
    return true;
}
int main() {
    long long int s=7653;
    long long int s1=Hash_3(s);
    return 0;
}