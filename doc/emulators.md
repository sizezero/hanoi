
# Emulators

## Unix First Edition

One of the easier ways to get started is to simply run a docker image that emulates an early unix. This is described in detail in [Run the First Edition of Unix (1972) with Docker.](https://nickjanetakis.com/blog/run-the-first-edition-of-unix-1972-with-docker)

Unfortunately if you try to run the C compiler you get the following errors:

'''
$ docker run --rm -it bahamat/unix-1st-ed

PDP-11 simulator V3.9-0
./simh.cfg> #!tools/pdp11
Unknown command
Disabling CR
Disabling XQ
RF: buffering file in memory
TC: creating new file
TC0: 16b format, buffering file in memory
Listening on port 5555 (socket 7)

:login: root
root
# ls
bin
dev
etc
tmp
# cat >foo.c

include <stdio.h>

main() {
printf("hello\n");
}
# cc foo.c
Can't find /usr/lib/c0
Can't find /usr/lib/c1
I
/tmp/ctm3a?
move failed: foo.o
# ^D
:login: 
Simulation stopped, PC: 007332 (MOV (SP)+,25244)
sim> exit
Goodbye
RF: writing buffer to file
$
```

It seems that not only is /usr/lib/ missing but there aren't any libraries to be found. Trying to install new libraries on this is probably a bigger job than finding a better emulator.

## Other Docker Images

I found another image that claims to [simulate some old v7 unix on a PDP11](https://hub.docker.com/r/jguillaumes/simh-vax/)

```$ docker run --rm -e SIMH_USE_CONTAINER='yes' -it jguillaumes/simh-pdpv7
SIMH_USE_CONTAINER=yes, using container storage
Copying distribution files...
'/image/RP04.000.gz' -> './RP04.000.gz'
'/image/SIMH-COPYRIGHT.txt' -> './SIMH-COPYRIGHT.txt'
'/image/pdp11.ini' -> './pdp11.ini'
Uncompressing OS image file...
All images uncompressed, starting simulator...

PDP-11 simulator V4.0-0 Beta        git commit id: 0da9a49c
Disabling XQ
Logging to file "console.log"
pdp11.ini-7> set remote telnet=2324
Listening on port 2324
pdp11.ini-27> attach dz 2323
Listening on port 2323
================================================================
= Type 'boot' (no quotes) to load the bootloader               =
= Then, answer 'hp(0,0)unix' to the ':' to boot UNIX V7        =
= Press CTRL-D after the "#" prompt to enable multiuser        =
" The initial password for the root account is 'root'          =
================================================================
boot
Boot
: hp(0,0)unix
mem = 175360
# LS
A.OUT
BIN
BOOT
DCUNIX
DEV
ETC
LIB
MYUNIX
OLDUNIX
TMP
UNIX
USR
# LS BIN/CC
BIN/CC
# ^D
# RESTRICTED RIGHTS: USE, DUPLICATION, OR DISCLOSURE
IS SUBJECT TO RESTRICTIONS STATED IN YOUR CONTRACT WITH
WESTERN ELECTRIC COMPANY, INC.
SAT MAY 14 01:25:22 GMT+1:00 2016

login: ^E
Simulation stopped, PC: 002326 (MOV (SP)+,177776)
Goodbye
Log file closed
$ 
```

This has a c compiler that make work but since the terminal is all caps and appears to be incapable of entering symbols such as curly braces, I have no idea how I would be able to program in C on this machine. I bet the problem is somehow reconfiguring the terminal.

## SIMH

Running an emulator isn't that hard. [SIMH](http://simh.trailing-edge.com/) appears to be the king of emulators and is capable of emulating a huge variety of machines.

You can either install the latest ubuntu package

```
$ sudo apt-get install simh
$ pdp11
```

...or if you want a newer version build it straight from github

```
$ git clone https://github.com/simh/simh
$ cd simh
$ make pdp11
$ BIN/pdp11

PDP-11 simulator V4.0-0 Current        git commit id: 81bcd6d3
sim> 
```

Running the simulator isn't enough. You actually have to configure the simulator to emulate a specific type of hardware

## Unix System V Images

A good description of running Unix System v5 can be found in a [Linux Journal article from 2005](http://www.linuxjournal.com/article/8547?page=0,1) This has you download a Unix System v5 image as well as configure the pdp11 emulator for a specific set of hardware. If you enter the [unix-v5](../unix-v5) directory of this project you can start the emulator with the following commands:

Run this once to download and unzip the Unix System v5 image

```./get-image.sh
```

Running the emulator

```$ pdp11

PDP-11 simulator V3.8-1
Disabling XQ
@unix

;login: root
# ls
bin
dev
etc
lib
mnt
tmp
unix
usr
# cat >hello.c
main() {
        printf("hello\n");
}^D
# cc hello.c
# ./a.out
hello
# ^D
;login: ^E
Simulation stopped, PC: 001726 (MOV (SP)+,177776)
sim> exit
Goodbye
$ 
```

There you have it. We wrote and ran a C program on an ancient UNIX!
