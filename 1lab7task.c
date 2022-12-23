#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 20

int main(void) {
	int arr[SIZE];
	srand(time(NULL));

	for (int i = 0; i < SIZE; i++) {
		arr[i] = (rand() % 101);
	}

	int max = 0;
	int min = 101;
	int index_max = 0;
	int index_min = 0;

	for (int i = 0; i < SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		if (!(arr[i] < max)) {
			max = arr[i];
			index_max = i;
		}
		if (!(arr[i] > min)) {
			min = arr[i];
			index_min = i;
		}
	}
	printf("min: %d\nmax: %d\n", min, max);
	arr[index_max] = min;
	arr[index_min] = max;

	for (int i = 0; i < SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");


	return 0;
}