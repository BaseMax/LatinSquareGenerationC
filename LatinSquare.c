#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
	int** data;
} mymatrix;

void reverse(int arr[], int size)
{
    for (int i = 0; i < size/2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

int* balancedLatinSquare(int* members, int size, int participantId) {
	int* result = malloc(sizeof(int) * size + 1);
	// Based on "Bradley, J. V. Complete counterbalancing of immediate sequential effects in a Latin square design. J. Amer. Statist. Ass.,.1958, 53, 525-528."
	for(int i = 0, j = 0, h = 0; i < size; ++i) {
		int val = 0;
		if (i < 2 || i % 2 != 0)
			val = j++;
		else {
			val = size - h - 1;
			++h;
		}

		int idx = (val + participantId) % size;
		result[i] = members[idx];
	}

	if(size % 2 != 0 && participantId % 2 != 0)
		reverse(result);
	return result;
}

// int indexOf(int* arr, int size, int what)
// {
// 	printf("indexOf\n");
// 	for(int i = 0; i < size; i++) {
// 		if(arr[i] == what) return i;
// 	}
// 	return -1;
// }

// int* splice(int* arr, int i, int j)
// {
// 	printf("splice\n");
// 	return arr;
// }

// void _removeItemFromArrayByValue(int* arr, int what, int size) {
// 	printf("_removeItemFromArrayByValue\n");
// 	int ax;
// 	while ((ax = indexOf(arr, size, what)) != -1) {
// 		arr = splice(arr, ax, 1); // arr.splice(ax, 1);
// 	}
// 	// return arr;
// }

// void _shuffleArr(int* arr, int size)
// {
// 	printf("_shuffleArr\n");
// 	int n1, n2, tmp;

// 	n1 = rand() % (size);
// 	n2 = rand() % (size);

// 	while (n1 == n2) 
// 		n2 = rand() % (size);
 
// 	tmp = *(arr + n1);
// 	*(arr + n1) = *(arr + n2);
// 	*(arr + n2) = tmp;
// }

int isValidSize(int n) {
	printf("isValidSize\n");
	return (n % 1 == 0) && n > 0 ;
}

void matrixInit(mymatrix *m)
{
	printf("matrixInit\n");
	m->data = malloc((sizeof(int) * m->y) + 1);
	for(int i=0; i < m->y; i++) {
		m->data[i] = malloc((sizeof(int) * m->x) + 1);
		for(int j=0; j < m->x; j++) {
			m->data[i][j] = 0;
		}
	}
}

mymatrix* generateDefaultLatinSquare(int size)
{
	printf("generateDefaultLatinSquare\n");
	mymatrix *lSquare = malloc(sizeof(mymatrix) * 1 + 1);
	lSquare->x = size;
	lSquare->y = size;
	matrixInit(lSquare);

	if(isValidSize(size)) {
		int *conditions = malloc(sizeof(int) * size + 1);
		for(int i = 1; i<= size; i++) {
			conditions[i-1] = i;
			lSquare->data[0][i] = i;
		}
		for(int r = 1; r < size; r++) {
			lSquare->data[r] = balancedLatinSquare(conditions, size, r);
		}
	}
	return lSquare;
}

void display(mymatrix *m)
{
	printf("[\n");
	for(int y=0; y < m->y; y++) {
		printf("\t[ ");
		for(int x=0; x < m->x; x++) {
			printf("%d, ", m->data[y][x]);
		}
		printf("\t],\n");
	}
	printf("]\n");
}

int main()
{
	srand(time(NULL));
	const int SIZE = 4; // 10;
	mymatrix *m = generateDefaultLatinSquare(SIZE);
	display(m);
	// [
	//   [ 3,  6, 2, 1, 7, 5, 10, 4, 9, 8 ],
	//   [ 4, 8, 9, 7, 5, 10, 2, 6, 3, 1 ],
	//   [ 7, 9, 4, 8,  1, 6, 3, 5, 2, 10 ],
	//   [ 6, 7, 1,  5, 8, 9, 4, 2, 10, 3 ],
	//   [ 10, 3, 6, 2, 9,  4, 8, 1, 5, 7 ],
	//   [ 2, 10, 8, 3, 4, 7,  1, 9, 6, 5 ],
	//   [ 9, 5,  7, 4, 3, 8, 6, 10, 1, 2 ],
	//   [ 5, 2, 3, 10, 6, 1, 7, 8,  4, 9 ],
	//   [ 8, 1, 5, 6, 10, 2, 9, 3, 7,  4 ],
	//   [ 1, 4, 10, 9, 2, 3, 5,  7, 8, 6 ]
	// ]
	return 0;
}
