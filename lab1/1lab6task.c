#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define SIZE 255
#define MALLOC_EXC 1

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

int is_alpha(char symbol) {
	return (symbol < 'a' || symbol > 'z') ? 0 : 1; 
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

int str_in_int(string str, int base, long* result) {
	int i = 0;
	while (str.str[i] != '\0') {
		*result = (*result)*base+((is_digit(str.str[i])) ? str.str[i] - '0' : str.str[i] - 'a' + 10);
		if ((*result) > INT_MAX) {
			return 1;
		}
		i++;
	}
	return 0;
}

int main(void) {
	FILE* fp;
	FILE* fo;
	fp = fopen("file.txt", "r");
	if (fp == NULL) {
		printf("Problem with File");
		return 0;
	}
	fo = fopen("fileout.txt", "w");
	if (fo == NULL) {
		printf("Problem with File");
		fclose(fp);
		return 0;
	}

	char c;
	char _c;
	char max;
	string buf;
	cr_str(&buf);
	int flag_minus = 0;
	long result_digit = 0;
	int status_code = 0;

	while (!feof(fp)) {
		_c = c;
		c = fgetc(fp);
		if (c == EOF) {
			if ((is_alpha(_c) || is_digit(_c))) {
				max = '1';
				for (int i = 0; i < buf.r_sz; i++) {
					if (tolower(buf.str[i]) > max) {
						max = tolower(buf.str[i]);
					}
				}
				if (is_digit(max)) {
					status_code = str_in_int(buf, max - '0' + 1, &result_digit);
				} else {
					status_code = str_in_int(buf, max - 'a' + 11, &result_digit);
				}
				if (is_digit(max)) {
					if (status_code == 1) {
						fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: Overed\n", buf.str, max - '0' + 1);
					} else if (status_code == 0) {
						if (flag_minus == 1) {
							fprintf(fo, "Digit: -%s   Number system: %d   Digit in ten notation: -%ld\n", buf.str, max - '0' + 1, result_digit);
						} else {
							fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: %ld\n", buf.str, max - '0' + 1, result_digit);
						}
					}
					free(buf.str);
					cr_str(&buf);
				} else if (is_alpha(max)) {
					if (status_code == 1) {
						fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: Overed\n", buf.str, max - 'a' + 11);
					} else if (status_code == 0) {
						if (flag_minus == 1) {
							fprintf(fo, "Digit: -%s   Number system: %d   Digit in ten notation: -%ld\n", buf.str, max - 'a' + 11, result_digit);
						} else {
							fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: %ld\n", buf.str, max - 'a' + 11, result_digit);
						}
					}
					free(buf.str);
					cr_str(&buf);
				} else {
					printf("MISTAKE");
					return 0;
				}
			}
			return 0;
		}
		if ((is_alpha(c) || is_digit(c)) && _c == '-') {
			flag_minus = 1;
		}
		if (is_alpha(c) || is_digit(c)) {
			check_size(&buf);
			buf.str[buf.r_sz++] = c;
		} else if (is_separator(c) && (is_alpha(_c) || is_digit(_c))) {
			max = '1';
			for (int i = 0; i < buf.r_sz; i++) {
				if (tolower(buf.str[i]) > max) {
					max = tolower(buf.str[i]);
				}
			}
			if (is_digit(max)) {
				status_code = str_in_int(buf, max - '0' + 1, &result_digit);
			} else {
				status_code = str_in_int(buf, max - 'a' + 11, &result_digit);
			}
			if (is_digit(max)) {
				if (status_code == 1) {
					fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: Overed\n", buf.str, max - '0' + 1);
				} else if (status_code == 0) {
					if (flag_minus == 1) {
						fprintf(fo, "Digit: -%s   Number system: %d   Digit in ten notation: -%ld\n", buf.str, max - '0' + 1, result_digit);
					} else {
						fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: %ld\n", buf.str, max - '0' + 1, result_digit);
					}
				}
				free(buf.str);
				cr_str(&buf);
			} else if (is_alpha(max)) {
				if (status_code == 1) {
					fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: Overed\n", buf.str, max - 'a' + 11);
				} else if (status_code == 0) {
					if (flag_minus == 1) {
						fprintf(fo, "Digit: -%s   Number system: %d   Digit in ten notation: -%ld\n", buf.str, max - 'a' + 11, result_digit);
					} else {
						fprintf(fo, "Digit: %s   Number system: %d   Digit in ten notation: %ld\n", buf.str, max - 'a' + 11, result_digit);
					}
				}
				free(buf.str);
				cr_str(&buf);
			} else {
				printf("MISTAKE");
				return 0;
			}
			result_digit = 0;
			flag_minus = 0;
		}
	}
	fclose(fp);
	fclose(fo);
	return 0;
}