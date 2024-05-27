#include <stdio.h>
#include <stdlib.h>

int verify_user_name(char *str)
{
	char *username = "dat_wil";

	puts("verifying username....\n");

	// if (strcmp(username, str) == 0)
	// 	return (0);
	// else
	// 	return (1);

	int i = 0;
	for (i; str[i] != '\0' && i < 7; ++i)
	{
		if (username[i] != str[i])
			return (username[i] - str[i]);
	}
	return (username[i] - str[i]);

}

int verify_pass(char *str)
{
	char *pass = "dat_wil";

	puts("verifying pass....\n");

	// if (strcmp(pass, str) == 0)
	// 	return (0);
	// else
	// 	return (1);

	int i = 0;
	for (i; str[i] != '\0' && i < 7; ++i)
	{
		if (pass[i] != str[i])
			return (pass[i] - str[i]);
	}
	return (pass[i] - str[i]);

}

int main(void)
{
	char	str[96];

	for (int i = 0; i < 16; ++i)
		str[i] = 0;
	
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(str, 256, stdin);

	if (verify_user_name(str) == 0)
	{
		puts("Enter Password: ");
		fgets(str, 100, stdin);
	
		if (verify_pass(str) == 0)
			return (0);
		else
		{
			puts("nope, incorrect password...\n");
			return (1);
		}
		return (0);
	}
	else
	{
		puts("nope, incorrect username...\n");
		return (1);
	}
}