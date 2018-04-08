
# Emulators

## Unix First Edition

One of the easier ways to get started is to simply run a docker image that emulates an early unix. This is described in detail in [Run the First Edition of Unix (1972) with Docker.](https://nickjanetakis.com/blog/run-the-first-edition-of-unix-1972-with-docker)

Unfortunately if you try to run the C compiler you get the following errors:

<pre>
$ <b>docker run --rm -it bahamat/unix-1st-ed</b>

PDP-11 simulator V3.9-0
./simh.cfg> #!tools/pdp11
Unknown command
Disabling CR
Disabling XQ
RF: buffering file in memory
TC: creating new file
TC0: 16b format, buffering file in memory
Listening on port 5555 (socket 7)

:login: <b>root</b>
root
# ls
bin
dev
etc
tmp
# <b>cat >foo.c
main() {
printf("hello\n");
}
^D</b>
# <b>cc foo.c</b>
Can't find /usr/lib/c0
Can't find /usr/lib/c1
I
/tmp/ctm3a?
move failed: foo.o
# <b>^D</b>
:login: 
Simulation stopped, PC: 007332 (MOV (SP)+,25244)
sim> <b>exit</b>
Goodbye
RF: writing buffer to file
$
</pre>

It seems that not only is `/usr/lib/` missing but there aren't any libraries to be found. Trying to install new libraries on this is probably a bigger job than finding a better emulator.

## Other Docker Images

I found another image that claims to [simulate some old v7 unix on a PDP11](https://hub.docker.com/r/jguillaumes/simh-vax/)

<pre>
$ <b>docker run --rm -e SIMH_USE_CONTAINER='yes' -it jguillaumes/simh-pdpv7</b>
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
<b>boot</b>
Boot
: <b>hp(0,0)unix</b>
mem = 175360
# <b>LS</b>
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
# <b>LS BIN/CC</b>
BIN/CC
# <b>^D</b>
# RESTRICTED RIGHTS: USE, DUPLICATION, OR DISCLOSURE
IS SUBJECT TO RESTRICTIONS STATED IN YOUR CONTRACT WITH
WESTERN ELECTRIC COMPANY, INC.
SAT MAY 14 01:25:22 GMT+1:00 2016

login: <b>^E</b>
Simulation stopped, PC: 002326 (MOV (SP)+,177776)
Goodbye
Log file closed
$ 
</pre>

This has a C compiler that might work but since the terminal is all caps and appears to be incapable of entering symbols such as curly braces, I have no idea how I would be able to program in C on this machine. I bet the problem is somehow reconfiguring the terminal.

## SIMH

Running an emulator isn't that hard. [SIMH](http://simh.trailing-edge.com/) appears to be the king of emulators and is capable of emulating a huge variety of machines.

You can either install the latest ubuntu package

<pre>
$ <b>sudo apt-get install simh</b>
$ <b>pdp11</b>

PDP-11 simulator V3.8-1
sim> <b>exit</b>
Goodbye
$ 
</pre>

...or if you want a newer version build it straight from github

<pre>
$ <b>git clone https://github.com/simh/simh</b>
$ <b>cd simh</b>
$ <b>make pdp11</b>
$ <b>BIN/pdp11</b>

PDP-11 simulator V4.0-0 Current        git commit id: 81bcd6d3
sim> 
</pre>

Running the simulator isn't enough. You actually have to configure the simulator to emulate a specific type of hardware

## Unix System V Images

A good description of running Unix System v5 can be found in a [Linux Journal article from 2005](http://www.linuxjournal.com/article/8547?page=0,1) This has you download a Unix System v5 image as well as configure the pdp11 emulator for a specific set of hardware. If you enter the [unix-v5](../unix-v5) directory of this project you can start the emulator with the following commands:

Run this once to download and unzip the Unix System v5 image

<pre>
$ <b>cd hanoi/unix-v5</b>
$ <b>./get-image.sh</b>
</pre>

Running the emulator

<pre>
$ <b>pdp11</b>

PDP-11 simulator V3.8-1
Disabling XQ
@<b>unix</b>

;login: <b>root</b>
# <b>ls</b>
bin
dev
etc
lib
mnt
tmp
unix
usr
# <b>cat >hello.c
main() {
        printf("hello\n");
}^D</b>
# <b>cc hello.c</b>
# <b>./a.out</b>
hello
# <b>^D</b>
;login: <b>^E</b>
Simulation stopped, PC: 001726 (MOV (SP)+,177776)
sim> <b>exit</b>
Goodbye
$ 
</pre>

There you have it. We wrote and ran a C program on an ancient UNIX! The emulator actually persists the filesystem of multiple runs so be careful you don't screw it up. If you want to reset you can just copy back the original filesystem.

<pre>
$ <b>cp unix_v5_rk.dsk.orig unix_v5_rk.dsk</b>
</pre>

# Non-root User

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
