An extension of Brainfuck with small virtual machine

Copyright (c) 2012 Rifur Ni.

[-] Introduction

Brainfuck is a small programming language which just has eight instructions, created in 1993 by Urban Müller.

We write a small virtual machine for brainfuck, and with something new syntax.

[-] Brainfunny's Syntax

There is an extension for brainfuck's syntax, not strictly, may be equivalent to original. Let us call it "Brainfunny":
  $2    moves the data pointer to position three. Equivalently, we can imagine that the position 0 (may -1) are signed a special symbol, may be a star symbol or something you like. We move the data pointer backward until meet the special symbol, then move k steps (if $k) forward.

  +3    equivalent to "+++" in brainfuck.
  -4    equivalent to "----" in brainfuck.
  =5    clean current data cell, and plus m (if =m).

We append some ideas into brainfunny, such as:
  %100  tells to virtual machine, puts program from address 100.
  #100  jumps to address 100.

[-] Process Inside
Starting virtual machine, you can give one or more brainfuck (may brainfunny) source code, like
  ./bfInt A.bf B.bf C.bf
it will generate three process, time sharing, to run those program.

[-] Build
In default, we use clang++ as our compiler, you can use what you want.
  $make
then we will get bfInt, that is our virtual machine (with interpreter)
  ./bfInt A.bf
to run it.


