#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

int check_for_int(long int number) {
	if (number < 0) {
		return -1;
	} else if (number > UINT_MAX) {
		return -1;
	}
	return 1;

}

int str_to_int(char* string, unsigned int* result) {
	char* ps = string;
	int part = 0;
	while ((*ps) != '\0') {
		if (!isdigit(*ps)) {
			return -1;
		} else {
			if (check_for_int((long)(*result)*10+((*ps)-'0')) == -1) {
				return -2;
			} else {
				(*result) = (*result)*10+((*ps)-'0');
			}
		}
		ps++;
	}
	return 0;
}

int check_flag(char flag){
	switch(flag) {
		case 'h':
			return 1;
		case 'p':
			return 1;
		case 's':
			return 1;
		case 'e':
			return 1;
		case 'a':
			return 1;
		case 'f':
			return 1;
		default:
			return 0;
	}
	return 0;
}

unsigned int degree(int number, int degr) {
	unsigned int result = 1;
	for (int i = 0; i < degr; i++) {
		if (check_for_int((long)((long)result*number)) == -1) {
			return 0;
		} else {
			result *= number;
		}
	}
	return result;
}

int main(int argc, char* argv[]) {
	unsigned int digit = 0;
	if (argc < 3) {
		printf("Wrong input \n");
		return 0;
	}
	int status_code = str_to_int(argv[1], &digit);

	if (status_code == -1) {
		printf("Wrong digit\n");
		return 0;
	} else if (status_code == -2) {
		printf("Bigger than int\n");
		return 0;
	} else if (digit == 0) {
		printf("Wrong digit\n");
		return 0;
	} else {
		printf("Digit: %u\n", digit);
	}
	if ((argv[2][0] != '-' && argv[2][0] != '/') || (!check_flag(argv[2][1]))) {
		printf("Wrong flag\n");
		return 0;
	}
	int status = 0;
	unsigned int sum = 0;
	unsigned int fct = 1;
	long int degre_1;
	switch(argv[2][1])  {
		case 'h':
			for (int i = digit; i < 100; i+=digit) {
				printf("%d ", i);
				status = 1;
			}
			if (status == 0) {
				printf("\nNo divider");
			}
			printf("\n");
			break;
		case 'p':
			if (digit == 1) {
				printf("Digit = 1\n");
				break;
			}
			if (digit == 2) {
				printf("Number is prime\n");
				break;
			}
			if (digit % 2 == 0) {
				printf("Number is composite\n");
				break;
			}
			for (int i = 3; i < (int)sqrt(digit); i+=2) {
				if (digit % i == 0) {
					printf("Number is composite\n");
					break;
				}
			}
			printf("Number is prime\n");
			break;
		case 's':
			if (digit == 0) {
				printf("0\n");
				break;
			}
			printf("Digits of number: ");
			while (digit) {
				printf("%d ", digit%10);
				digit /= 10;
			}
			printf("\n");
			break;
		case 'e':
			if (digit > 10) {
				printf("Wrong number\n");
				break;
			} else {
				for (int i = 1; i < 11; i++) {
					printf("Degree for %d -> ", i);
					for (int j = 0; j < (digit+1); j++) {
						degre_1 = degree(i, j);
						if (degre_1 == 0) {
							printf("Bigger than int\n");
							break;
						} else {
							printf("%ld ", degre_1);
						}
					}
					printf("\n");
				}
			}
			break;

		case 'a':
			for (int i = 1; i < (digit+1); i++) {
				if (check_for_int((long)((long)sum+i)) == -1) {
					printf("Bigger than int\n");
					return 0;
					break;
				} else {
					sum += i;
				}
			}
			printf("%u\n", sum);
			break;

		case 'f':
			for (int i = 1; i < (digit+1); i++) {
				if (check_for_int((long)((long)fct*i)) == -1) {
					printf("Bigger than int\n");
					return 0;
					break;
				} else {
					fct = fct * i;
				}
			}
			printf("%d! = %d\n", digit, fct);
			break;
		default:
			printf("Wrong flag");
			break;
	}


	return 0;
}