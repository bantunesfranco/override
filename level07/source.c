#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <signal.h>

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

int	store_number(unsigned int *data)
{
	unsigned int	index = 0;
	unsigned int	number = 0;

	printf(" Number: ");
	number = get_unum();

	printf(" Index: ");
	index = get_unum();

	if (index % 3 == 0 || (number >> 24) == 183) // 0x18 0xb7
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}

	data[index] = number;
	return 0;
}

int read_number(unsigned int *data)
{
	unsigned int	index = 0;

	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, data[index]);
	return 0;
}

int main(int argc, char **argv, char **envp)
{
	char			**av = argv;
	char			**env = envp;

	unsigned int	arr[100] = {0}; // 0x64
	char 			buff[20]; // 0x14
	int				ret = 0;

	for (int i = 0; av[i]; ++i)
		memset(av[i], 0, strlen(av[i]));
	for (int i = 0; env[i]; ++i)
		memset(env[i], 0, strlen(av[i]));
	
	puts(
"----------------------------------------------------\n\
  Welcome to wil\'s crappy number storage service!  \n\
----------------------------------------------------\n\
 Commands:                                          \n\
    store - store a number into the data storage    \n\
    read  - read a number from the data storage     \n\
    quit  - exit the program                        \n\
----------------------------------------------------\n\
   wil has reserved some storage :>                 \n\
----------------------------------------------------\n"
);

	while (1)
	{
		printf("Input command: ");
		memset(buff, 0, 20);
		fgets(buff, 20, stdin);
		buff[strlen(buff) - 1] = '\0';

		if (strncmp(buff, "store", 5) == 0)
			ret = store_number(arr);
		else if (strncmp(buff, "read", 4) == 0)
			ret = read_number(arr);
		else if (strncmp(buff, "quit", 4) == 0)
			return 0;

		if (ret == 0)
			printf(" Completed %s command successfully\n", buff);
		else
			printf(" Failed to do %s command\n", buff);
	}
	return 0;
}
