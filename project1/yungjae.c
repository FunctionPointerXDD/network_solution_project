#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

#include <time.h>


typedef enum{
	EQUAL, GREATER, SMALLER
}CompRes;

#define MAX_SIZE 100
// MAX_SIZE * 2 + Operator + Signs(if any) + EOS(end of string)
#define MAX_INPUT_SIZE  2 * MAX_SIZE + 1 + 2 + 1

#define TRUE 1
#define FALSE 0

#define INT_BIT_LENGTH sizeof(int) * 8

typedef char bool;

typedef struct 
{
	char value[MAX_SIZE];
	unsigned int length;
	bool sign;
} Number;


CompRes CompareAbs(Number* leftOperand, Number* rightOperand);
void Print(const Number* number);


void Add(Number*, Number*);
void Sub(Number*, Number*);
typedef void (*Operation)(Number*, Number*);
Operation operations[UCHAR_MAX] = { FALSE, };

void Init()
{
	operations['+'] = Add;
	operations['-'] = Sub;
}



Operation GetExpression(Number*, Number*);

void TestModAndMul();

int main()
{
	Init();
	Number leftOperand = { 0 };
	Number rightOperand = { 0 };

	Operation operation = GetExpression(&leftOperand, &rightOperand);

	if (operation == NULL) {
		return 1;
	}

	/*Print(&leftOperand);
	Print(&rightOperand);*/

	operation(&leftOperand, &rightOperand);


	//TestModAndMul();
	return 0;
}

Operation GetExpression(Number* leftOperand, Number* rightOperand)
{
	char input[MAX_INPUT_SIZE];

	printf("> ");
	scanf("%s", input);

	
	unsigned int cursor = 0;
	leftOperand->sign = FALSE;
	if (input[cursor] == '-') {
		leftOperand->sign = TRUE;
		cursor++;
	}

	unsigned int startCursor = cursor;
	char current = input[cursor];
	while (!operations[current]) {
		if (!isdigit(current)) {
			return NULL;
		}
		current = input[++cursor];
	}

	leftOperand->length = cursor - startCursor;
	for (unsigned int i = 0; i < leftOperand->length; i++) {
		leftOperand->value[i] = input[cursor - 1 - i] - '0';
	}


	

	
	Operation operation = operations[current];





	current = input[++cursor];

	rightOperand->sign = FALSE;
	if (current == '-') {
		rightOperand->sign = TRUE;
		current = input[++cursor];
	}

	startCursor = cursor;
	while (input[cursor] != '\0') {
		if (!isdigit(current)) {
			return NULL;
		}
		current = input[++cursor];
	}
	rightOperand->length = cursor - startCursor;
	for (unsigned int i = 0; i < rightOperand->length; i++) {
		rightOperand->value[i] = input[cursor - 1 - i] - '0';
	}


	return operation;
}



void Add(Number* leftOperand, Number* rightOperand)
{
	Number result = { 0 };

	CompRes compRes = CompareAbs(leftOperand, rightOperand);

	Number* greater = leftOperand;
	Number* smaller = rightOperand;
	
	if (compRes == SMALLER) {
		greater = rightOperand;
		smaller = leftOperand;
	}
	result.length = greater->length;
	result.sign = greater->sign;


	// Same sign
	if (greater->sign == smaller->sign) {
		bool carry = FALSE;
		for (unsigned int i = 0; i < result.length; i++) {
			result.value[i] = greater->value[i] + smaller->value[i]  + carry ;

			carry = result.value[i] / 10;
			result.value[i] = result.value[i] - (10 * carry);
		}

		result.value[result.length] = carry;
		result.length += carry;
		Print(&result);
		return;
	}

	// Different sign & Same absolute value
	if (compRes == EQUAL) {
		result.length = 1;
		result.sign = FALSE;
		result.value[0] = 0;
		Print(&result);
		return;
	}

	// Different sign & Different absolute value
	bool borrow = FALSE;
	for (unsigned int i = 0; i < result.length; i++) {
		result.value[i] = greater->value[i] - smaller->value[i] - borrow;
		borrow = (result.value[i] >> (INT_BIT_LENGTH - 1)) & 1;
		result.value[i] = result.value[i] + (10 * borrow);
	}

	result.length -= !(result.value[result.length - 1]);	
	Print(&result);

}


void Sub(Number*leftOperand, Number* rightOperand)
{
	rightOperand->sign = !rightOperand->sign;
	Add(leftOperand, rightOperand);
}

CompRes CompareAbs(Number* leftOperand, Number* rightOperand)
{
	if (leftOperand->length > rightOperand->length) {
		return GREATER;
	}
	if (leftOperand->length < rightOperand->length) {
		return SMALLER;

	}
	if (leftOperand->length == rightOperand->length) {
		for (int i = leftOperand->length; i >= 0; i--) {
			if (leftOperand->value[i] < rightOperand->value[i]) {
				return SMALLER;
			}
			if (leftOperand->value[i] > rightOperand->value[i]) {
				return GREATER;
			}
		}
	}
	return EQUAL;
}

void Print(const Number* number)
{
	if (number->sign) {
		printf("Sign : -, ");
	}
	printf("Length : %d,  ", number->length);
	for (int i = number->length - 1; i >= 0; i--) {
		printf("%d", number->value[i]);
	}
	printf("\n");
}





void TestModAndMul()
{
	clock_t start, end;
	double time_taken;

	int a = 123456789;
	int b = 987654321;
	int result;

	const unsigned int NUM_ITERATIONS = 100000000;
	start = clock();
	for (unsigned int i = 0; i < NUM_ITERATIONS; ++i) {
		result = a * b - 1;
	}
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Multiplication: %f seconds\n", time_taken);

	start = clock();
	for (unsigned int i = 0; i < NUM_ITERATIONS; ++i) {
		result = a % b;
	}
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Modular: %f seconds\n", time_taken);
}

