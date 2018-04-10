
# Software

## Non-root User

I did some work for a while as `root` and ran into various file corruptions and hangs. While I'm not sure what the root cause of these problems was (yuk) I decided it would be a good idea to reduce my privileges a bit.

<pre>
$ <b>pdp11</b>

PDP-11 simulator V3.8-1
Disabling XQ
@<b>unix</b>

;login: <b>root</b>
# <b>cat /etc/passwd</b>
root::0:1::/:
daemon::1:1::/bin:
bin::3:1::/bin:
# <b>ed /etc/passwd</b>
49
<b>a
robert::7:3::/robert:
.
w</b>
71
<b>q</b>
# <b>mkdir robert</b>
# <b>chown robert robert</b>
# <b>^D</b>
;login: <b>robert</b>
% <b>pwd</b>
../robert
% <b>cat >/bin/blah</b>
/bin/blah: cannot create
% <b>^D</b>
;login: <b>^E</b>
Simulation stopped, PC: 001726 (MOV (SP)+,177776)
sim> <b>exit</b>
Goodbye
$ 
</pre>

## Editors

I guess the only editor you can count on is [ed](https://en.wikipedia.org/wiki/Ed_(text_editor))

I'm finding the old version of ed is even more primitive than the modern GNU one.

* Range parameters must be fully specified e.g. `1,5l` not `1,l.` You actually need to be aware of how many lines are currently in the file.
* Many commands are missing including `P`
* I don't see a manual for this anywhere. The archived PDFs of the online manuals seem to document a newer version with more commands.

## Old C

There are definitely some quirks between [old C and new C](http://ee.hawaii.edu/~tep/EE160/Book/chapapx/node7.html). The most significant differences are:

* Variable declarations must come before all other instructions.
* Variable declarations cannot include assignments.
* Function arguments and types must be on separate lines.
* Only old fashioned comments are allowed.
* Void is not allowed as a function return type.
* Standard includes don't exist. (although `#define` does exist but the terminal has a hard time with non-escaped # characters)
* Heap allocation doesn't exist. No `malloc()`
* The parser is easily confused by ambiguity. Expressions such as `j==-1` are somehow interpreted as an assignment and should instead be written as `j == -1`

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

## Other System Limitations

Filenames are limited to 14 characters. Longer filenames are often silently truncated.

Backspace and delete don't work. However `@` means ignore all previous characters and `#` means ignore the previous character. This means the line `cd@chdir rbo##obert` is interpreted as `chdir robert`

Ideally you should be able to develop a big C file in a modern environment and cut and paste it into an ancient machine's terminal. `gcc` actually compiles primitive C, it just adds lots of warnings. Unfortunately the terminal hangs on pastes that are larger than a couple hundred characters. One way around this is to paste into multiple files and then cat them together.

<pre>
$ <b>cat >p1.c
<i>paste first chunk</i>
^D</b>
$ <b>cat >p2.c
<i>paste second chunk</i>
^D</b>
$ <b>cat >p3.c
<i>paste third chunk</i>
^D</b>
$ <b>cat p?.c > p.c</b>
$ <b>cc p.c</b>
$ <b>./a.out</b>
</pre>

