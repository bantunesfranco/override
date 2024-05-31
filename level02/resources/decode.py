#!/usr/bin/env python3

def main() -> None:
	password : str = "0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d"
	password : list[bytes] = [bytes.fromhex(chunk) for chunk in password.split("0x")]

	for chunk in password:
		print(chunk.decode('ascii')[::-1], end='')
	print()

if __name__ == "__main__":
	main()