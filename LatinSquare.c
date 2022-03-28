// LatinSquareGenerationC
// Max Base
// "Bradley, J. V. Complete counterbalancing of immediate sequential effects in a Latin square design. J. Amer. Statist. Ass.,.1958, 53, 525-528."
// 2022/03/29

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
	int** data;
} mymatrix;

void reverse(int *arr, int size)
{
	for(int i = 0; i < size/2; i++) {
		int temp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = temp;
	}
}

int* balance(int* members, int size, int shift)
{
	int* result = malloc(sizeof(int) * size);
	for(int i = 0, j = 0, h = 0; i < size; ++i) {
		int val, idx;
		if(i < 2 || i % 2 != 0)
			val = j++;
		else {
			val = size - h - 1;
			++h;
		}
		idx = (val + shift) % size;
		result[i] = members[idx];
	}

	if(size % 2 != 0 && shift % 2 != 0)
		reverse(result, size);
	return result;
}

int isValidSize(int n)
{
	return (n % 1 == 0) && n > 0 ;
}

void matrixInit(mymatrix *m)
{
	m->data = malloc((sizeof(int) * m->y));
	for(int i=0; i < m->y; i++) {
		m->data[i] = malloc((sizeof(int) * m->x));
		for(int j=0; j < m->x; j++) {
			m->data[i][j] = 0;
		}
	}
}

mymatrix* latinSquare(int size)
{
	mymatrix *lSquare = malloc(sizeof(mymatrix) * 1);
	lSquare->x = size;
	lSquare->y = size;
	matrixInit(lSquare);

	if(isValidSize(size)) {
		int *conditions = malloc(sizeof(int) * size);
		for(int i = 1; i<= size; i++)
			conditions[i-1] = i;
		lSquare->data[0] = conditions;
		for(int r = 0; r < size; r++) {
			if(size > 100) printf("%d/%d\n", r+1, size);
			lSquare->data[r] = balance(conditions, size, r);
		}
	}
	return lSquare;
}

void display(mymatrix *m)
{
	printf("[\n");
	for(int y=0; y < m->y; y++) {
		printf("\t[ ");
		for(int x=0; x < m->x; x++)
			printf("%d, ", m->data[y][x]);
			// printf("%d\t", m->data[y][x]);
		printf("\t],\n");
		// printf("\n");
	}
	printf("]\n");
}

void display_tab(mymatrix *m)
{
	for(int y=0; y < m->y; y++) {
		for(int x=0; x < m->x; x++)
			printf("%d\t", m->data[y][x]);
		printf("\n");
	}
}

void save(mymatrix *m)
{
	// create "latinSquare-{m->x}.csv" file
	char filename[100];
	sprintf(filename, "latinSquare-%d.csv", m->x);
	FILE *fp = fopen(filename, "w");
	if(fp == NULL) {
		printf("Error creating file!\n");
		exit(1);
	}

	// write data to file
	for(int y=0; y < m->y; y++) {
		for(int x=0; x < m->x; x++)
			fprintf(fp, "%d,", m->data[y][x]);
		fprintf(fp, "\n");
	}

	// close file
	fclose(fp);
}

int main(int argc, char** argv)
{
	int size = 10; // 1073741824;
	if(argc > 1) sscanf(argv[1], "%d", &size);

	mymatrix *m = latinSquare(size);

	if(size <= 100) display(m); // display_tab(m);

	save(m);
	return 0;
}
