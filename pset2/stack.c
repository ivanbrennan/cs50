#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/* Stack Library - This library offers the minimal stack operations for a stack
 * of integers */

struct stack_rec
{
	stack_data data;
	struct stack_rec *next;
};

struct stack_rec *top = NULL;

void stack_init()
{
	top = NULL;
}

void stack_clear()
{
	while (!stack_empty()) {
		stack_pop();
	}
}

int stack_empty()
{
	if (top == NULL) {
		return(1);
	} else {
		return(0);
	}
}

void stack_push(stack_data d)
{
	struct stack_rec *temp;
	temp = (struct stack_rec *)malloc(sizeof(struct stack_rec));
	temp->data = d;
	temp->next = top;
	top = temp;
}

stack_data stack_pop()
{
	struct stack_rec *temp;
	stack_data d = 0;

	if (top != NULL) {
		d = top->data;
		temp = top;
		top = top->next;
		free(temp);
	}
	return(d);
}

void stack_dup()
{
	stack_data d;

	if (top != NULL) {
		d = top->data;
		stack_push(d);
	}
}

int stack_count()
{
	int count = 0;
	struct stack_rec *el;

	el = top;
	while (el != NULL) {
		count++;
		el = el->next;
	}

	return(count);
}

int stack_add()
{
	int i, sum;
	struct stack_rec *el;

	i = sum = 0;
	el = top;

	while ((el != NULL) && (i < 2)) {
		sum += el->data;
		el = el->next;
		i++;
	}

	return(sum);
}
