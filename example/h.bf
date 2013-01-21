DEF

def clear(a) {
	a [-]
}

def move(a, b) {
	a [ b + a - ]
}

def for(a) {
	a [
}

def next(a) {
	a - ]
}

def move2(s, d, t) {
	for(s) d + t + next(s)
}

def copy(s, d, t) {
	move2(s, d, t)
	move(t, s)
}


END

MAIN
++++++++++[>+++++++>++++++++++>+++>+<<<<-]
>++.>+.+++++++..+++.>++.<<+++++++++++++++.
>.+++.------.--------.>+.>.

$0 = 101
$1 = 0
move(0, 1)
$1 .

clear(1)

$0 = 10
move(0, 1)
$1 .

$0 = 72
$1 = 0
$2 = 0
copy(0, 1, 2)
$1 .