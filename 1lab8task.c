#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 255
#define MALLOC_EXC 1
#define DEBUG

typedef struct string {
	char* str;
	int c_sz;
	int r_sz;
} string;

void cr_str(string* str) {
	str->c_sz = SIZE;
	str->r_sz = 0;
	str->str = (char*)malloc(sizeof(char) * SIZE);
}

int check_size(string* str) {
	if (str->r_sz == str->c_sz - 1) {
		char* p_str = (char*)realloc(str->str, sizeof(char) * 2 * str->c_sz);
		if (p_str == NULL) {
			return MALLOC_EXC;
		}
		str->str = p_str;
		str->c_sz = 2 * str->c_sz;
	}
	return 0;
}

int is_digit(char symbol) {
	return (symbol < '0' || symbol > '9') ? 0 : 1;
}

int is_separator(char symbol) {
	if (symbol == ' ' || symbol == '\n' || symbol == '\v' || symbol == '\r') {
		return 1;
	} else {
		return 0;
	}
}

int main(void) {
	int arr[128];

	char flag;

	printf("Enter flag: ");
	scanf("%c", &flag);

	FILE* fp;
	fp = fopen("massiv.txt", "r");
	if (fp == NULL) {
		printf("Problem with File");
		return 0;
	}
	int digit = 0;
	int index = 0;
	char c;
	char _c;
	int flag_minus = 0;

	while(!feof(fp)) {
		_c = c;
		c = fgetc(fp);
		if (c == EOF && is_digit(_c)) {
			arr[index++] = digit;
			flag_minus = 0;
			break;
		}
		if (is_digit(c) && _c == '-') {
			flag_minus = 1;
		}
		if (is_digit(c)) {
			digit = digit*10+(c-'0');
		} else if (is_separator(c) && is_digit(_c)){
			if (flag_minus == 1) {
				arr[index++] = -digit;
			} else {
				arr[index++] = digit;
			}
			digit = 0;
			flag_minus = 0;
		}

	}

	int arr_out[128];
	int index_arr = 0;
	int max_differ = 0;
	int elem = 0;
	int index_elem = 0;
	int summ = 0;

	switch (flag){
		case 'a':
			index_arr = 0;
			for (int i = 1; i < index; i+=2) {
				arr_out[index_arr++] = arr[i];
			}
			break;
		case 'b':
			index_arr = 0;
			for (int i = 0; i < index; i++) {
				if (arr[i]%2 == 0) {
					arr_out[index_arr++] = arr[i];
				}
			}
			break;
		case 'c':
			printf("Digit: ");
			scanf("%d", &elem);
			index_arr = 0;
			for (int i = 0; i < index; i++) {
				if ( !((abs(arr[i] - elem)) < max_differ) ) {
					max_differ = abs(arr[i] - elem);
					index_elem = i;
				}
			}
			arr_out[index_arr++] = arr[index_elem];
			break;
		case 'd':
			printf("Digit: ");
			scanf("%d", &elem);
			index_arr = -1;
			summ = 0;
			for (int i = 0; i < index; i++) {
				if (arr[i] == elem) {
					index_elem = i;
				}
			}
			if (index_arr == -1) {
				printf("There is no such number\n");
			}
			for (int i = 0; i < index_elem; i++) {
				summ += arr[i];
			}
			arr_out[index_arr++] = summ;
			break;
		case 'e':
			printf("Digit: ");
			scanf("%d", &elem);
			index_arr = 0;
			summ = 0;
			for (int i = 0; i < index; i++) {
				if (arr[i] < elem) {
					summ += arr[i];
				}
			}
			arr_out[index_arr++] = summ;
			break;
		default:
			printf("Not correct flag\n");
			break;
	}

	for (int i = 0; i < index_arr; i++) {
		printf("%d ", arr_out[i]);
	}
	printf("\n");
	fclose(fp);

	return 0;
}