#include <stdio.h>
#define FIELD_SIDE 3

char field[FIELD_SIDE][FIELD_SIDE] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

void printField() {
	for (int row = 0; row < FIELD_SIDE; row++) {
		for (int colum = 0; colum < FIELD_SIDE; colum++) {
			printf("%c", field[row][colum]);
			if (colum < 2) { //ToDo: Remove this condition
				printf("|");
			}
		}
		if (row < 2) {
			printf("\n-----\n");
		}
	}
}

int main() {
	printField();
}