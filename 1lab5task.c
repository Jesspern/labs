#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

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

int read_str(string* str) {
	char symb;
	while ((symb = getchar()) != '\n') {
		if (symb == EOF) {
			return 2;
		}
		check_size(str);
		str->str[str->r_sz++] = symb;
	}
	str->str[str->r_sz++] = '\0';
	return 0;
}

int read_str_file(string* str, FILE* fp) {
	char c;
	while (!feof(fp)) {
		c = fgetc(fp);
		if (c == EOF) {
			check_size(str);
			str->str[str->r_sz++] = '\0';
			return 2;
		}
		if (c == '\n' || c == '\v' || c == '\r') {
			check_size(str);
			str->str[str->r_sz++] = '\0';
			return 0;
		}
		check_size(str);
		str->str[str->r_sz++] = c;
	}
	str->str[str->r_sz++] = '\0';
	return 0;
}

int write_in_file(FILE* fi, FILE* fo) {
	if (fi == NULL) {
		printf("Problem with arguments");
		return -1;
	}
	if (fo == NULL) {
		printf("Problem with arguments");
		return -1;
	}
	char c;
	while (!feof(fi)) {
		c = fgetc(fi);
		if (c == EOF) {
			return 0;
		}
		fputc(c, fo);
	}
	return 0;
}

int main(int argc, char* argv[]) {
	if (argv[1][0] != '-') {
		printf("Problem with arguments\n");
		return 0;
	}
	FILE* fo;
	fo = fopen("out.txt", "w");
	if (fo == NULL) {
		printf("Problem with arguments\n");
		return 0;
	}
	if (argv[1][1] == 'f' && argv[1][2] == 'i') {
		if (argc != 3) {
			printf("Problem with arguments\n");
			return 0;
		}
		FILE* fp;
		fp = fopen(argv[2], "r");
		if (fp == NULL) {
			printf("Problem with arguments\n");
			return 0;
		}
		string files;
		int status_code = 0;
		while (!feof(fp)) {
			cr_str(&files);
			status_code = read_str_file(&files, fp);
			FILE* fs = fopen(files.str, "r");
			printf("%s\n", files.str);
			if (fs == NULL) {
				printf("Problem with arguments\n");
				free(files.str);
				fclose(fp);
				return 0;
			}
			if ((write_in_file(fs, fo)) == -1) {
				printf("Problem with file\n");
			}
			free(files.str);
			fclose(fs);
		}
	} else if (argv[1][1] == 'c' && argv[1][2] == 'i' && argv[1][3] == 'n') {
		if (argc != 2) {
			printf("Problem with arguments\n");
			return 0;
		}
		string files;
		do {
			cr_str(&files);
			read_str(&files);
			if (files.r_sz == 0) {
				break;
			}
			FILE* fs = fopen(files.str, "r");
			if (fs == NULL) {
				printf("Problem with filename\n");
				free(files.str);
				return 0;
			}
			if ((write_in_file(fs, fo)) == -1) {
				printf("Problem with file\n");
			}
			free(files.str);


		} while (files.r_sz != 0);
		
	} else if (argv[1][1] == 'a' && argv[1][2] == 'r' && argv[1][3] == 'g') {
		for (int i = 2; i < argc; i++) {
			FILE* fs = fopen(argv[i], "r");
			if (fs == NULL) {
				printf("Problem with arguments oo\n");
				return 0;
			}
			if ((write_in_file(fs, fo)) == -1) {
				printf("Problem with file\n");
			}
			fclose(fs);
		}	
	} else {
		printf("Problem with file");
	}
	fclose(fo);
	fclose(fs);
	fclose(fp);


	return 0;
}