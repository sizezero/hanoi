
#include <stdio.h>
#include <stdlib.h>

/* let's write this in a functional way with global variables and naked functions */

void usage() {
    printf("usage\n");
    printf("\thanoi <num disks>\n");
    printf("\t<num disks must be an integer value\n");
    exit(1);
}

/* the number of disks */
int N;
int **stacks[3];

void init() {
    for (int i=0 ; i<3 ; ++i) {
        stacks[i]=malloc(sizeof(int)*N);
        for (int j=0 ; j<N ; ++j)
            if (i==0)
                //stacks[i][j]=j+1;
            else
                stacks[i][j]=0;
    }
}

void printDisk(int v) {
    
}

void printStacks() {
    for (int j=0 ; j<N ; ++j)
        for (int i=0 ; i<3 ; ++i)
            ;
}

int main(int argc, char* argv[]) {
    if (argc != 2) usage();
    N = atoi(argv[1]);
    if (N == 0) usage();
    
    init();

    printStacks();
}
