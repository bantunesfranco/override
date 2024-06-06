#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <fcntl.h>


void log_wrapper(FILE *log, char *msg, char *filename)
{
	char buff[0x110];
	strcpy(buff, msg);

	int len = 0xfe - strlen(buff);
	snprintf(buff+strlen(buff), len, "%s", filename);
	buff[strcspn(buff, "\n")] = '\0';

	fprintf(log, "%s\n", buff);
}

int main(int argc, char **argv)
{
	int ac = argc;
	char **av = argv;

	if (ac != 2)
		printf("Usage: %s filename\n", av[0]);

	FILE *log = fopen("./backups/.log", "w");
	if (!log)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}

	log_wrapper(log, "Starting back up: ", av[1]);

	FILE *input = fopen(av[1], "r");
	if (!input)
	{
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(1);
	}

	char buffer[0x70];
	memmove(buffer, "./backups/", strlen("./backups/"));

	int len = -1;
	len = strlen(buffer);
	len = 99 - len; // 0x69

	strncat(buffer, av[1], len);

	int fd = open(buffer, 0xc1, 0x1b0);
	if (fd == -1)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
		exit(1);
	}

	int bytesRead;
	while ((bytesRead = fgetc(input)) != EOF)
	{
		buffer[0] = bytesRead;
		write(fd, buffer, 1);
	}

	log_wrapper(log, "Finished back up ", av[1]);

	fclose(input);
	close(fd);

	return 0;
}
