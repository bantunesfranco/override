#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char buffer1[100];	// 0x70
	char buffer2[48];	// 0x20
	char buffer3[100];	// 0x110
	FILE *file = NULL;
	int ac = argc;
	char **av = argv;

	memset(buffer1, 0, 96);	// 0xc -> 12*8 = 96
	memset(buffer2, 0, 40);	// 0x5 -> 5*8 = 40
	memset(buffer3, 0, 96);	// 0xc -> 12*8 = 96

	file = NULL;
	int bytes = 0;

	file = fopen("file_path", "r");
	if (file == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}

	bytes = fread(buffer2, 1, 41, file);	// 0x29 -> 41
	size_t pos = strcspn(buffer2, "\n");
	buffer2[pos] = '\0';

	if (bytes != 41) {
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}

	close(file);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\***************************************/");

	printf("--[ Username: ");
	fgets(buffer1, 100, stdin);
	pos = strcspn(buffer1, "\n");
	buffer1[pos] = '\0';

	printf("--[ Password: ");
	fgets(buffer3, 100, stdin);
	pos = strcspn(buffer3, "\n");
	buffer3[pos] = '\0';

	puts("*****************************************");
	if (strncmp(buffer2, buffer3, 41) != 0) {
		printf(buffer1);
		puts(" does not have access!");
		exit(1);
	}

	printf("Greetings, %s!\n", buffer1);
	system("/bin/sh");
	return 0;
}
