#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#define MAX 1000000
#include "stack.h"
#include <math.h>
int main() {
	char line[MAX];
	Number x;
	Ninit(&x);
	while(getmyline(line, 8192)) {
		x = infixeval(line);
		printinfix(x);
		printf("\n");
	}
	return 0;
}
	
int getmyline(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n' && i < MAX - 1) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}	

int bracket(char *mainl) {
	length l1;
	char sub1[MAX], sub2[MAX], bracketline[MAX];
	int flag = 0, i = 0, j = 0, inflag = 0;
	char *str;
	Number val;
	while(mainl[i] != '\0') {
		if(mainl[i] == '(')
			flag++;
		i++;	
	}
	if(flag == 0)
		return 0;
	i = 0;
	while(mainl[i] != '(') {
		sub1[i] = mainl[i];
		i++;
	}
	sub1[i++] = '\0';
	while(inflag != -1 && mainl[i] != '\0') {
		if(mainl[i] == '(')
			inflag++;
		bracketline[j++] = mainl[i++];
		if(mainl[i] == ')')
			inflag--; 
	}
	bracketline[j] = '\0';
	j = 0;
	i++;
	while(mainl[i] != '\0')
		sub2[j++] = mainl[i++];
	sub2[j] = '\0';
	val = infixeval(bracketline);
	l1 = lengthofNumber(val);
	str = (char *)malloc(sizeof(char) * (l1.lbd + l1.lad + 1));
	Integertostring(val, str);
	strcpy(bracketline, str);
	strcat(sub1, bracketline);
	strcat(sub1, sub2);
	strcpy(mainl, sub1);
	return 1;	
}
stack s;
Number infixeval(char *l) {
	int i = 0, lbd1, lad1;
	Number j, j1;
	Ninit(&j);
	Ninit(&j1);
	char k, k1;
	stack temp;
	cstack cs, ctemp;
	length l1;
	init(&s);
	cinit(&cs);
	init(&temp);
	cinit(&ctemp);
	while(bracket(l));
	while(l[i] != '\0') {
		j = takenumber(l, &i);
		push(&s, j);
		k = takecharachter(l, &i);
		cpush(&cs, k);
	}
	if(top(&cs) == 'e')
		cpop(&cs);
	while(!cisempty(&cs)) {
		k = cpop(&cs);
		k1 = top(&cs);
		if(priority(k) > priority(k1)) {
			j = pop(&s);
			j1 = pop(&s);
			switch(k) {
				case '+' :
					j = add(j1, j);
					break;
				case '-' : 
					j = sub(j1, j);
					break;
				case '*' :
					j = mul(j, j1);
					break;
				case '/' :
					l1 = lengthofNumber(j);
					if((l1.lbd == 0 && l1.lad == 0) || (l1.lbd == 1 && j.head->dig == '0' && l1.lad == 0)) {
						printf("cant divide by 0\n");
						exit(0);
					}
					else
						j = division(j1, j);
					break;
				case '%' : 
					l1 = lengthofNumber(j);
					if(l1.lad != 0) {
						printf("wrong input\n");
						exit(0);
					}
					l1 = lengthofNumber(j1);
					if(l1.lad != 0) {
						printf("wrong input\n");
						exit(0);
					}
					j = mod(j1, j);
					break;
				case '^' :
					j = powe(j1, j);
					break;
			}
			push(&s, j);
			while(!isempty(&temp)) {
				j = pop(&temp);
				push(&s, j);
			}
			while(!cisempty(&ctemp)) {
				k = cpop(&ctemp);
				cpush(&cs, k);
			}
		}
		else {
			cpush(&ctemp, k);
			j = pop(&s);
			push(&temp, j);
		}
	}	
	j = pop(&s);
	if(isempty(&s))
		return j;
	//else
		//return perror;				
}

char top(cstack *ts) {
	char top = '\0';
	if(!cisempty(ts)) {
		top = cpop(ts);
		cpush(ts, top);
	}	
	return top;
}

int priority(char ch) {
	switch(ch) {
		case '+' : case '-' :
			return 1;
			break;
		case '*' : case '/' :
			return 2;
			break;
		case '%' :
			return 3;	
			break;
		case '^':
			return 4;
			break;
		default :
			return -1;
			break;	
	}
	return -1;
}

Number takenumber(char *l, int *p) {	
	Number a;
	Ninit(&a);
	int flag = 0;
	int sign = 1;
	while(l[*p] == ' ')
		*p += 1;
	if(l[*p] == 's' && l[*p + 1] == 'i' && l[*p + 2] == 'n') {
		flag = 1;
		*p += 3;
	}
	if(l[*p] == 'c' && l[*p + 1] == 'o' && l[*p + 2] == 's') {
		flag = 2;
		*p += 3;
	}
	if(l[*p] == 't' && l[*p + 1] == 'a' && l[*p + 2] == 'n') {
		flag = 3;
		*p += 3;
	}
	if(l[*p] == 's' && l[*p + 1] == 'e' && l[*p + 2] == 'c') {
		flag = 4;
		*p += 3;
	}
	if(l[*p] == 'c' && l[*p + 1] == 'o' && l[*p + 2] == 's' && l[*p + 3] == 'e' && l[*p + 4] == 'c') {
		flag = 5;
		*p += 5;
	}
	if(l[*p] == 'c' && l[*p + 1] == 'o' && l[*p + 2] == 't') {
		flag = 6;
		*p += 3;
	}
	if(l[*p] == '-') {
		a.sign = -1;
		*p += 1;
	}
	else
		a.sign = 1;	
	while(l[*p] == ' ')
		*p += 1;	
	while((l[*p] <= '9' && l[*p] >= '0') || l[*p] == '.') {	
		appendright(&a, l[*p]);
		*p += 1;
	}
	if(flag == 0);
	else if(flag == 1)
		a = sine(a);
	else if(flag == 2)
		a = cosine(a);
	else if(flag == 3)
		a = tangent(a);
	else if(flag == 4)
		a = sec(a);
	else if(flag == 5)
		a = cosec(a);
	else if(flag == 6)
		a = cot(a);
	return a;
}

char takecharachter(char *l, int *p) {
	char ch = '\0';
	Number c;
	length l1;
	while(1) {
		if(l[*p] == '\0')
			return 'e';	
		else if(l[*p] != ' ' && l[*p] != '!') {
			ch = l[*p];
			*p += 1;
			break;
		}
		else if(l[*p] == '!') {
			c = pop(&s);
			l1 = lengthofNumber(c);
			if(c.sign == 1 && l1.lad == 0) {
				c = factorial(c);
				push(&s, c);
				//*p += 1;
			}
		}
		*p += 1;		
	}
	return ch;
}
