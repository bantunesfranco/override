#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void	clear_stdin(void)
{
	char	c = 0;

	while (c != '\n' && c != 0xFF)
		c = getchar();
}

unsigned int	get_unum(void)
{
	unsigned int	value = 0;

	fflush(stdout);
	scanf("%u", &value);
	clear_stdin();
	return value;
}

void	prog_timeout(void)
{
	_exit(1);
}

void	decrypt(int value)
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

void	test(int input, int pwd)
{
	int	diff = pwd - input;

	if (diff > 21) // 0x15
		decrypt(rand());
	else
		decrypt(diff);
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