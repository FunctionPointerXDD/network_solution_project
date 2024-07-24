#include <stdio.h>
#include <string.h>

#define PLUS_CODE 0
#define MINUS_CODE 1
#define ASCII_CODE_OF_ZERO  0x30
#define ASCII_CODE_OF_PLUS  0x2B
#define ASCII_CODE_OF_MINUS 0x2D

#define CONVERT_CALC_CODE_TO_ASCII_CODE(calcCode) calcCode == 0 ? ASCII_CODE_OF_PLUS : ASCII_CODE_OF_MINUS

#define MAX_INTEGER_LENGTH 100

typedef struct BigInteger
{
	char number[104];
	int len;
	char sign;
} BigInteger;

void ReadUserInputValue(BigInteger* operand1, BigInteger* operand2, char* operation);
char* converToLittleEndian(char* dest, char* source, int length);
void Sum(const BigInteger* operand1, const BigInteger* operand2, BigInteger* result);
void Sub(const BigInteger* operand1, const BigInteger* operand2, BigInteger* result);
void printBigInteger(const BigInteger* result);

int main(void)
{
	int retOfScanf = 0;
	BigInteger operand1 = { 0 };
	BigInteger operand2 = { 0 };
	char operation = 0;
	BigInteger result = { 0 };

	for (;;)
	{
		memset(&operand1, 0, sizeof(BigInteger));
		memset(&operand2, 0, sizeof(BigInteger));
		memset(&result, 0, sizeof(BigInteger));
		operation = 0;

		ReadUserInputValue(&operand1, &operand2, &operation);

		switch (operation)
		{
		case '+':
			Sum(&operand1, &operand2, &result);
			break;
		case '-':
			Sub(&operand1, &operand2, &result);
			break;
		}

		printf("%12s: ", "∞·∞˙ √‚∑¬");
		printBigInteger(&result);
		printf("\n\n");
	}
	
}

void ReadUserInputValue(BigInteger* operand1, BigInteger* operand2, char* operation)
{
	printf("ªÁøÎ¿⁄ ¿‘∑¬: \n");

	int retScanf = 0;
	char input1[MAX_INTEGER_LENGTH + 1] = { 0 };
	char input2[MAX_INTEGER_LENGTH + 1] = { 0 };

	while (1)
	{
		printf("«« ø¨ªÍ¿⁄(1): ");
		retScanf = scanf("%s", input1);
		while (getchar() != '\n');
		if (retScanf == 0)
		{
			printf("100¿⁄ ¿Ã≥ª∑Œ ¿‘∑¬«œººø‰.\n");
			continue;
		}
		break;
	}

	while (1)
	{
		printf("%12s: ", "ø¨ªÍ¿⁄");
		*operation = getchar();
		while (getchar() != '\n');

		if (*operation != '+' && *operation != '-')
		{
			printf("ø¨ªÍ¿⁄¥¬ +, - ∏∏ ¿‘∑¬ ∞°¥…«’¥œ¥Ÿ.\n");
			continue;
		}
		break;
	}

	while (1)
	{
		printf("«« ø¨ªÍ¿⁄(2): ");
		retScanf = scanf("%s", input2);
		while (getchar() != '\n');
		if (retScanf == 0)
		{
			printf("100¿⁄ ¿Ã≥ª∑Œ ¿‘∑¬«œººø‰. \n\n");
			continue;
		}
		break;
	}

	if (input1[0] == '-')
	{
		operand1->sign = MINUS_CODE;
	}
	else
	{
		operand1->sign = PLUS_CODE;
	}
	
	if (input2[0] == '-')
	{
		operand2->sign = MINUS_CODE;
	}
	else
	{
		operand2->sign = PLUS_CODE;
	}

	operand1->len = (int)(strlen(input1) - operand1->sign);
	operand2->len = (int)(strlen(input2) - operand2->sign);

	converToLittleEndian(operand1->number, input1 + operand1->sign, operand1->len);
	converToLittleEndian(operand2->number, input2 + operand2->sign, operand2->len);
}

char* converToLittleEndian(char* dest, char* source, int length)
{
	for (int i = 0; i < length; ++i)
	{
		dest[i] = source[length - 1 - i] - ASCII_CODE_OF_ZERO;
	}

	return dest;
}

void Sum(const BigInteger* operand1, const BigInteger* operand2, BigInteger* result)
{
	int sumLength = operand1->len > operand2->len ? operand1->len : operand2->len;
	char nthSum = 0;
	char carry = 0;

	BigInteger* ptrNegativeOperand = 0;
	BigInteger* ptrPositiveOperand = 0;
	BigInteger complementOfTen = { 0 };
	int zeroCheck = 0;
	
	if (operand1->sign == operand2->sign)
	{
		for (int i = 0; i < sumLength; ++i)
		{
			nthSum = operand1->number[i] + operand2->number[i] + carry;
 			result->number[i] = nthSum % 10;
			carry = nthSum / 10;
		}

		if (carry == 1)
		{
			result->number[sumLength] = 1;
		}

		result->len = sumLength + carry;
		result->sign = operand1->sign;
	}
	else
	{
		if (operand1->sign == MINUS_CODE)
		{
			ptrNegativeOperand = operand1;
			ptrPositiveOperand = operand2;
		}
		else
		{
			ptrNegativeOperand = operand2;
			ptrPositiveOperand = operand1;
		}

		carry = 1;
		for (int i = 0; i < sumLength; ++i)
		{
			nthSum = 9 - ptrNegativeOperand->number[i] + carry;
			complementOfTen.number[i] = nthSum % 10;
			carry = nthSum / 10;
		}

		carry = 0;
		for (int i = 0; i < sumLength; ++i)
		{
			nthSum = ptrPositiveOperand->number[i] + complementOfTen.number[i] + carry;
			result->number[i] = nthSum % 10;
			carry = nthSum / 10;
		}

		if (carry == 1)
		{
			result->sign = PLUS_CODE;
		}
		else
		{
			result->sign = MINUS_CODE;
			carry = 1;
			for (int i = 0; i < sumLength; ++i)
			{
				nthSum = 9 - result->number[i] + carry;
				result->number[i] = nthSum % 10;
				carry = nthSum / 10;
			}
		}
		
		for (int i = sumLength - 1; i > 0; --i)
		{
			zeroCheck += result->number[i];
			if (zeroCheck == 0)
			{
				sumLength -= 1;
			}
		}

		result->len = sumLength;
	}
}
void Sub(const BigInteger* operand1, const BigInteger* operand2, BigInteger* result)
{
	int sumLength = operand1->len > operand2->len ? operand1->len : operand2->len;
	char nthSum = 0;
	char carry = 0;

	BigInteger* ptrNegativeOperand = 0;
	BigInteger* ptrPositiveOperand = 0;
	BigInteger complementOfTen = { 0 };
	int zeroCheck = 0;

	if (operand1->sign != operand2->sign)
	{
		for (int i = 0; i < sumLength; ++i)
		{
			nthSum = operand1->number[i] + operand2->number[i] + carry;
			result->number[i] = nthSum % 10;
			carry = nthSum / 10;
		}

		if (carry == 1)
		{
			result->number[sumLength] = 1;
		}

		result->len = sumLength + carry;
		result->sign = operand1->sign;
	}
	else
	{
		if (operand1->sign == MINUS_CODE)
		{
			ptrNegativeOperand = operand1;
			ptrPositiveOperand = operand2;
		}
		else
		{
			ptrNegativeOperand = operand2;
			ptrPositiveOperand = operand1;
		}

		carry = 1;
		for (int i = 0; i < sumLength; ++i)
		{
			nthSum = 9 - ptrNegativeOperand->number[i] + carry;
			complementOfTen.number[i] = nthSum % 10;
			carry = nthSum / 10;
		}

		carry = 0;
		for (int i = 0; i < sumLength; ++i)
		{
			nthSum = ptrPositiveOperand->number[i] + complementOfTen.number[i] + carry;
			result->number[i] = nthSum % 10;
			carry = nthSum / 10;
		}

		if (carry == 1)
		{
			result->sign = PLUS_CODE;
		}
		else
		{
			result->sign = MINUS_CODE;
			carry = 1;
			for (int i = 0; i < sumLength; ++i)
			{
				nthSum = 9 - result->number[i] + carry;
				result->number[i] = nthSum % 10;
				carry = nthSum / 10;
			}
		}

		for (int i = sumLength - 1; i > 0; --i)
		{
			zeroCheck += result->number[i];
			if (zeroCheck == 0)
			{
				sumLength -= 1;
			}
		}

		result->len = sumLength;
	}
}

void printBigInteger(const BigInteger* result)
{
	if (result->sign == MINUS_CODE)
	{
		printf("%c", ASCII_CODE_OF_MINUS);
	}
	
	int resultLen = result->len;
	for (int i = resultLen - 1; i > 0; --i)
	{
		printf("%d", result->number[i]);
	}

	printf("%d", result->number[0]);
}

