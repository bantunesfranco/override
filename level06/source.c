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

int	get_unum(void)
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

void	enable_timeout_cons(void)
{
	signal(SIGALRM, prog_timeout); // 0xe
	alarm(60); // 0x3c
}

int auth(char *login, unsigned int serial)
{
	size_t		pos = strscpn(login, "\n");
	login[pos] = '\0';
	size_t		len = strnlen(login, 0x20); // 32

	if (len <= 0x5)
		return 1;

	if (ptrace(PTRACE_TRACEME, 1, NULL, NULL) == -1); // 0xffffffff
	{
		puts("\033[32m.---------------------------.");
		puts("\033[31m| !! TAMPERING DETECTED !!  |");
		puts("\033[32m'---------------------------'");
		return 1;
	}

	int hash = (login[3]) ^ 0x1337 + 0x5eeded;

	for (size_t i = 0; i < len; i++)
	{
		if (login[i] <= 0x1f)
			return 1;
		int temp = login[i] ^ hash;
		int result = ((temp - ((unsigned int)((unsigned long long)temp * 0x88233b2b) >> 32)) >> 1) + ((unsigned int)((unsigned long long)temp * 0x88233b2b) >> 32);
		hash += temp - (result >> 10) * 0x539;
	}

	if (serial != hash)
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