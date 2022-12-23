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

int read_to_space(string str, string* result, int* index) {
	int i = 0;
	while (str.str[*index] != '\0') {
		if (str.str[*index] == ' ') {
			check_size(result);
			result->str[i++] = '\0';
			(*index)++;
			return 0;
		}
		check_size(result);
		result->str[i] = str.str[*index];
		(*index)++;
		i++;
	}
	return 0;
}


int main(void) {
	FILE* fp;
	FILE* fs;
	fp = fopen("filefor4.txt", "r");
	if (fp == NULL) {
		printf("Problem with file");
		return 0;
	}
	fs = fopen("filefor4_1.txt", "w");
	if (fs == NULL) {
		printf("Problem with file");
		fclose(fp);
		return 0;
	}

	string str;
	string column_1;
	string column_2;
	string column_3;
	int status_code = 0;

	while(!feof(fp)) {
		int index = 0;
		cr_str(&str);
		cr_str(&column_1);
		cr_str(&column_2);
		cr_str(&column_3);
		read_str_file(&str, fp);
		read_to_space(str, &column_1, &index);
		read_to_space(str, &column_2, &index);
		read_to_space(str, &column_3, &index);
		fprintf(fs, "%s %s %s\n", column_3.str, column_1.str, column_2.str);
		free(column_1.str);
		free(column_2.str);
		free(column_3.str);

	}	
	fclose(fp);
	fclose(fs);
	return 0;
}