#include <stdio.h>
#include <stdlib.h>
#define __def void
int *code, *p;
#define zero(argc, z) \
p=z;
#define While(argc, t) \
p=t;while(*p){
#define endWhile(argc, t) \
p=t;}
#define If(argc, t) \
p=t;while(*p){
#define endIf(argc, z) \
zero(1,z);}
#define Clean(argc, a) \
p=a;while(*p){--*p;}
#define Copy_withoutClean(argc, s, d, t) \
p=s;while(*p){p=d;++*p;p=t;++*p;p=s;--*p;}p=t;while(*p){p=s;++*p;p=t;--*p;}
#define Copy(argc, s, d, t) \
p=d;while(*p){--*p;}p=t;while(*p){--*p;}Copy_withoutClean(3,s,d,t);
#define Minus_withoutClean(argc, s, d, t) \
p=s;while(*p){p=d;--*p;p=t;++*p;p=s;--*p;}p=t;while(*p){p=s;++*p;p=t;--*p;}
#define IsGreater(argc, a, b, t1, t2, f) \
Copy(3,a,t1,t2);Copy(3,b,t2,f);While(1,t1);p=f;++*p;p=t1;--*p;p=t2;while(*p){--*p;Clean(1,f);zero(1, &code[0]);}endWhile(1,t1);
#define IsSmaller(argc, a, b, t1, t2, f) \
Copy(3,a,t1,t2);Copy(3,b,t2,f);While(1,t2);p=f;++*p;p=t2;--*p;p=t1;while(*p){--*p;Clean(1,f);zero(1, &code[0]);}endWhile(1,t2);
#define IsEqual(argc, a, b, t1, t2, f) \
Copy(3,a,t1,f);Copy(3,b,t2,f);Clean(1,f);While(1,t1);p=f;++*p;p=b;while(*p){p=f;--*p;zero(1, &code[0]);}endWhile(1,t1);p=f;while(*p){p=f;while(*p){--*p;}}
#define NOT(argc, a, f) \
p=f;while(*p){--*p;}++*p;p=a;while(*p){Clean(1,f);zero(1, &code[0]);}
#define IsNotSmaller(argc, a, b, t1, t2, f) \
IsSmaller(5,a,b,t1,t2,f);Clean(1,t1);p=f;while(*p){p=t1;++*p;p=f;--*p;}NOT(2,t1,f);
#define IsNotEqual(argc, a, b, t1, t2, f) \
IsEqual(5,a,b,t1,t2,f);Clean(1,t1);p=f;while(*p){p=t1;++*p;p=f;--*p;}NOT(2,t1,f);
#define Add(argc, a, b, c, t) \
Clean(1,c);Clean(1,t);Copy_withoutClean(3,a,c,t);Clean(1,t);Copy_withoutClean(3,b,c,t);
#define Sub(argc, a, b, c, t) \
p=t;while(*p){--*p;}Copy_withoutClean(3,a,c,t);Minus_withoutClean(3,b,c,t);
#define Mul(argc, a, b, c, ta, t) \
Clean(1,c);Copy(3,a,ta,t);While(1,ta);p=ta;--*p;Copy(3,b,c,t);endWhile(1,ta);
#define Div(argc, a, b, c, r, t1, t2, t3) \
p=c;while(*p){--*p;}p=r;while(*p){--*p;}p=t1;while(*p){--*p;}p=t2;while(*p){--*p;}p=t3;while(*p){--*p;}Copy(3,b,r,t2);If(1,b);IsNotSmaller(5,r,a,t1,t2,t3);While(1,t3);Sub(4,r,a,t2,t3);Clean(1,t3);Copy(3,t2,r,t3);p=c;++*p;IsNotSmaller(5,r,a,t1,t2,t3);endWhile(1,t3);endIf(1, &code[0]);
#define Xor(argc, a, b, c, ta, tb, t, ac, bc, ar, br, t1, t2, t3) \
Copy(3,a,ta,t);Copy(3,b,tb,t);p=t;*p=2;p=ta;while(*p){p=tb;while(*p){Div(7,t,ta,ac,ar,t1,t2,t3);Copy(3,ac,ta,t2);Div(7,t,tb,bc,br,t1,t2,t3);Copy(3,bc,tb,t2);Mul(5,t,c,t1,t2,t3);Copy(3,t1,c,t2);IsNotEqual(5,ar,br,t1,t2,t3);p=t3;while(*p){p=c;++*p;zero(1, &code[0]);}p=tb;}p=ta;}
#define RandomLCG(argc, prex, m, a, c, tx, t1, t2, t3, t4) \
p=tx;while(*p){--*p;}p=t1;while(*p){--*p;}p=t2;while(*p){--*p;}p=t3;while(*p){--*p;}p=t4;while(*p){--*p;}Mul(5,a,prex,t1,t2,t3);Add(4,t1,c,t2,t3);Copy(3,t2,prex,t3);Div(7,m,prex,t1,tx,t2,t3,t4);

int main(void) { code = (int *)calloc(10000, 4); p = &code[0];p=&code[0];while(*p){--*p;}p=&code[1];while(*p){--*p;}++*p;p=&code[100];*p=256;p=&code[101];*p=65;p=&code[102];*p=27;p=&code[103];*p=1;p=&code[201];*p=0;p=&code[202];*p=0;p=&code[203];*p=0;p=&code[204];*p=0;RandomLCG(9, &code[103], &code[100], &code[101], &code[102], &code[103], &code[201], &code[202], &code[203], &code[204]);Copy(3, &code[201], &code[103], &code[204]);RandomLCG(9, &code[103], &code[100], &code[101], &code[102], &code[103], &code[201], &code[202], &code[203], &code[204]);Copy(3, &code[201], &code[103], &code[204]);Div(7, &code[101], &code[100], &code[201], &code[202], &code[203], &code[204], &code[205]);p=&code[201];printf("%d\n",*p);return 0; }
