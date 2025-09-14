#include <stdio.h>
#include <stdbool.h>
#define FIELD_SIDE 3
//Player sides:
#define X 'X'
#define O 'O'
//Game statuses:
#define GAME_CONTINUE 0
#define X_WIN 1
#define O_WIN 2
#define DRAW 3

char field[FIELD_SIDE][FIELD_SIDE] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

void printField() {
	for (unsigned int row = 0; row < FIELD_SIDE; row++) {
		for (unsigned int colum = 0; colum < FIELD_SIDE; colum++) {
			printf("%c", field[row][colum]);
			if (colum < 2) { //ToDo: Remove this condition
				printf("|");
			}
		}
		if (row < 2) {
			printf("\n-----\n");
		}
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void playerTurn(char player_side) {
	unsigned int row = 0, column = 0;
	bool is_correct = 0;
	printf("%c turn:\nEnter position (row, column): ", player_side);
	while (!is_correct) {
		scanf_s("%u %u", &row, &column);
		if (row < FIELD_SIDE && column < FIELD_SIDE && field[row][column] == ' ') {
			is_correct = 1;
		}
		else
		{
			printf("Uncorrect enter. Please enter position again (row, column): ");
		}
	}
	field[row][column] = player_side;
}

void botTurn() {

}

unsigned int getGameStatus() {
	//horizontal check
	for (unsigned int row = 0; row < FIELD_SIDE; row++) {
		unsigned int x_count = 0;
		unsigned int o_count = 0;
		for (unsigned int column = 0; column < FIELD_SIDE; column++) {
			if (field[row][column] == 'X') {
				x_count++;
			}
			else if (field[row][column] == 'O') o_count++;
		}
		if (x_count == FIELD_SIDE) {
			return X_WIN;
		}
		else if (o_count == FIELD_SIDE) return O_WIN;
	}

	//vertical check
	for (unsigned int column = 0; column < FIELD_SIDE; column++) {
		unsigned int x_count = 0;
		unsigned int o_count = 0;
		for (unsigned int row = 0; row < FIELD_SIDE; row++) {
			if (field[row][column] == 'X') {
				x_count++;
			}
			else if (field[row][column] == 'O') o_count++;
		}
		if (x_count == FIELD_SIDE) {
			return X_WIN;
		}
		else if (o_count == FIELD_SIDE) return O_WIN;
	}

	//main diagonal check
	unsigned int x_count = 0;
	unsigned int o_count = 0;
	for (unsigned int diagonal_pos = 0; diagonal_pos < FIELD_SIDE; diagonal_pos++) {
		if (field[diagonal_pos][diagonal_pos] == 'X') {
			x_count++;
		} 
		else if (field[diagonal_pos][diagonal_pos] == 'O') o_count++;
	}
	if (x_count == FIELD_SIDE) {
		return X_WIN;
	}
	else if (o_count == FIELD_SIDE) return O_WIN;

	//antidiagonal check
	x_count = 0;
	o_count = 0;
	for (unsigned int diagonal_pos = 0; diagonal_pos < FIELD_SIDE; diagonal_pos++) {
		if (field[diagonal_pos][FIELD_SIDE - diagonal_pos - 1] == 'X') {
			x_count++;
		}
		else if (field[diagonal_pos][FIELD_SIDE - diagonal_pos - 1] == 'O') o_count++;
	}
	if (x_count == FIELD_SIDE) {
		return X_WIN;
	}
	else if (o_count == FIELD_SIDE) return O_WIN;

	//draw check
	unsigned int spaces_count = 0;
	for (unsigned int row = 0; row < FIELD_SIDE; row++) {
		for (unsigned int column = 0; column < FIELD_SIDE; column++)
		{
			if (field[row][column] == ' ') spaces_count++;
		}
	}
	if (spaces_count == 0) return DRAW;

	return GAME_CONTINUE;
}

void main() {
	while (!getGameStatus()) {
		printField();
		playerTurn(X);
		printField();
		if (!getGameStatus()) {
			playerTurn(O);
		}
	}
	printf("Game end! ");
	switch (getGameStatus()) {
		case X_WIN:
			printf("X Wins!");
			break;
		case O_WIN:
			printf("O Wins!");
				break;
		case DRAW:
			printf("Draw");
				break;
	}
	system("pause");
}