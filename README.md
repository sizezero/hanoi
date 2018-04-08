
# Primitive Tower's of Hanoi

I stopped by the [living computer museum](http://www.livingcomputers.org/) a couple weekends ago and found some amazing old unixy systems that are older than I am. I want to try to run some non-trivial program on them so I figured I'd code it up first.

I'm going to try a program that solves the towers of hanoi problem in a primitive version of C.

## Emulators

While writing this I figured it would be helpful to actually emulate some old machines to see how old C actually runs on old hardware. I [investigated some emulators](doc/emulators.md)

## Old C

There are definitely some quirks between [old C and new C](http://ee.hawaii.edu/~tep/EE160/Book/chapapx/node7.html). The most significant differences are:

1. Variable declarations must come before all other instructions.
1. Variable declarations cannot include assignments.
1. Function arguments and types must be on separate lines.
1. Only old fashioned comments are allowed.
1. Void is not allowed as a function return type.
1. Standard includes don't exist. (although #define does exist but the terminal has a hard time with non-escaped # characters)
1. Heap allocation (malloc) doesn't exist.
1. The parser is easily confused by ambiguity. Expressions such as j==-1 are somehow interpreted as an assignment and should instead be written as j == -1

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

func2(char* msg, int count) { /* ERROR can't combine names and types in fn parms */
}

func2(msg, count)
char* msg;
int count; {
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

# Other System Limitations

Filenames are limited to 14 characters. Longer filenames are often silently truncated.

Backspace and delete don't work. However @ means ignore all previous characters and # means ignore the previous character. This means the line "cd@chdir rbo##obert" is interpreted as "chdir robert"

## Lessons

After using linux without history I started to make my filenames very short. Now I know where cp, mv, du, etc. came from.

Having to scope all variables at the top of the function means you may have to reuse the variables for different purposes. You might as well call them i, j, k

I am so used to compiler help. In particular no type checking is difficult.