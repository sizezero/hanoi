
/* let's write this in a functional way with global variables and naked functions */

usage() {
    printf("usage\n");
    printf("\thanoi <num disks>\n");
    printf("\t<num disks must be an integer value\n");
    exit(1);
}

/* the number of disks */
int N;
int stacks[3][10];

init() {
    int i,j;
    for (i=0 ; i<3 ; ++i) {
        for (j=0 ; j<N ; ++j)
            if (i==0)
                stacks[i][j]=j+1;
            else
                stacks[i][j]=0;
    }
}

/*
N==4
1 '    *    '
2 '   ***   '
3 '  *****  '
4 ' ******* '
Whitespace amount is: N+1-v
Star amount is: 1+(v-1)*2
*/
printDisk(v)
int v; {
    int w,s,i;
    if (v==0) {
        for (i=0 ; i<N ; ++i)
            putchar(' ');
        putchar('I');
        for (i=0 ; i<N ; ++i)
            putchar(' ');
    } else {
        w = N+1-v;
        s = 1+(v-1)*2;
        for (i=0 ; i<w ; ++i)
            putchar(' ');
        for (i=0 ; i<s ; ++i)
            putchar('*');
        for (i=0 ; i<w ; ++i)
            putchar(' ');
    }
}

printStacks() {
    int i,j;
    for (j=0 ; j<N ; ++j) {
        for (i=0 ; i<3 ; ++i)
            printDisk(stacks[i][j]);
        putchar('\n');
    }
}

main(argc, argv)
int argc;
char* argv[]; {
    if (argc != 2) usage();
    /* couldn't get atoi to work */
    N = *argv[1] - '0';
    if (N <= 0 || N > 10) usage();
    
    init();

    printStacks();
}
