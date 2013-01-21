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
		f+ b[f- zero(0)]
	endWhile(t1)
	f [ f[-] ]
}

def NOT(a, f) {
	f [-] + a [ Clean(f) zero(0) ]
}

def IsNotSmaller(a, b, t1, t2, f) {
	IsSmaller(a, b, t1, t2, f)
	Clean(t1)  f [ t1+ f- ]
	NOT(t1, f)
}


def IsNotEqual(a, b, t1, t2, f) {
	IsEqual(a, b, t1, t2, f)
	Clean(t1)  f [ t1+ f- ]
	NOT(t1, f)
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
		Copy(b, c, t)
	endWhile(ta)
}

def Div(a, b, c, r, t1, t2, t3) {
	c[-] r[-] t1[-] t2[-] t3[-]
	Copy(b, r, t2)

	If(b)
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
	tx[-]t1[-]t2[-]t3[-]t4[-]
	Mul(a, prex, t1, t2, t3)
	Add(t1, c, t2, t3)
	Copy(t2, prex, t3)
	Div(m, prex, t1, tx, t2, t3, t4)
}

END
MAIN

$0 [-]
$1 [-]+
$100 =256
$101 =65
$102 =27
$103 =1
$201 =0
$202 =0
$203 =0
$204 =0

RandomLCG(103, 100, 101, 102, 103, 201, 202, 203, 204)
Copy(201, 103, 204)
RandomLCG(103, 100, 101, 102, 103, 201, 202, 203, 204)
Copy(201, 103, 204)

Div(101, 100, 201, 202, 203, 204, 205)
$201 .