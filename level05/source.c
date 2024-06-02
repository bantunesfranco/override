#include <stdio.h>
#include <ctype.h>

int	main()
{
	char buffer[40]; // 0x28
	fgets(buffer, 100, stdin);

	int i = 0;
	while (buffer[i] != '\0') {
		if (buffer[i] > '@' && buffer[i] <= 'Z') {
			// tolower()
			buffer[i] ^= 32; // 0x20
		}
		i++;
	}

	print(buffer);
	exit(0);
}