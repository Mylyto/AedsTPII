#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int main(){
    srand(time(NULL));
    Generator g;
    initGenerator(&g);
    return 0;
}
