#!/bin/env python3

def calculate_hash(login: str, serial: int) -> int:
	hash: int = (ord(login[3])) ^ 0x1337 + 0x5eeded
	for c in login:
		temp: int = ord(c) ^ hash
		result: int = ((temp - ((temp * 0x88233b2b) >> 32)) >> 1) + ((temp * 0x88233b2b) >> 32)
		hash += temp - (result >> 10) * 0x539
	return hash

def find_valid_login_and_serial():
	login: str = "abcdef" # serial = 6232802
	serial: int = 0
	while True:
		if calculate_hash(login, serial) == serial:
			return login, serial
		if serial > 0xffffffff:
			raise Exception("No valid login found")
		serial += 1

def main() -> None:
	login, serial = find_valid_login_and_serial()
	print(f"Valid login: {login}, serial: {serial}")

if __name__ == "__main__":
	main()