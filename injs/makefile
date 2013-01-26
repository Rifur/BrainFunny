test:
	nodejs main.js ../example/Hello.bf > Hello.c
	gcc Hello.c -o Hello

maze:
	nodejs main.js ../example/maze.bf > maze.c
	gcc maze.c -o maze

maze2BF:
	nodejs mainBFextToBF.js ../example/Hello.bf > Hello.c
	nodejs mainBFextToBF.js ../example/maze.bf > maze.c
	gcc -E -P Hello.c -o Hello.txt
	gcc -E -P maze.c -o maze.txt
	nodejs main.js maze.txt > maze.c
	nodejs main.js Hello.txt > Hello.c
	gcc Hello.c -o Hello
	gcc maze.c -o maze

interpreter:
	nodejs main.js ../example/interpreter.bf > interpreter.c
	gcc interpreter.c -o interpreter

clean-windows:
	del maze.exe maze.c

clean:
	rm -rf interpreter Hello maze *.txt *.out Hello.c maze.c interpreter.c