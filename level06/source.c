#include <stdio.h>
#include <stdlib.h>

int auth(char *login, int serial)
{
	int		len = strnlen(login, 0x20); // 32
	int		i = 0;
	int		hash = 0;

	while (i < len)
	{
		hash += login[i] * (i + 1);
		i++;
	}

	if (hash == serial)
		return 1;
	return 0;
}

int	main(int argc, char **argv)
{
	int		serial = 0;
	int		i = 0;
	char	buffer[0x20]; // 32

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");

	printf("-> Enter Login: ");
	fgets(buffer, 0x20, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");

	printf("-> Enter Serial: ");
	scanf("%u", &serial);

	if (auth(buffer, serial) == 0)
	{
		puts("Invalid Password!");
		return 1;
	}

	puts("Authenticated!");
	system("/bin/sh");
	return 0;
}