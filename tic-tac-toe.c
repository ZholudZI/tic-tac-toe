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

char field[FIELD_SIDE * FIELD_SIDE];

void initField() {
	for (unsigned int i = 0; i < FIELD_SIDE * FIELD_SIDE; i++) {
		field[i] = ' ';
	}
}

void printField() {
	for (unsigned int i = 0; i < FIELD_SIDE * FIELD_SIDE; i++) {
		printf("%c", field[i]);
		if (i % FIELD_SIDE < 2) { //ToDo: Remove this condition
			printf("|");
		}
		if (i % FIELD_SIDE == 2 && i < FIELD_SIDE * FIELD_SIDE - 1) {
			printf("\n-----\n");
		}
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void playerTurn(char player_side) {
	unsigned int position = 1;
	bool is_correct = 0;
	printf("%c turn:\nEnter position: ", player_side);
	while (!is_correct) {
		scanf_s("%u", &position);
		if (position - 1 < FIELD_SIDE * FIELD_SIDE && field[position - 1] == ' ') {
			is_correct = 1;
		}
		else
		{
			printf("Uncorrect enter. Please enter position again: ");
		}
	}
	field[position - 1] = player_side;
}

void botTurn() {
	
}

int getScore() {
	switch (getGameStatus()) {
	case X_WIN:
		return -1;
		break;
	case O_WIN:
		return 1;
		break;
	case DRAW:
		return 0;
		break;
	}
}

unsigned int getGameStatus() {
	//horizontal check
	for (unsigned int row = 0; row < FIELD_SIDE; row++) {
		unsigned int x_count = 0;
		unsigned int o_count = 0;
		for (unsigned int column = 0; column < FIELD_SIDE; column++) {
			if (field[row * FIELD_SIDE + column] == 'X') {
				x_count++;
			}
			else if (field[row * FIELD_SIDE + column] == 'O') o_count++;
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
			if (field[row * FIELD_SIDE + column] == 'X') {
				x_count++;
			}
			else if (field[row * FIELD_SIDE + column] == 'O') o_count++;
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
		if (field[diagonal_pos * FIELD_SIDE + diagonal_pos] == 'X') {
			x_count++;
		} 
		else if (field[diagonal_pos * FIELD_SIDE + diagonal_pos] == 'O') o_count++;
	}
	if (x_count == FIELD_SIDE) {
		return X_WIN;
	}
	else if (o_count == FIELD_SIDE) return O_WIN;

	//antidiagonal check
	x_count = 0;
	o_count = 0;
	for (unsigned int diagonal_pos = 0; diagonal_pos < FIELD_SIDE; diagonal_pos++) {
		if (field[diagonal_pos * FIELD_SIDE + FIELD_SIDE - diagonal_pos - 1] == 'X') {
			x_count++;
		}
		else if (field[diagonal_pos * FIELD_SIDE + FIELD_SIDE - diagonal_pos - 1] == 'O') o_count++;
	}
	if (x_count == FIELD_SIDE) {
		return X_WIN;
	}
	else if (o_count == FIELD_SIDE) return O_WIN;

	//draw check
	unsigned int spaces_count = 0;
	for (unsigned int i = 0; i < FIELD_SIDE * FIELD_SIDE; i++) {
			if (field[i] == ' ') spaces_count++;
	}
	if (spaces_count == 0) return DRAW;

	return GAME_CONTINUE;
}

void printResults() {
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
}

int main() {
	initField();
	while (!getGameStatus()) {
		printField();
		playerTurn(X);
		printField();
		if (!getGameStatus()) {
			playerTurn(O);
		}
	}
	printResults();
}
