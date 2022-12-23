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

typedef struct massiv {
	int* mass;
	int c_sz;
	int r_sz;
} massiv;

void cr_str(string* str) {
	str->c_sz = SIZE;
	str->r_sz = 0;
	str->str = (char*)malloc(sizeof(char) * SIZE);
}

void cr_mass(massiv* arr) {
	arr->c_sz = SIZE;
	arr->r_sz = 0;
	arr->mass = (int*)malloc(sizeof(int) * SIZE);
}

int check_size_mass(massiv* arr) {
	if (arr->r_sz == arr->c_sz - 1) {
		int* p_str = (int*)realloc(arr->mass, sizeof(int) * 2 * arr->c_sz);
		if (p_str == NULL) {
			return MALLOC_EXC;
		}
		arr->mass = p_str;
		arr->c_sz = 2 * arr->c_sz;
	}
	return 0;
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

int read_str(string* str) {
	char c;
	scanf("%c", &c);
	while (c != '\n') {
		check_size(str);
		str->str[str->r_sz++] = c;
		scanf("%c", &c);
		if (c == '\n') {
			check_size(str);
			str->str[str->r_sz++] = '\0';	
			return 0;
		}
	}
	return 0;
}

int is_digit(char symbol) {
	return (symbol < '0' || symbol > '9') ? 0 : 1;
}

int is_alpha(char symbol) {
	return (symbol < 'A' || symbol > 'Z') ? 0 : 1; 
}

int check_str(string str, int notation) {
	if (notation < 11) {
		for (int i = 0; i < (str.r_sz-1); i++) {
			if (!(is_digit(str.str[i])) || (str.str[i] - '0') >= notation) {
				return 2;
			}
		}
		return 0;
	} else if (notation > 10 && notation < 33) {
		for (int i = 0; i < (str.r_sz-1); i++) {
			if (!(is_alpha(str.str[i])) && !(is_digit(str.str[i]))) {
				return 2;
			} else if (is_alpha(str.str[i])) {
				if ((str.str[i] - 'A' + 10) >= notation) {
					return 2;
				}
			}
		}
		return 0;
	} else {
		return 1;
	}
	return 0;
}

int str_in_int(string str, int base, int* result) {
	int i = 0;
	while (str.str[i] != '\0') {
		*result = (*result)*base+((is_digit(str.str[i])) ? str.str[i] - '0' : str.str[i] - 'A' + 10);
		i++;
	}
	return 0;
}

int length_of_notation(int number, int base) {
	int count = 0;
	while (number) {
		number /= base;
		count++;
	}
	return count;

}

int int_in_str(string* str, int base, int number) {
	if (base < 2 || base > 36) {
		return 1;
	}
	int r;
	int length = length_of_notation(number, base);
	if (length > str->c_sz-1) {
		char* p_str = (char*)realloc(str->str, sizeof(char) * length + 1);
		if (p_str == NULL) {
			return MALLOC_EXC;
		}
		str->str = p_str;
		str->c_sz = length + 1;
	}
	str->str[length--] = '\0';
	while (number) {
		if (length == -1) {
			return 0;
		}
		r = number%base;
		str->str[length--] = ((r > 9) ? r - 10 + 'A' : r + '0');
		number /= base;
	}
	return 0;

}


int main(void) {
	int notation = 0;
	char rubbish;

	printf("Notation: ");
	scanf("%d", &notation);
	scanf("%c", &rubbish);

	if (notation < 2 || notation > 32) {
		printf("Wrong notation\n");
		return 0;
	}

	string str;
	massiv arr;
	cr_mass(&arr);
	int status_code = 0;
	int result = 0;
	while (1) {
		cr_str(&str);
		read_str(&str);
		result = 0;
		if (str.str[0] == 'S' && str.str[1] == 't' && str.str[2] == 'o' && str.str[3] == 'p' && str.str[4] == '\0') {
			break;
		}
		status_code = check_str(str, notation);
		if (status_code == 1) {
			printf("Wrong notation\n");
		} else if (status_code == 2) {
			printf("Wrong number\n");
		} else if (status_code == 0) {
			str_in_int(str, notation, &result);
			check_size_mass(&arr);
			arr.mass[arr.r_sz++] = result;
		}
		free(str.str);
	}
	int max = -1;
	for (int i = 0; i < arr.r_sz; i++) {
		if (abs(arr.mass[i]) > max) {
			max = arr.mass[i];
		}
	}
	printf("%d\n", max);
	string result_num;
	
	for (int i = 9; i <= 36; i+=9) {
		cr_str(&result_num);
		status_code = int_in_str(&result_num, i, max);
		if (status_code == 1) {
			printf("Wrong notation\n");
		}
		printf("Max in 9: %s\n", result_num.str);
		free(result_num.str);
	}

	return 0;
}