#include <stdio.h>

int valid(int digits[], int len);

void printCardType(int digits[], int len);

int main(void)
{
	long long number, balance;
	int i, head;
	int digits[16] = {0};

	// get user input
	printf("Number: ");
	scanf(" %lld", &number);

	// parse digits
	balance = number;
	i = 0;
	while (balance > 0) {
		digits[i] = balance % 10;
		balance /= 10;
		i++;
	}

	// print result
	if (valid(digits, i)) {
		printCardType(digits, i);
	} else {
		printf("INVALID\n");
	}

	return 0;
}

int valid(int digits[], int len)
{
	int i, dbl, sum;

	for (i = 1; i < len; i += 2) {
		dbl = digits[i] * 2;
		sum += dbl / 10; // tens place
		sum += dbl % 10; // ones place
	}
	for (i = 0; i < len; i += 2) {
		sum += digits[i];
	}

	return (sum % 10 == 0);
}

void printCardType(int digits[], int len)
{
	int head;

	head = (10 * digits[len - 1]) + digits[len - 2];

	if ((len == 15) && (head == 34 || head == 37)) {
		printf("AMEX\n");
	} else if ((len == 16 ) && (51 <= head && head <= 55)) {
		printf("MASTERCARD\n");
	} else if (((len == 13) || (len == 16)) && (head / 10 == 4)) {
		printf("VISA\n");
	} else {
		printf("INVALID\n");
	}

	return;
}
