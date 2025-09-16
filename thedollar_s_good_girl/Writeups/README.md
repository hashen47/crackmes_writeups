# Solution to good girl 

## 1. Decompilation with ghidra

```c
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
```

- so after get the decompilation i rename, and fix some variables like argv and soon, so no we are good to go, above code is runnable.
- now we analyze the code, first thing this program expect 9 command line arguments (user should submit 8, with the binary name total become 9).
- then it skip the first argv value, (because first value is binary name), then handle 2 arguments at a time, that mean 4 loop cycles happening.
- in each loop cycle get 2 number arguments, convert them to **long** integers then create a index using that two numbers. 
- then access value from buffer in that index, then sum that value to **num3** variable value.
- at the end **good girl!** msg print only if **num3** variable value is 0, otherwise print **bad girl!**.
- that mean total sum should be zero.

## 2. Implement a solution 

- so first thing we have to focus is how sum is happend, how program access buffer array value, specialy how array index is created 

```c
num3 = num3 + buffer[num2 + num1 * 4];
```

- when cracking this program, it is very hard to control with 2 variables, mainly `num1 * 4` is a very pain.
- so what we do is always set **num1** to 0, then we can control the index only using **num2** variable.
- so to do that we can pass first character always 0 in the input, like below.

```bash
./good-girl 0 1 0 2 0 3 0 4
```

- first issue is done, now we try to find what combinations can make total sum (**num3** variable value) set to zero.
- to find that we have to check different combinations of inputs.
- so total number of combinations we have check is `15 * 15 * 15 * 15` (**50625**).
- so to crack this we need 4 nested loops (4 nested loop are ok because **50625** is small).
- each loop we access one element at a time and then we add them together, if sum become zero then we know combination is right.
- to do this i created a another c file.

```c
#include <stdio.h>

int main(void)
{
	int buffer [18];
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

	size_t len = 15; 

	for (size_t i = 0; i < len; i++) {
		for (size_t j = 0; j < len; j++) {
			for (size_t k = 0; k < len; k++) {
				for (size_t l = 0; l < len; l++) {
					int sum = buffer[i] + buffer[j] + buffer[k] + buffer[l];
					if (sum == 0)
						printf("0 %zu 0 %zu 0 %zu 0 %zu\n", i, j, k, l);
				}
			}
		}	
	}	

	return 0;
}
```

- when sum become 0 i print the indexes away that we can directly use that as the input to the actual binary.
- when we run the above **crack program** we can see all solutions are print to the console one by one.
- so i used one of them.

## 3. Solve

```bash
./good-girl 0 0 0 2 0 3 0 4

# good girl! # we can see this output 
```
