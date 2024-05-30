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