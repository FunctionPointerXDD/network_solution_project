#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define arrayMaxSize 1024

char* Sub(const char* buf1, const char* buf2);
char* Add(const char* buf1, const char* buf2);
int check_digit(const char* buf);
void removeLeadingZeros(char* str);

/*ª¨º¿ ºˆ«‡ «‘ºˆ*/
char* Sub(const char* buf1, const char* buf2)
{
	char* res = 0;
	int	len1 = 0, len2 = 0, raise = 0, size = 0;
	int negative = 0; //∞·∞˙∞° ¿Ωºˆ¿œ ∞ÊøÏ 1

	res = malloc(sizeof(char) * arrayMaxSize);
	if (!res) {
		perror("malloc failed!");
		exit(1);
	}
	memset(res, 0, arrayMaxSize);

	if (isdigit(buf1[0]) && buf2[0] == '-') {
		return Add(buf1, buf2 + 1); //buf2¿« ¿Ωºˆ ∫Œ»£ ¡¶∞≈ »ƒ Add«‘ºˆ »£√‚
	}

	if (buf1[0] == '-' && buf2[0] == '-') {

		return Add(buf2+1, buf1); //¿Œºˆ∞° µ— ¥Ÿ ¿Ωºˆ¿œ ∞ÊøÏ ª¨º¿¿∫ buf1 buf2¿« ¿ßƒ°∏¶ ∫Ø∞Ê«œ∞Ì buf2¿« ¿Ωºˆ ±‚»£∏¶ æ¯æÿ µ⁄ µ°º¿«—¥Ÿ.
	}

	len1 = strlen(buf1) - 1;
	len2 = strlen(buf2) - 1;
	if (len1 < 0 || len2 < 0)
		return 0;

	// buf1¿« ¿⁄∏¥ºˆ∞° buf2∫∏¥Ÿ ¿€∞≈≥™ ∞∞¥Ÿ∏È ªÁ¿¸º¯ ∫Ò±≥
	if (len1 < len2 || (len1 == len2 && strcmp(buf1, buf2) < 0)) {
		negative = 1;
		const char* temp = buf1;
		buf1 = buf2;
		buf2 = temp;
		int tlen = len1;
		len1 = len2;
		len2 = tlen;
	}

	size = len1 + 1;
	res[size] = '\0';

	int i = size - 1;
	while (len1 >= 0 || len2 >= 0) {
		int tmp1 = 0, tmp2 = 0, num = 0;

		if (len1 >= 0)
			tmp1 = buf1[len1--] - '0';
		if (len2 >= 0)
			tmp2 = buf2[len2--] - '0';

		num = tmp1 - tmp2 - raise;
		if (num < 0) {
			num += 10;
			raise = 1;
		}
		else {
			raise = 0;
		}

		res[i--] = num + '0';
	}

	// æ’¿« ∫“« ø‰«— 0 ¡¶∞≈
	removeLeadingZeros(res);

	if (negative) {
		size = strlen(res);
		memmove(res + 1, res, size + 1); //¿Ωºˆ ∫Œ»£ ∫Ÿ¿Ã±‚ ¿ß«ÿ «—ƒ≠ π“
		res[0] = '-';
	}

	return res;
}

char* Add(const char* buf1, const char* buf2)
{
	char* res;
	int	len1 = 0, len2 = 0, raise = 0;
	int size;
	int flag = 0; //¿Œºˆ 2∞≥ ¥Ÿ ¿Ωºˆ¿œ ∞ÊøÏ 1

	res = (char*)malloc(sizeof(char) * arrayMaxSize + 1);
	if (!res)
	{
		puts("malloc failed!");
		exit(1);
	}
	memset(res, 0, arrayMaxSize);

	if (isdigit(buf1[0]) && buf2[0] == '-') {
		return Sub(buf1, buf2 + 1); //buf2¿« ¿Ωºˆ ∫Œ»£ ¡¶∞≈ »ƒ ¿¸¥ﬁ
	}

	if (buf1[0] == '-' && buf2[0] == '-') {
		memmove(buf1, buf1 + 1, strlen(buf1) + 1); //¿Ωºˆ ∫Œ»£ ¡¶∞≈∏¶ ¿ß«ÿ «—ƒ≠ ¥Á±Ë
		memmove(buf2, buf2 + 1, strlen(buf2) + 1); //¿Ωºˆ ∫Œ»£ ¡¶∞≈∏¶ ¿ß«ÿ «—ƒ≠ ¥Á±Ë
		flag = 1;
	}

	len1 = strlen(buf1) - 1;
	len2 = strlen(buf2) - 1;
	if (len1 >= len2)
		size = len1 + 1;
	else
		size = len2 + 1;

	res[size - 1] = '\0';

	int i = 0;
	while (size--)
	{
		int tmp1 = 0, tmp2 = 0, num = 0;

		if (len1 >= 0)
			tmp1 = buf1[len1--] - '0'; // ASCII TO INT
		if (len2 >= 0)
			tmp2 = buf2[len2--] - '0';

		num = tmp1 + tmp2 + raise;
		if (num >= 10)
			raise = 1;
		else
			raise = 0;

		num = num % 10;
		res[size] = (char)(num + '0');
	}

	// æ’¿« ∫“« ø‰«— 0 ¡¶∞≈
	removeLeadingZeros(res);

	if (flag == 1){ //¿Œºˆ 2∞≥ ∏µŒ ¿Ωºˆø¥¿∏π«∑Œ ø¨ªÍ »ƒ «—ƒ≠ π–∞Ì ¿Ωºˆ ∫Œ»£ ∫Ÿ¿”
		memmove(res + 1, res, strlen(res) + 1);
		res[0] = '-';
	}
	return res;
}

int check_digit(const char* buf)
{
	// √π π¯¬∞ πÆ¿⁄∞° '-'¿Œ ∞ÊøÏ ¿Ã∏¶ π´Ω√«œ∞Ì ¿Ã»ƒ πÆ¿⁄∏¶ ∞ÀªÁ
	if (*buf == '-') {
		buf++;
	}

	// ≥≤¿∫ πÆ¿⁄∞° ∏µŒ º˝¿⁄¿Œ¡ˆ ∞ÀªÁ
	while (*buf) {
		if (!isdigit(*buf++)) {
			return 0;
		}
	}

	return 1;
}


void removeLeadingZeros(char* str)
{
	int len = strlen(str);
	int i = 0;
	while (i < len - 1 && str[i] == '0') {
		i++;
	}
	if (i > 0) {
		memmove(str, str + i, len - i + 1);
	}
}

int	main(void)
{
	char* buf1 = 0;
	char* buf2 = 0;
	char* res = 0;
	char op = 0;

	buf1 = malloc(sizeof(char) * arrayMaxSize); // char * arrayMaxSize ¿⁄∏Æ «“¥Á , +1 ¿∫ ≥Œ∞™
	buf2 = malloc(sizeof(char) * arrayMaxSize); // char * arrayMaxSize ¿⁄∏Æ «“¥Á , +1 ¿∫ ≥Œ∞™
	if (!buf1 || !buf2)
	{
		puts("malloc failed!");
		exit(1);
	}

	memset(buf1, 0, arrayMaxSize);
	memset(buf2, 0, arrayMaxSize);

	fgets(buf1, arrayMaxSize, stdin);
	scanf("%c%*c", &op);
	fgets(buf2, arrayMaxSize, stdin);

	buf1[strlen(buf1) - 1] = '\0'; // ∞≥«‡ ¡¶∞≈, // √÷¥Î ¿‘∑¬ ¿⁄∏¥ºˆ: arrayMaxSize
	buf2[strlen(buf2) - 1] = '\0'; // ∞≥«‡ ¡¶∞≈, // √÷¥Î ¿‘∑¬ ¿⁄∏¥ºˆ: arrayMaxSize

	if (!check_digit(buf1) || !check_digit(buf2))
	{
		perror("invalid argument!");
		return 1;
	}

	if (op == '+')
	{
		res = Add(buf1, buf2);
	}
	else
	{
		res = Sub(buf1, buf2);
	}

	printf("Result: %s\n", res);

	free(buf1);
	free(buf2);
	free(res);

	return 0;
}

