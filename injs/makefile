test:
	nodejs main.js h.bf > test.c; clang test.c

maze-windows:
	nodejs main.js ../example/maze.bf > maze.c
	gcc maze.c -o maze.exe

maze:
	nodejs main.js ../example/maze.bf > maze.c
	gcc maze.c -o maze

clean-windows:
	del maze.exe *.c