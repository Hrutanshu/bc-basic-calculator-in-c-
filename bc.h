#include <stdio.h>
typedef struct node {
	char dig;
	struct node *next, *prev;
}node;
typedef struct Number {
	node *head, *tail;
	int sign;
}Number;
typedef struct token {
	Number n;
	char op;
	int type;
}token;
typedef struct length {
	int lbd, lad;
}length;
Number add(Number a, Number b);
length lengthofNumber(Number a);
Number mod(Number a, Number b);
Number division(Number a, Number b);
Number subofdiv(Number a, Number b);
Number mul(Number a, Number b);
Number sub(Number a, Number b);
int bigger(Number a, Number b);
void appendright(Number *a, char ch);
void appendleft(Number *a, char ch);
void remov(Number *a, char ch);
void insertfromlast(Number *c, char ch, int pos);
void Ninit(Number *a);
int getmyline(char *arr, int len);
int bracket(char *mainl);
Number infixeval(char *l);
int priority(char ch);
Number takenumber(char *l, int *p);
char takecharachter(char *l, int *p);
void printinfix(Number x);
void Integertostring(Number val, char* str);
Number factorial(Number c);
Number powe(Number j1, Number j);
Number sine(Number a);
Number cosine(Number a);
Number tangent(Number a);
Number sec(Number a);
Number cosec(Number a);
Number cot(Number a);
