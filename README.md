
# Primitive Tower's of Hanoi

I stopped by the [living computer museum](http://www.livingcomputers.org/) a couple weekends ago and found some amazing old unixy systems that are older than I am. I want to try to run some non-trivial program on them so I figured I'd code it up first.

I'm going to try a program that solves the [towers of hanoi](https://en.wikipedia.org/wiki/Tower_of_Hanoi) problem in a primitive version of C.

## Hardware

While writing this I figured it would be helpful to actually emulate some old machines to see how old C actually runs on old hardware. I [investigated some hardware emulators](doc/hardware.md)

## Software

[Configuring and developing the software](doc/software.md) was much different than it is today.

## Lessons

After using the command line without command history I started to make my filenames very short. Now I know where `cp`, `mv`, `du`, etc. came from.

Having to scope all variables at the top of the function means you may have to reuse the variables for different purposes. You might as well call them `i`, `j`, `k`. It makes sense that early versions of K+R C manuals consistently used these letters as variable names.

I am so used to compiler help: typing, mismatched arguments, error messages that mean something, correct line numbers, etc.

More than once while editing hit `q` expecting changes to be saved before exiting. They were not. There was no warning.

Source control: I can't believe progress was once made without this tool.

All of these issues make me very gun shy about any changes to the system. I started composing all of my actions before actually entering any of them. I felt like I was chisleling a marble statue. Mistakes are costly. This was a bad thing but it wasn't a 100% bad thing. I think keeping more of this *think before doing* attitude in modern environments would be a good thing.
