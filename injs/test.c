#include <stdio.h>
#include <stdlib.h>
#define __def void
char *code, *p;
#define clear(argc, a) \
p = a;while(*p) { --*p;}
#define move(argc, a, b) \
p = a;while(*p) { p = b;++*p;p = a;--*p;}
#define for(argc, a) \
p = a;while(*p) { 
#define next(argc, a) \
p = a;--*p;}
#define move2(argc, s, d, t) \
for(1,s);p = d;++*p;p = t;++*p;next(1,s);
#define copy(argc, s, d, t) \
move2(3,s,d,t);move(2,t,s);

int main(void) { code = (char *)calloc(10000, 1); p = &code[0];++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;while(*p) { ++p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++p;++*p;++*p;++*p;++p;++*p;--p;--p;--p;--p;--*p;}++p;++*p;++*p;putchar(*p);++p;++*p;putchar(*p);++*p;++*p;++*p;++*p;++*p;++*p;++*p;putchar(*p);putchar(*p);++*p;++*p;++*p;putchar(*p);++p;++*p;++*p;putchar(*p);--p;--p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;++*p;putchar(*p);++p;putchar(*p);++*p;++*p;++*p;putchar(*p);--*p;--*p;--*p;--*p;--*p;--*p;putchar(*p);--*p;--*p;--*p;--*p;--*p;--*p;--*p;--*p;putchar(*p);++p;++*p;putchar(*p);++p;putchar(*p);p = &code[0];*p = 101;p = &code[1];*p = 0;move(2, &code[0], &code[1]);p = &code[1];putchar(*p);clear(1, &code[1]);p = &code[0];*p = 10;move(2, &code[0], &code[1]);p = &code[1];putchar(*p);p = &code[0];*p = 72;p = &code[1];*p = 0;p = &code[2];*p = 0;copy(3, &code[0], &code[1], &code[2]);p = &code[1];putchar(*p);return 0; }
