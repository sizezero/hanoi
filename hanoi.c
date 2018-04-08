
/* let's write this in a functional way with global variables and naked functions */

usage() {
    printf("usage\n");
    printf("\thanoi <num disks>\n");
    printf("\t<num disks must be an integer value\n");
    exit(1);
}

/* the number of disks */
int N;
/*
Three stacks with a maximum depth of 10.
Lower indicies represent the top of the stack.
Higher indices represent the bottom of the stack.
0 for the element represents an empty value
a positive integer element represents a disk of the specified size

We should define 10 as a constant but preprocessing is
problematic in the compiler I'm using.
*/
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

/* print character c, n times */
nChars(c, n)
char c;
int n; {
    int i;
    for (i=0 ; i<n ; ++i)
        putchar(c);
}

/*
Prints a single disk with a fixed width.
if v is:
positive: print the disk of the given size
zero    : print the empty space
negative: print the stack tray with label -v
*/
printDisk(v)
int v; {

    /*
      N==4
      0  '         '
      1  '    *    '
      2  '   ***   '
      3  '  *****  '
      4  ' ******* '
      -1 ' [  1  ] '
      Whitespace amount is: N+1-v
      Star amount is: 1+(v-1)*2
     */

    int w,s,i;

    if (v<0) {
        putchar('[');
        nChars(' ', N-1);
        putchar(-v + '0');
        nChars(' ', N-1);
        putchar(']');
    } else if (v==0) {
        nChars(' ', 2*N+1);
    } else {
        w = N+1-v;
        s = 1+(v-1)*2;
        nChars(' ', w);
        nChars('*', s);
        nChars(' ', w);
    }
}

/* print all stacks with a labeled tray at the bottom */
printStacks() {
    int i,j;

    for (j=0 ; j<N ; ++j) {
        for (i=0 ; i<3 ; ++i)
            printDisk(stacks[i][j]);
        putchar('\n');
    }
    for (i = -1 ; i >= -3 ; --i)
        printDisk(i);
    putchar('\n');
}

/*
prints a description of the  move from one state to another
as well as the resulting stacks
*/
printMove(src, dst)
int src;
int dst; {
    printf("\n%d --> %d\n\n", src+1, dst+1);
    printStacks();
}

/*
returns the index of the top disk from the given stack
returns -1 if the stack is empty
 */
int top(i)
int i; {
    int j;
    for (j=0 ; j<10 ; ++j)
        if (stacks[i][j] != 0) return j;
    return -1;
}

/*
Move disks from src stack to dst stack
using tmp stack as an intermediate.
"count" number of disks are moved from
the top of the src stack.
 */
move(src, dst, tmp, count)
int src;
int dst;
int tmp;
int count; {
    int i, j;
    if (count == 1) {
        i = top(src);
        j = top(dst);
        /* we have to put the disk on top of the destination disks */
        if (j == -1)
            j = N-1;
        else
            --j;
        stacks[dst][j] = stacks[src][i];
        stacks[src][i] = 0;
        printMove(src, dst);
    } else {
        /* move all but the bottom disks to the temp stack */
        move(src, tmp, dst, count-1);
        /* move the last/bottom source disk to the destination */
        move(src, dst, tmp, 1);
        /* move the disks from the temp stack to the destination */
        move(tmp, dst, src, count-1);
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
    /*
     source spindle == 0
     destination spindle == 2
     temp spindle == 1
     count == N
    */
    move(0, 2, 1, N);
}
