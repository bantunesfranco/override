#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_msg
{
	char	username[40]; // 0x28
	char	content[140]; // 0x8C
	int		len; // 0x8
} t_msg;

void secret_backdoor()
{
	char buff[128]; // 0x80
	fgets(buff, 128, stdin);
	system(buff);
}

void	set_msg(t_msg* msg)
{
	char buff[1024]; // 0x400
	memset(buff, 0, 1024); // 8 * 128 = 0x400

	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(buff, 1024, stdin);

	strncpy(msg->content, buff, msg->len);
}

void	set_username(t_msg *msg)
{
	char buff[128]; // 0x80
	memset(buff, 0, 128); // 8 * 16 = 0x80

	puts(">: Enter your username");
	printf(">>: ");
	fgets(buff, 128, stdin);

	for (int i = 0; i <= 40 && buff[i] != '\0'; ++i) { // 0x28
		msg->username[i] = buff[i];
	}

	printf(">: Welcome, %s\n", msg->username);
}

void	handle_msg(void)
{
	t_msg msg;
	memset(&msg.username, 0, 40); // 0x28
	msg.len = 140; // 0x8c
	
	set_username(&msg);
	set_msg(&msg);
	puts(">: Msg sent!");
}

int	main(void)
{
	puts("\
--------------------------------------------\n\
|   ~Welcome to l33t-m$n ~    v1337        |\n\
--------------------------------------------"
);
	handle_msg();
	return 0;
}