DEF

def HelloWorld(a) {
	a
	++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
}

def clear(a) {
	a =0
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

def isZero(s, d, t) {
	clear(d)
	clear(t)
	copy(s, d, t)
	s [ d + s - ]
	move(t, s)
}

def isEqual(a, b, t1, t2, t) {
	clear(t1)
	clear(t2)
	copy(a, t1, t)
	clear(t)
	copy(b, t2, t)
	t1 [ t2 - t1 - ]

	t =1
	t2 [ t =0 ]
}

def NOT(a,t) {
	t =1
	a [ t =0 ]
}

def AND(a, b, t) {
	t =0
	a [ b [ t=1 $0 ] $0 ]
}

def OR(a, b, t) {
	t =0
	a [ t=1 $0 ]
	b [ t=1 $0 ]
}

def If(a) {
	a [ 
}

def endIf(a) {
	$0 ]
}

def to(a) {
	a
}

def printf(a) {
}

END

MAIN
$100 =44
$101 =46
$102 =62
$103 =60
$104 =43
$105 =25
$2 =1
$1 =1
[
$1 ,

	isEqual(1, 100, 200, 201, 300)
	If(300)
		copy(1000, 2000, 1)
		$1000 [ > $1000 - ]
		,
		copy(2000, 1000, 1)
	endIf(1)

	isEqual(1, 101, 200, 201, 300)
	If(300)
		copy(1000, 2000, 1)
		printf(1000)
		$1000 [ > $1000 - ]
		.
		copy(2000, 1000, 1)
	endIf(1)

	isEqual(1, 102, 200, 201, 300)
	If(300)
		$1000
		+
	endIf(1)

	isEqual(1, 103, 200, 201, 300)
	If(300)
		$1000
		-
	endIf(1)

	isEqual(1, 104, 200, 201, 300)
	If(300)
		copy(1000, 2000, 1)
		$1000 [ > $1000 - ]
		+
		copy(2000, 1000, 1)
	endIf(1)

	isEqual(1, 105, 200, 201, 300)
	If(300)
		copy(1000, 2000, 1)
		$1000 [ > $1000 - ]
		-
		copy(2000, 1000, 1)
	endIf(1)

	$2
]