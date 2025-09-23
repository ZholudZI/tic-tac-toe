#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
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
		if (i % FIELD_SIDE < FIELD_SIDE - 1) { //ToDo: Remove this condition
			printf("|");
		}
		if (i % FIELD_SIDE == FIELD_SIDE - 1 && i < FIELD_SIDE * FIELD_SIDE - 1) {
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
		scanf_s("%u", &position); //Try read char and convert it to int
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

int getScore(char field[]) {
	switch (getGameStatus(field)) {
	case X_WIN:
		return -10;
		break;
	case O_WIN:
		return 10;
		break;
	case DRAW:
		return 0;
		break;
	}
}

char invertSide(char player_side) {
	if (player_side == X) return O;
	return X;
}

unsigned int botPos() {
	unsigned int result_pos = 0;
	//creating copy of array
	char fieldCopy[FIELD_SIDE * FIELD_SIDE];
	for (unsigned int i = 0; i < FIELD_SIDE * FIELD_SIDE; i++) {
		fieldCopy[i] = field[i];
	}

	int max_score = INT_MIN;
	for (unsigned int pos = 0; pos < FIELD_SIDE * FIELD_SIDE; pos++) {
		if (fieldCopy[pos] == ' ') {
			int thisScore = checkPos(fieldCopy, pos, O);
			if (max_score < thisScore) {
				max_score = thisScore;
				result_pos = pos;
			}
		}
	}
	return result_pos;
}

int checkPos(char field[], unsigned int pos, char player_side) {
	char fieldCopy[FIELD_SIDE * FIELD_SIDE];
	for (unsigned int i = 0; i < FIELD_SIDE * FIELD_SIDE; i++) {
		fieldCopy[i] = field[i];
	}
	fieldCopy[pos] = player_side;

	int result_score = 0;
	if (getGameStatus(field) == GAME_CONTINUE) {
		for (unsigned int pos = 0; pos < FIELD_SIDE * FIELD_SIDE; pos++) {
			if (fieldCopy[pos] == ' ') {
				result_score += checkPos(fieldCopy, pos, invertSide(player_side));
			}
		}
		return result_score;
	}
	return getScore(fieldCopy);
}

unsigned int getGameStatus(char field[]) {
	//horizontal check
	for (unsigned int row = 0; row < FIELD_SIDE; row++) {
		unsigned int x_count = 0;
		unsigned int o_count = 0;
		for (unsigned int column = 0; column < FIELD_SIDE; column++) {
			if (field[row * FIELD_SIDE + column] == X) {
				x_count++;
			}
			else if (field[row * FIELD_SIDE + column] == O) o_count++;
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
			if (field[row * FIELD_SIDE + column] == X) {
				x_count++;
			}
			else if (field[row * FIELD_SIDE + column] == O) o_count++;
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
		if (field[diagonal_pos * FIELD_SIDE + diagonal_pos] == X) {
			x_count++;
		} 
		else if (field[diagonal_pos * FIELD_SIDE + diagonal_pos] == O) o_count++;
	}
	if (x_count == FIELD_SIDE) {
		return X_WIN;
	}
	else if (o_count == FIELD_SIDE) return O_WIN;

	//antidiagonal check
	x_count = 0;
	o_count = 0;
	for (unsigned int diagonal_pos = 0; diagonal_pos < FIELD_SIDE; diagonal_pos++) {
		if (field[diagonal_pos * FIELD_SIDE + FIELD_SIDE - diagonal_pos - 1] == X) {
			x_count++;
		}
		else if (field[diagonal_pos * FIELD_SIDE + FIELD_SIDE - diagonal_pos - 1] == O) o_count++;
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
	switch (getGameStatus(field)) {
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
	while (!getGameStatus(field)) {
		printField();
		playerTurn(X);
		printField();
		if (!getGameStatus(field)) {
			printf("%d ", botPos() + 1);
			playerTurn(O);
		}
	}
	printResults();
}
