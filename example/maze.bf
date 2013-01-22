DEF

def zero(z) { 
	z
}

def While(t) {
	t [
}

def endWhile(t) {
	t ]
}

def If(t) {
	t [
}

def endIf(z) {
	zero(z) ]
}


def Clean(a) {
	a [-]
}

def Copy_withoutClean(s, d, t) {
	s [ d+ t+ s- ]
	t [ s+ t- ]
}

def Copy(s, d, t) {
	d [-] t [-] Copy_withoutClean(s, d, t)
}

def Minus_withoutClean(s, d, t) {
	s [ d- t+ s- ]
	t [ s+ t- ]
}

def AND(a, b, f) {
	Clean(f) a[ b [ f+ zero(0) ] zero(0)]
}

def OR(a, b, f) {
	Clean(f) 
	a [ f+ zero(0) ]
	b [ f+ zero(0) ]
}

def NOT(a, f) {
	f [-]+ a [ Clean(f) zero(0) ]
}

def IsGreater(a, b, t1, t2, f) {
	Copy(a, t1, t2)
	Copy(b, t2, f)

	While(t1)
		f+ t1- t2 [- Clean(f) zero(0) ]
	endWhile(t1)
}

def IsSmaller(a, b, t1, t2, f) {
	Copy(a, t1, t2)
	Copy(b, t2, f)

	While(t2)
		f+ t2- t1 [- Clean(f) zero(0) ]
	endWhile(t2)
}

def IsEqual(a, b, t1, t2, f) {
	Copy(a, t1, f)
	Copy(b, t2, f)
	Clean(f)
	While(t1)
		f+ t1- t2 [- f- zero(0)]
	endWhile(t1)

	While(t2)
		f+ t2- t1 [- f- zero(0)]
	endWhile(t2)	
	NOT(f, t1)
	Clean(f) t1 [ f+ t1- ]
}



def IsNotSmaller(a, b, t1, t2, f) {
	IsSmaller(a, b, t1, t2, f)
	Clean(t1)  f [ t1+ f- ]
	NOT(t1, f)
}


def IsNotEqual(a, b, t1, t2, f) {
	IsEqual(a, b, t1, t2, f)
	NOT(f, t1)
	f[-] t1 [ f+ zero(0) ]
}

def Add(a, b, c, t) {
	Clean(c)
	Clean(t)
	Copy_withoutClean(a, c, t)
	Clean(t)
	Copy_withoutClean(b, c, t)
}

def Sub(a, b, c, t) {
	t [-]
	Copy_withoutClean(a, c, t)
	Minus_withoutClean(b, c, t)
}

def Mul(a, b, c, ta, t) {
	Clean(c)
	Copy(a, ta, t)

	While(ta)
		ta - 
		Copy_withoutClean(b, c, t)
	endWhile(ta)
}



def Div(a, b, c, r, t1, t2, t3) {
	c[-] r[-] t1[-] t2[-] t3[-]
	Copy(b, r, t2)

	If(a)
		IsNotSmaller(r, a, t1, t2, t3)
		While(t3)
			Sub(r, a, t2, t3)
			Clean(t3)
			Copy(t2, r, t3)
			c+
			IsNotSmaller(r, a, t1, t2, t3)
		endWhile(t3)
	endIf(0)
}

def Xor(a, b, c, ta, tb, t, ac, bc, ar, br, t1, t2, t3) {
	Copy(a, ta, t)
	Copy(b, tb, t)
	t =2
	ta [ tb [
		Div(t, ta, ac, ar, t1, t2, t3)
		Copy(ac, ta, t2)
		Div(t, tb, bc, br, t1, t2, t3)
		Copy(bc, tb, t2)
		Mul(t, c, t1, t2, t3)
		Copy(t1, c, t2)

		IsNotEqual(ar, br, t1, t2, t3)
		t3 [ c+ zero(0) ]
	tb] ta ]
}

def RandomLCG(prex, m, a, c, tx, t1, t2, t3, t4) {
	tx[-] t1[-] t2[-] t3[-] t4[-]
	Mul(a, prex, t1, t2, t3)
	Add(t1, c, t2, t3)
	Copy(t2, prex, t3)
	Div(m, prex, t1, tx, t2, t3, t4)
	Copy(tx, prex, t1)
}

def testMul(a,b,c,d,e,f,g) {

	a =0
	b =0
	Mul(a, b, c, d, e)
	d =0
	IsNotEqual(c, d, e, f, g)
	If(g)
		a. b. c. d.
	endIf(0)

	a =1
	b =1
	Mul(a, b, c, d, e)
	d =1
	IsNotEqual(c, d, e, f, g)
	If(g)
		a. b. c. d.
	endIf(0)

	a =5
	b =3
	Mul(a, b, c, d, e)
	d =15
	IsNotEqual(c, d, e, f, g)
	If(g)
		a. b. c. d.
	endIf(0)

	a =8
	b =7
	Mul(a, b, c, d, e)
	d =56
	IsNotEqual(c, d, e, f, g)
	If(g)
		a. b. c. d.
	endIf(0)

}

def testDiv(a,b,c,d,e,f,g,h,i) {

	a =0
	b =0
	Div(a, b, c, d, e, h, i)
	i =0
	IsNotEqual(c, i, e, f, g)
	i =0
	IsNotEqual(d, i, e, f, h)
	OR(g, h, i)
	If(i)
		a. b. c. d.
	endIf(0)

	a =1
	b =0
	Div(a, b, c, d, e, h, i)
	i =0
	IsNotEqual(c, i, e, f, g)
	i =0
	IsNotEqual(d, i, e, f, h)
	OR(g, h, i)
	If(i)
		a. b. c. d.
	endIf(0)

	a =3
	b =8
	Div(a, b, c, d, e, h, i)
	i =2
	IsNotEqual(c, i, e, f, g)
	i =2
	IsNotEqual(d, i, e, f, h)
	OR(g, h, i)
	If(i)
		a. b. c. d.
	endIf(0)

	a =11
	b =17
	Div(a, b, c, d, e, h, i)
	i =1
	IsNotEqual(c, i, e, f, g)
	i =6
	IsNotEqual(d, i, e, f, h)
	OR(g, h, i)
	If(i)
		a. b. c. d.
	endIf(0)

	a =17
	b =11
	Div(a, b, c, d, e, h, i)
	i =0
	IsNotEqual(c, i, e, f, g)
	i =11
	IsNotEqual(d, i, e, f, h)
	OR(g, h, i)
	If(i)
		a. b. c. d.
	endIf(0)

}

def Random(y) {
	$1000 =997
	$1001 =65
	$1002 =7

	Copy(y, 1003, 1008)

	RandomLCG(1003, 1000, 1001, 1002, 1004, 1005, 1006, 1007, 1008)
	Copy(1003, y, 1008)
}

def RandToBin(y, b) {
	Random(y)
	$1002 =2
	Div(1002, y, 1001, 1003, 1004, 1005, 1006)
	
	Clean(b)
	$1003 [ b+ zero(0) ]
}

END
MAIN

$0 [-]
$1 [-]+

$100 +
$200=9585

$1 [ RandToBin(100, 101) Add(200, 101, 102, 103) $102 .  $1 ]


