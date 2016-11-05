#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int main(){
    int num = 6;
    Generator g;
    initGenerator(&g,num);
    return 0;
}
