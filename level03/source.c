#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void decrypt(int value)
{
	char	str[17] = "Q}|u`sfg~sf{}|a3";

	int len = strlen(str);
	for (int i = 0; i < len; ++i)
		str[i] = str[i] ^ value;

	if (strncmp(str, "Congratulations!", 17) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
}


void test(int input, int pwd)
{
	int diff = pwd - input;

	switch (diff) // jmp diff
	{
		case 0x1:
		case 0x2:
		case 0x3:
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
		case 0x8:
		case 0x9:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15: // 21
			decrypt(diff);
			break;
		default:
			decrypt(rand());
			break;
	}
}

int	main(void)
{
	int	input;

	srand(time(0));

	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");

	printf("Password:");
	scanf("%d", &input);

	test(input, 0x1337d00d); // 322424845

	return 0;
}