#define MAX 100000000
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
void init(stack *s) {
	s -> p = (Number *)malloc(sizeof(Number) * MAX);
	s -> i = 0;
}

void push(stack *s, Number num) {
	s -> p[s -> i] = num;
	(s -> i)++;
}

Number pop(stack *s) {	
	(s -> i)--;
	return (s -> p[s -> i]);
}

int isfull(stack *s) {
	return (s -> i == MAX);
}

int isempty(stack *s) {	
	return (s -> i == 0);
}

/* functions for cstack */

void cinit(cstack *s) {
	s -> p = (char *)malloc(sizeof(char) * MAX);
	s -> i = 0;
}

void cpush(cstack *s, char inchar) {
	s -> p[(s -> i)] = inchar;
	(s -> i)++;
}

char cpop(cstack *s) {	
	(s -> i)--;
	return (s -> p[s -> i]);
}

int cisfull(cstack *s) {
	return (s -> i == MAX);
}

int cisempty(cstack *s) {	
	return (s -> i == 0);
}

