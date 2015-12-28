#include "stack.h"
#include <stdio.h>

int main()
{
	int i;
	stack_data pushed[4], popped;

	printf("Initializing the stack...\n");
	stack_init();
	printf("Stack has %d elements.\n", stack_count());
	printf("Top two elements sum to %d\n", stack_add());

	printf("Pushing on the stack...\n");
	for (i = 0; i < 4; i++) {
		pushed[i] = i;
		stack_push(pushed[i]);
		printf("\tpushed %d\n", pushed[i]);
	}
	printf("Top two elements sum to %d\n", stack_add());

	printf("Dupping a couple times...\n");
	for (i = 0; i < 2; i++) {
		stack_dup();
	}

	printf("Stack has %d elements.\n", stack_count());

	printf("Popping off the stack...\n");
	while (!stack_empty()) {
		popped = stack_pop();
		printf("\tpopped %d\n", popped);
	}

	printf("Pushing a couple more...\n");
	stack_push(9);
	printf("\tpushed %d\n", 9);
	printf("Top two elements sum to %d\n", stack_add());
	stack_push(10);
	printf("\tpushed %d\n", 10);
	printf("Top two elements sum to %d\n", stack_add());

	printf("Clearing the stack...\n");
	stack_clear();

	printf("Now popping returns garbage...\n");
	for (; i > 0; i--) {
		popped = stack_pop();
		printf("\tpopped %d\n", popped);
	}

	return 0;
}
