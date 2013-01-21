#include <stdio.h>
#include <stdlib.h>
#define __def void
int *code, *p;
#define HelloWorld(argc, a) \
p=a;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;while(*p){++p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++p;++*p;++*p;++*p;++p;++*p;--p;--p;--p;--p;--*p;}++p;++*p;++*p;putchar(*p);++p;++*p;putchar(*p);++*p;++*p;++*p;++*p;++*p;++*p;++*p;putchar(*p);putchar(*p);++*p;++*p;++*p;putchar(*p);++p;++*p;++*p;putchar(*p);--p;--p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;putchar(*p);++p;putchar(*p);++*p;++*p;++*p;putchar(*p);--*p;--*p;--*p;--*p;--*p;--*p;putchar(*p);--*p;--*p;--*p;--*p;--*p;--*p;--*p;--*p;putchar(*p);++p;++*p;putchar(*p);++p;putchar(*p);
#define clear(argc, a) \
p=a;*p=0;
#define move(argc, a, b) \
p=a;while(*p){p=b;++*p;p=a;--*p;}
#define for(argc, a) \
p=a;while(*p){
#define next(argc, a) \
p=a;--*p;}
#define move2(argc, s, d, t) \
for(1,s);p=d;++*p;p=t;++*p;next(1,s);
#define copy(argc, s, d, t) \
move2(3,s,d,t);move(2,t,s);
#define isZero(argc, s, d, t) \
clear(1,d);clear(1,t);copy(3,s,d,t);p=s;while(*p){p=d;++*p;p=s;--*p;}move(2,t,s);
#define isEqual(argc, a, b, t1, t2, t) \
clear(1,t1);clear(1,t2);copy(3,a,t1,t);clear(1,t);copy(3,b,t2,t);p=t1;while(*p){p=t2;--*p;p=t1;--*p;}p=t;*p=1;p=t2;while(*p){p=t;*p=0;}
#define NOT(argc, a, t) \
p=t;*p=1;p=a;while(*p){p=t;*p=0;}
#define AND(argc, a, b, t) \
p=t;*p=0;p=a;while(*p){p=b;while(*p){p=t;*p=1;p=&code[0];}p=&code[0];}
#define OR(argc, a, b, t) \
p=t;*p=0;p=a;while(*p){p=t;*p=1;p=&code[0];}p=b;while(*p){p=t;*p=1;p=&code[0];}
#define If(argc, a) \
p=a;while(*p){
#define endIf(argc, a) \
p=&code[0];}
#define to(argc, a) \
p=a;
#define printf(argc, a) \


int main(void) { code = (int *)calloc(10000, 4); p = &code[0];p=&code[100];*p=44;p=&code[101];*p=46;p=&code[102];*p=62;p=&code[103];*p=60;p=&code[104];*p=43;p=&code[105];*p=25;p=&code[2];*p=1;p=&code[1];*p=1;while(*p){p=&code[1];*p=getchar();isEqual(5, &code[1], &code[100], &code[200], &code[201], &code[300]);If(1, &code[300]);copy(3, &code[1000], &code[2000], &code[1]);p=&code[1000];while(*p){++p;p=&code[1000];--*p;}*p=getchar();copy(3, &code[2000], &code[1000], &code[1]);endIf(1, &code[1]);isEqual(5, &code[1], &code[101], &code[200], &code[201], &code[300]);If(1, &code[300]);copy(3, &code[1000], &code[2000], &code[1]);printf(1, &code[1000]);p=&code[1000];while(*p){++p;p=&code[1000];--*p;}putchar(*p);copy(3, &code[2000], &code[1000], &code[1]);endIf(1, &code[1]);isEqual(5, &code[1], &code[102], &code[200], &code[201], &code[300]);If(1, &code[300]);p=&code[1000];++*p;endIf(1, &code[1]);isEqual(5, &code[1], &code[103], &code[200], &code[201], &code[300]);If(1, &code[300]);p=&code[1000];--*p;endIf(1, &code[1]);isEqual(5, &code[1], &code[104], &code[200], &code[201], &code[300]);If(1, &code[300]);copy(3, &code[1000], &code[2000], &code[1]);p=&code[1000];while(*p){++p;p=&code[1000];--*p;}++*p;copy(3, &code[2000], &code[1000], &code[1]);endIf(1, &code[1]);isEqual(5, &code[1], &code[105], &code[200], &code[201], &code[300]);If(1, &code[300]);copy(3, &code[1000], &code[2000], &code[1]);p=&code[1000];while(*p){++p;p=&code[1000];--*p;}--*p;copy(3, &code[2000], &code[1000], &code[1]);endIf(1, &code[1]);p=&code[2];}return 0; }
