#include <stdio.h>
#include <stdbool.h>
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

void playerTurn() {
	unsigned int row = 0, column = 0;
	bool is_correct = 0;
	printf("Enter position (row, column): ");
	while (!is_correct) {
		scanf_s("%u %u", &row, &column);
		if (row < FIELD_SIDE && column < FIELD_SIDE) {
			is_correct = 1;
		}
		else
		{
			printf("Uncorrect enter. Please enter position again (row, column): ");
		}
	}
	field[row][column] = 'X';
}

int main() {
	playerTurn();
	printField();
}