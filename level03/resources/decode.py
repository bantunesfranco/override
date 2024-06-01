#!/bin/env python3

def main() -> None:

	pwd  : str = 'Congratulations!'
	hash : str = 'Q}|u`sfg~sf{}|a3'

	for x in range(0, 22):
		res : list[int] = []
		for i in hash:
			res.append(ord(i) ^ x)
	
		password : str = ''.join(map(chr, res)) 
		if password == pwd:
			print(f'diff = {x}, password = {0x1337d00d - x}')
			break

if __name__ == '__main__':
	main()



