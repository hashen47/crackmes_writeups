// ISSUE LINK: 
// https://crackmes.one/crackme/6896d8398fac2855fe6fb463

#include <stdio.h>

int main(int argc, char **argv)
{
	long num1;
	long num2;
	int num3;
	int return_code;
	char **current_argv;
	char **next_argv;
	int buffer [18];

	if (argc == 9) {
		num3 = 0;
		buffer[0]  = 11;
		buffer[1]  = 13;
		buffer[2]  = 23;
		buffer[3]  = -7;
		buffer[4]  = -27;
		buffer[5]  = 107;
		buffer[6]  = -53;
		buffer[7]  = 41;
		buffer[8]  = 67;
		buffer[9]  = -51;
		buffer[10] = 253;
		buffer[11] = -143;
		buffer[12] = -119;
		buffer[13] = 101;
		buffer[14] = 401;
		buffer[15] = -391;

		current_argv = argv + 1;

		do {
			next_argv = current_argv + 2;
			num1 = strtol(*current_argv, NULL, 10);
			num2 = strtol(current_argv[1], NULL, 10);
			num3 = num3 + buffer[num2 + num1 * 4];
			current_argv = next_argv;
		} while ((argv + 9) != next_argv);

		if (num3 == 0) {
			puts("good girl!");
		}
		else {
			puts("bad girl!");
		}
		return_code = 0;

	}
	else {
		puts("bad girl!");
		return_code = 1;
	}

	return return_code;
}
