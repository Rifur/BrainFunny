test:
	nodejs main.js ../example/Hello.bf > Hello.c
	gcc Hello.c -o Hello

maze:
	nodejs main.js ../example/maze.bf > maze.c
	gcc maze.c -o maze

clean-windows:
	del maze.exe maze.c
