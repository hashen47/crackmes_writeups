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

	FILE *fp = fopen("solutions.txt", "w");
	if (fp == NULL) {
		perror("ERROR");
		return 0;
	}

	size_t len = 15; 

	for (size_t i = 0; i < len; i++) {
		for (size_t j = 0; j < len; j++) {
			for (size_t k = 0; k < len; k++) {
				for (size_t l = 0; l < len; l++) {
					int sum = buffer[i] + buffer[j] + buffer[k] + buffer[l];
					// printf("n1: %ld, n2: %ld, n3: %ld, SUM: %ld\n", buffer[i], buffer[j], buffer[k], sum);
					if (sum == 0) {
						fprintf(fp, "0 %zu 0 %zu 0 %zu 0 %zu\n", i, j, k, l);
					}
				}
			}
		}	
	}	

	fclose(fp);
	printf("DONE\n");

	return 0;
}
