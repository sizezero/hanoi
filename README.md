
# Primitive Tower's of Hanoi

I stopped by the living computer museum a couple weekends ago and found some amazing old unixy systems that are older than I am. I want to try to run some non-trivial program on them so I figured I'd code it up first.

I'm going to try a program that solves the towers of hanoi problem in a primitive version of C.

## Emulators

While writing this I figured it would be helpful to actually emulate some old machines to see how old C actually runs on old hardware. I [investigated some emulators](doc/emulators.md)

## Old C

There are definitely some quirks between old and new C. The most significant differences are:

1. variable declarations must come before all other instructions
1. variable declarations cannot include assignments
1. function arguments and types must be on separate lines
1. only old fashioned comments are allowed

```C
func1() {
    int i=1; /* ERROR assignment not allowed in definition */
    i=3;
    int j; /* ERROR all declarations must be together */
    int k;
}

func1() {
    int i, j;
    int k;
    i=3;
}

func2(char* msg) { /* ERROR can't combine names and types in fn parms */
}

func2(msg)
char* msg {
}

// I'm a cutting edge one line comment
/* ERROR need to use old style comments */
```

## Editors

I guess the only editor you can count on is [ed](https://en.wikipedia.org/wiki/Ed_(text_editor))

I'm finding the old version of ed is even more primitive than the modern GNU one.

1. Range parameters must be fully specified e.g. 1,5l not 1,l. You actually need to be aware of how many lines are currently in the file.
1. Many commands are missing including P
1. I don't see a manual for this anywhere. The archived PDFs of the online manuals seem to document a newer version with more commands.