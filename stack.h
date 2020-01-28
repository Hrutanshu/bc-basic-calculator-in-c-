#include <stdio.h>
#include "bc.h"
typedef struct stack {
	Number *p;
	int i;
}stack;

typedef struct cstack {
	char *p;
	int i;
}cstack;
 
void init(stack *s);
void push(stack *s, Number num);
Number pop(stack *s);
int isempty(stack *s);
int isfull(stack *s);

void cinit(cstack *s);
void cpush(cstack *s, char ch);
char cpop(cstack *s);
int cisempty(cstack *s);
int cisfull(cstack *s);
char top(cstack *ts);
