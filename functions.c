#include "bc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void Ninit(Number *a) {
	a->head = a->tail = NULL;
	a->sign = 1;
}
void insertfromlast(Number *c, char ch, int pos) {
	node *p;
	int i;
	p = c->tail;
	if(!pos)
		return;
	else {
	node *tmp;
	tmp = (node *)malloc(sizeof(node));
	tmp->dig = ch;
		for(i = 0; i < pos; i++) 
			p = p->prev;
		tmp->next = p->next;
		tmp->prev = p;
		p->next->prev = p->next = tmp;
	}
}
void remov(Number *a, char ch) {
	node *p;
	p = a->head;
	if(p->dig == ch) {
		a->head = p->next;
		p->next->prev = NULL;
		return;
	}
	if(p->dig == '0' && p->next->dig == ch) {
		a->head = p->next->next;
		p->next->next->prev = NULL;
		return;
	}
	while(p) {
		if(p->dig == ch) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			break;
		}
		p = p->next;
	}
}	
void appendleft(Number *a, char ch) {
	node *tmp, *p;
	p = a->head;
	tmp = (node *)malloc(sizeof(node));
	tmp->dig = ch;
	tmp->prev = NULL;
	if(!p) {
		a->head = a->tail = tmp;
		tmp->next = NULL;
	}
	else {
		tmp->next = a->head;
		a->head->prev = a->head = tmp;
	}
}
void appendright(Number *a, char ch) {
	node *tmp, *p;
	p = a->tail;
	tmp = (node *)malloc(sizeof(node));
	tmp->dig = ch;
	tmp->next = NULL;
	if(!p) {
		a->head = a->tail = tmp;
		tmp->prev = NULL;
	}
	else {
		tmp->prev = a->tail;
		a->tail->next = a->tail = tmp;
	}
}
length lengthofNumber(Number a) {
	node *p;
	p = a.head;
	length l;
	l.lbd = l.lad = 0;
	if(!p) {
		l.lbd = l.lad = 0;
		return l;
	}
	else {
		if(p->dig == '.') {
			l.lbd = 0;
			p = p->next;
			while(p) {
				(l.lad)++;
				p = p->next;
			}
			return l;
		}
		else {
			while(p) {
				if(p->dig != '.') {
					(l.lbd)++;
					p = p->next;
				}
				else  {
					p = p->next;
					while(p) {
						(l.lad)++;
						p = p->next;
					}
				}
			}
			return l; 
		}
	}
}
int bigger(Number a, Number b) {
	int i;
	length l1, l2;
	l1 = lengthofNumber(a);
	l2 = lengthofNumber(b);
	node *p, *q;
	if(l1.lbd > l2.lbd) {
		i = l1.lbd - l2.lbd;
		while(i!=0) {
			appendleft(&b, '0');
			i--;
		}
	}
	if(l2.lbd > l1.lbd) {
		i = l2.lbd - l1.lbd;
		while(i!=0) {
			appendleft(&a, '0');
			i--;
		}
	}
	if(l2.lad) {
		if(l1.lad > l2.lad) {
			i = l1.lad - l2.lad;
			while(i != 0) {
				appendright(&b, '0');
				i--;
			}
		}
	}
	if(!l2.lad) { 
		if(l1.lad > l2.lad) {
			appendright(&b, '.');
			i = l1.lad - l2.lad;
			while(i != 0) {
				appendright(&b, '0');
				i--;
			}
		}
	}
	if(l1.lad) {
		if(l2.lad > l1.lad) {
			i = l2.lad - l1.lad;
			while(i != 0) {
				appendright(&a, '0');
				i--;
			}
		}
	}
	if(!l1.lad) {
		if(l2.lad > l1.lad) {
			appendright(&a, '.');
			i = l1.lad - l2.lad;
			while(i != 0) {
				appendright(&a, '0');
				i--;
			}
		}
	}
	p = a.head;
	q = b.head;
	while(p) {
		if((p->dig - '0') > (q->dig - '0'))
			return 1;
		else if((p->dig - '0') < (q->dig - '0'))
			return -1;
		else {
			p = p->next;
			q = q->next;
		}
	}
	return 0;
}
Number add(Number a, Number b) {
	node *p, *q;
	Number c;
	Ninit(&c);
	length l1, l2;
	int i;
	l1.lbd = l1.lad = l2.lbd = l2.lad = 0;
	if((a.sign == 1 && b.sign == 1) || (a.sign == -1 && b.sign == -1)) {
		if(a.sign == 1 && b.sign == 1)
			c.sign = 1;
		if(a.sign == -1 && b.sign == -1)
			c.sign = -1;
		l1 = lengthofNumber(a);
		l2 = lengthofNumber(b);
		if(l1.lbd == 0 && l2.lbd == 0 && l1.lad == 0 && l2.lad == 0) {
			appendright(&c, '0');
			c.sign = 1;
			return c;
		}
		else {
			if(l1.lbd > l2.lbd) {
				i = l1.lbd - l2.lbd;
				while(i!=0) {
					appendleft(&b, '0');
					i--;
				}
			}
			if(l2.lbd > l1.lbd){
				i = l2.lbd - l1.lbd;
				while(i!=0) {
					appendleft(&a, '0');
					i--;
				}
			}
			if(l2.lad) {
				if(l1.lad > l2.lad) {
					i = l1.lad - l2.lad;
					while(i != 0) {
						appendright(&b, '0');
						i--;
					}
				}
			}
			if(!l2.lad) { 
				if(l1.lad > l2.lad) {
					appendright(&b, '.');
					i = l1.lad - l2.lad;
					while(i != 0) {
						appendright(&b, '0');
						i--;
					}
				}
			}
			if(l1.lad) {
				if(l2.lad > l1.lad) {
					i = l2.lad - l1.lad;
					while(i != 0) {
						appendright(&a, '0');
						i--;
					}
				}
			}
			if(!l1.lad) {
				if(l2.lad > l1.lad) {
					appendright(&a, '.');
					i = l2.lad - l1.lad;
					while(i != 0) {
						appendright(&a, '0');
						i--;
						}
				}
			}
		}
		p = a.tail;
		q = b.tail;
		l1 = lengthofNumber(a);
		i = 0;
		int carry = 0, num, j = 0, i1, i2;
		if(l1.lad) {
			for (i = 0; i < l1.lad; i++) {
				i1 = p->dig - '0';
				i2 = q->dig - '0';
				if((i1 + i2 + carry) >= 10) {
					num = (i1 + i2 + carry) % 10;
					appendleft(&c, (num + '0'));
					carry = 1;
				}
				else {
					num = i1 + i2 + carry;
					appendleft(&c, (num + '0'));
					carry = 0;
				}	
				p = p->prev;
				q = q->prev;
			}
			appendleft(&c, '.');
			p = p->prev;
			q = q->prev;
		}
		if(l1.lbd) {
			for (i = 0; i < l1.lbd; i++) {
				i1 = p->dig - '0';
				i2 = q->dig - '0';
				if((i1 + i2 + carry) >= 10) {
					num = (i1 + i2 + carry) % 10;
					appendleft(&c, (num + '0'));
					carry = 1;
				}
				else {
					num = i1 + i2 + carry;
					appendleft(&c, (num + '0'));
					carry = 0;
				}	
				p = p->prev;
				q = q->prev;
			}
		}
		if(carry > 0)
			appendleft(&c, (carry + '0'));
	}
	else if((a.sign == -1 && b.sign == 1)) {
		a.sign = b.sign = 1;
		c = sub(b, a);
	}
	else if((a.sign == 1 && b.sign == -1)) {
		a.sign = b.sign = 1;
		c = sub(a, b);
	}
	return c;
}
Number sub(Number a, Number b) {
	node *p, *q;
	Number c;
	Ninit(&c);
	length l1, l2;
	int i, big;
	l1.lbd = l1.lad = l2.lbd = l2.lad = 0;
	if((a.sign == 1 && b.sign == 1)) {
		l1 = lengthofNumber(a);
		l2 = lengthofNumber(b);
		if(l1.lbd == 0 && l2.lbd == 0 && l1.lad == 0 && l2.lad == 0) {
			appendright(&c, '0');
			return c;
		}
		else {
			if(l1.lbd > l2.lbd) {
				i = l1.lbd - l2.lbd;
				while(i!=0) {
					appendleft(&b, '0');
					i--;
				}
			}
			if(l2.lbd > l1.lbd){
				i = l2.lbd - l1.lbd;
				while(i!=0) {
					appendleft(&a, '0');
					i--;
				}
			}
			if(l1.lad > l2.lad && l2.lad) {
				i = l1.lad - l2.lad;
				while(i != 0) {
					appendright(&b, '0');
					i--;
				}
			}
			if(l2.lad) {
				if(l1.lad > l2.lad) {
					i = l1.lad - l2.lad;
					while(i != 0) {
						appendright(&b, '0');
						i--;
					}
				}
			}
			if(!l2.lad) { 
				if(l1.lad > l2.lad) {
					appendright(&b, '.');
					i = l1.lad - l2.lad;
					while(i != 0) {
						appendright(&b, '0');
						i--;
					}
				}
			}
			if(l1.lad) {
				if(l2.lad > l1.lad) {
					i = l2.lad - l1.lad;
					while(i != 0) {
						appendright(&a, '0');
						i--;
					}
				}
			}
			if(!l1.lad) {
				if(l2.lad > l1.lad) {
					appendright(&a, '.');
					i = l2.lad - l1.lad;
					while(i != 0) {
						appendright(&a, '0');
						i--;
						}
				}
			}
		}
		big = bigger(a, b);
		if(big == 1) {
			c.sign = 1;
			p = a.tail;
			q = b.tail;
			l1 = lengthofNumber(a);
			i = 0;
			int carry = 0, num, j = 0, i1, i2;
			if(l1.lad) {
				for (i =0; i < l1.lad; i++) {
					i1 = p->dig - '0';
					i2 = q->dig - '0';
					if((i1 - i2 + carry) < 0) {
						num = (i1 + 10 - i2 + carry);
						appendleft(&c, (num + '0'));
						carry = -1;
					}
					else {
						num = i1 - i2 + carry;
						appendleft(&c, (num + '0'));
						carry = 0;
					}	
					p = p->prev;
					q = q->prev;
				}
				appendleft(&c, '.');
				p = p->prev;
				q = q->prev;
			}
			if(l1.lbd) {
				for (i =0; i < l1.lbd; i++) {
					i1 = p->dig - '0';
					i2 = q->dig - '0';
					if((i1 - i2 + carry) < 0) {
						num = (i1 + 10 - i2 + carry);
						appendleft(&c, (num + '0'));
						carry = -1;
					}
					else {
						num = i1 - i2 + carry;
						appendleft(&c, (num + '0'));
						carry = 0;
					}	
					p = p->prev;
					q = q->prev;
				}
			}	
			return c;
		}
		else if(big == -1) {
			c = sub(b, a);
			c.sign = -1;
			return c;
		}
		else if(big == 0) {
			appendleft(&c, '0');
			c.sign = 1;
			return c;
		}
		
	}
	else if((a.sign == -1 && b.sign == -1)) {
		a.sign = b.sign = 1;
		c = sub(b, a);
		return c;
	}
	else if((a.sign == -1 && b.sign == 1)) {
		a.sign = b.sign = -1;
		c = add(a, b);
		return c;
	}
	else if((a.sign == 1 && b.sign == -1)) {
		a.sign = b.sign = 1;
		c = add(a, b);
		return c;
	}
}
Number mul(Number a, Number b) {
	node *p, *q;
	Number c, temp;
	length l1, l2;
	Ninit(&c);
	Ninit(&temp);
	int x, carry, y, z;
	l1.lbd = l1.lad = l2.lbd = l2.lad = 0;
	l1 = lengthofNumber(a);
	l2 = lengthofNumber(b);
	int len1, len2;
	len1 = l1.lbd + l1.lad;
	len2 = l2.lbd + l2.lad;
	p = a.head;
	q = b.head;
	if(len1 == 0 || len2 == 0 || (len1 == 1 && p->dig == '0') || (len2 == 1 && q->dig == '0')) {
		appendleft(&c, '0');
		return c;
	}
	remov(&a, '.');
	remov(&b, '.');
	q = b.tail;
	z = 0;
	while(q) {
		
		carry = 0;
		p = a.tail;
		Ninit(&temp);
		while(p) {
		
			x = (p->dig - '0') * (q->dig - '0') + carry;
			//printf("%d",x);
			carry = x / 10;
			x = x % 10;
			appendleft(&temp, (x + '0'));
			p = p->prev;
		}
		if(carry > 0)
			appendleft(&temp, (carry + '0'));
		for(y = 0;y < z; y++) 
			appendright(&temp, '0');
		c = add(c, temp);
		q = q->prev;
		z++;
	}
	
	
	if((a.sign == 1 && b.sign == -1) || (a.sign == -1 && b.sign == 1))
		c.sign = -1;
	if((a.sign == 1 && b.sign == 1) || (a.sign == -1 && b.sign == -1))
		c.sign = 1;
		
	insertfromlast(&c, '.', l1.lad + l2.lad);
	return c;
}
Number subofdiv(Number a, Number b) {
	Number c;
	node *p, *q;
	Ninit(&c);
	length l1, l2;
	int i1, i2, i, num, carry = 0;
	l1 = lengthofNumber(a);
	l2 = lengthofNumber(b);
	if(l1.lbd == 0 && l2.lbd == 0 && l1.lad == 0 && l2.lad == 0) {
		appendright(&c, '0');
		return c;
	}
	p = a.tail;
	q = b.tail;
	for (i = 0; i < l1.lbd; i++) {
		i1 = p->dig - '0';
		i2 = q->dig - '0';
		if((i1 - i2 + carry) < 0) {
			num = (i1 + 10 - i2 + carry);
			appendleft(&c, (num + '0'));
			carry = -1;
		}
		else {
			num = i1 - i2 + carry;
			appendleft(&c, (num + '0'));
			carry = 0;
		}	
		p = p->prev;
		q = q->prev;
	}
	return c;
}			
Number division(Number a, Number b) {
	node *p, *q;
	int big, big1, big2, big3, big4, big5, i, x;
	Number c, temp;
	Ninit(&temp);
	length l1, l2;
	Ninit(&c);
	if((a.sign == 1 && b.sign == -1) || (a.sign == -1 && b.sign == 1))
		c.sign = -1;
	if((a.sign == 1 && b.sign == 1) || (a.sign == -1 && b.sign == -1))
		c.sign = 1;
	l1 = lengthofNumber(a);
	l2 = lengthofNumber(b);
	p = a.head;
	if((l1.lbd == 0 && l1.lad == 0) || (l1.lbd == 1 && p->dig == '0' && l1.lad == 0)) {
		appendleft(&c, '0');
		return c;
	}
	remov(&a, '.');
	remov(&b, '.');
	if(l1.lad < l2.lad) {
		for(i = 0; i < l2.lad - l1.lad; i++)
			appendright(&a, '0');
	}
	if(l1.lad > l2.lad) {
		for(i = 0; i < l1.lad - l2.lad; i++)
			appendright(&b, '0');
	}
	big = bigger(a, b);
	p = a.head;
	if(big == 1) {
		l1 = lengthofNumber(a);
		l2 = lengthofNumber(b);
		for(i = 0; i < l2.lbd; i++) {
			appendright(&temp, p->dig);
			p = p->next;
		}
		big2 = bigger(temp, b);
		if(big2 == 1 || big2 == 0)
			i = 0;
		else if(big2 == -1) {
			i = 1;
			appendright(&temp, p->dig);
			p = p->next;
		}	
		for(; i <= l1.lbd - l2.lbd; i++) {
			big1 = bigger(temp, b);
			if(big1 == 1) {
				x = 0;
				while(1) {
					temp = subofdiv(temp, b);
					x++;
					big3 = bigger(temp, b);
					if(big3 == 1) {
						continue;
					}
					else if(big3 == -1) {
						appendright(&c, x + '0');
						break;
					}
					else if(big3 == 0) {
						appendright(&c, x + 1 + '0');
						Ninit(&temp);
						break;
					}
				}
				if(p) {
					appendright(&temp, p->dig);
					p = p->next;	
				}
			}
			else if(big1 == -1) {
				appendright(&c, '0');
				if(p) {
					appendright(&temp, p->dig);
					p = p->next;
				}
			}
			else if(big1 == 0) {
				appendright(&c, '1');
				Ninit(&temp);
				if(p) {
					appendright(&temp, p->dig);
					p = p->next;
				}
			}
		}
		if(!(temp.head))
			return c;
		else {
			appendright(&c, '.');
			for(i = 0; i < 100; i++) {
				while(1) {
					appendright(&temp, '0');
					big4 = bigger(temp, b);
					if(big4 == 1) {
						x = 0;
						while(1) {
							temp = subofdiv(temp, b);
							x++;
							big5 = bigger(temp, b);
							if(big5 == 1) {
								continue;
							}
							else if(big5 == -1) {
								appendright(&c, x + '0');
								break;
							}
							else if(big5 == 0) {
								appendright(&c, x + 1 + '0');
								return c;
							}
						}
						break;
					}
					else if(big4 == -1) {
						appendright(&c, '0');
						break;
					}
					else if(big4 == 0) {
						appendright(&c, '1');
						return c;
					}
				}
			}
		}

	}
	else if(big == -1){
		appendright(&c, '0');
		appendright(&c, '.');
		for(i = 0; i < 100; i++) {
			while(1) {
				appendright(&a, '0');
				big1 = bigger(a, b);
				if(big1 == 1) {
					x = 0;
					while(1) {
						a = subofdiv(a, b);
						x++;
						big2 = bigger(a, b);
						if(big2 == 1) {
							continue;
						}
						else if(big2 == -1) {
							appendright(&c, x + '0');
							break;
						}
						else if(big2 == 0) {
							appendright(&c, x + 1 + '0');
							return c;
						}
					}
					break;
				}
				else if(big1 == -1) {
					appendright(&c, '0');
					break;
				}
				else if(big1 == 0) {
					appendright(&c, '1');
					return c;
				}
			}
		}
	}
	else if(big == 0){
		appendleft(&c, '1');
		return c;
	}
	return c;
}
Number mod(Number a, Number b) {
	Number c, temp;
	Ninit(&temp);
	Ninit(&c);
	int big, big1;
	big = bigger(a, b);
	temp = a;
	if(big == 1) {
		c.sign = a.sign;
		while(1) {
			temp = subofdiv(temp, b);
			big1 = bigger(temp, b);
			if(big1 == 1) {
				continue;
			}
			else if(big1 == -1) {
				return temp;
			}
			else if(big1 == 0) {
				appendleft(&c, '0');
				return c;
			}
		}
	}
	else if(big == -1) {
		return a;
	}
	else if(big == 0) {
		appendleft(&c, '0');
		return c;
	}
}
Number powe(Number j1, Number j) {
	Number f, g;
	Ninit(&f);
	Ninit(&g);
	appendleft(&g, '1');
	appendleft(&f, '1');
	length l1;
	l1 = lengthofNumber(j);
	if((l1.lbd == 0 && l1.lad == 0) || (l1.lbd == 1 && j.head->dig == '0' && l1.lad == 0)) {
		if(j.sign == 1)
			return f;
		else if(j.sign == -1)
			return f = division(g, f);
	}
	else if((l1.lbd == 1 && j.head->dig == '1' && l1.lad == 0)) {
		if(j.sign == 1)
			return j1;
		else if(j.sign == -1)
			return j1 = division(g, j1);
	}
	else {
		while(1) {
			if((l1.lbd == 0 && l1.lad == 0) || (l1.lbd == 1 && j.head->dig == '0' && l1.lad == 0))
				break;
			f = mul(f, j1);
			j = sub(j, g);
			l1 =  lengthofNumber(j);
		}
		if(j.sign == 1)
			return f;
		else if(j.sign == -1)
			return f = division(g, f);
	}

}	
Number factorial(Number c) {
	Number f, g;
	Ninit(&f);
	Ninit(&g);
	appendleft(&g, '1');
	appendleft(&f, '1');
	length l1;
	l1 = lengthofNumber(c);
	if((l1.lbd == 0 && l1.lad == 0) || (l1.lbd == 1 && (c.head->dig == '0' || c.head->dig == '1') && l1.lad == 0)) {
		appendleft(&f, '1');
		return f;
	}
	else {
		while(1) {
			if((l1.lbd == 0 && l1.lad == 0) || (l1.lbd == 1 && c.head->dig == '0' && l1.lad == 0))
				break;
			f = mul(f, c);
			c = sub(c, g);
			l1 =  lengthofNumber(c);
		}
		return f;
	}

}
Number sine(Number a) {/*
	Number sum, temp, temp1, temp2, temp3, temp4, fact;
	Ninit(&sum);
	Ninit(&temp1);
	Ninit(&temp3);
	Ninit(&temp);
	Ninit(&temp4);
	Ninit(&fact);
	temp4.sign = -1;
	int i, j, x;
	x = -1;
	appendleft(&temp1, '2');
	appendleft(&temp1, '1');
	for(i = 0; i < 5; i++) {
		Ninit(&temp2);
		if(i < 10) {
			appendleft(&temp2, i + '0');
		}
		else {
			j = i;
			while(j) {
				appendleft(&temp2, (j % 10) + '0');
				j = j / 10;
			}
		}
		temp = mul(temp1, temp2);
		temp = add(temp, temp3);
		fact = factorial(temp);
		temp = powe(a, temp);
		temp = division(temp, fact);
		if(i % 2 == 0)
			temp.sign = 1;
		else
			temp.sign = -1;
		sum = add(sum, temp);
	}
	return sum;*/
		
}
Number cosine(Number a) {
}
Number tangent(Number a) {
}
Number sec(Number a) {
}
Number cosec(Number a) {
}
Number cot(Number a) {
}
void printinfix(Number x) {
	node *p;
	p = x.head;
	if(!p) {
		return;
	}
	else {
		if(x.sign == -1)
			printf("-");
		while(p) {
			printf("%c",p->dig);
			p = p->next;
		}
	}
	return;
}
void Integertostring(Number val, char* str) {
	node *p;
	p = val.head;
	length l1;
	int i = 0;
	l1 = lengthofNumber(val);
	if(!p) {
		return;
	}
	else {
		while(p) {
			str[i] = p->dig;
			p = p->next;
			i++;
		}
	}
	return;
}		
