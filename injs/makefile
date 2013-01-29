Hello:
	nodejs main.js ../example/Hello.bf > Hello.c
	gcc Hello.c -o Hello

maze:
	nodejs main.js ../example/maze.bf > maze.c
	gcc maze.c -o maze

parse2BF:
	nodejs mainBFextToBF.js ../example/Hello.bf > Hello.c
	gcc -E -P Hello.c -o Hello.txt
	nodejs main.js Hello.txt > Hello.c
	gcc Hello.c -o Hello

	nodejs mainBFextToBF.js ../example/maze.bf > maze.c
	gcc -E -P maze.c -o maze.txt
	nodejs main.js maze.txt > maze.c
	gcc maze.c -o maze

intr:
	nodejs main.js ../example/interpreter.bf > interpreter.c
	gcc interpreter.c -o interpreter

intrII:
	nodejs main.js ../example/interpreterII.bf > interpreterII.c
	gcc interpreterII.c -o interpreterII

clean-windows:
	del maze.exe maze.c

clean:
	rm -rf interpreter Hello maze interpreter interpreterII *.txt *.out Hello.c maze.c interpreter.c interpreterII.c