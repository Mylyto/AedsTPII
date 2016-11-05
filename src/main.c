#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int main(){
    srand(time(NULL));
    int num = 5;
    Generator g;
    initGenerator(&g,num);
    return 0;
}
