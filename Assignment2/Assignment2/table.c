//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include "table.h"

#define COLUMN_WIDTH 10
#define LINE "-------------------------------------------------------"
#define TRUE 1
#define FALSE 0

void printMatrix(tableType **matrix, int rows, int cols) {
	int row, col, halfColWidth = COLUMN_WIDTH / 2;

	for (row = 0; row < rows; row++) {
		printf("|");
		for (col = 0; col < cols; col++) {
			// Format for center alignment
			printf("%*c%-*c|", halfColWidth, matrix[row][col], COLUMN_WIDTH - halfColWidth, ' ');
		}

		printf("\n");
	}
}

void freeMatrix(void ***matrix, int rows) {
	int row;

	// Free a matrix in case it refers to something other than NULL only.
	if (matrix && *matrix) {
		for (row = 0; row < rows; row++) {
			if ((*matrix)[row]) {
				free((*matrix)[row]);
			}
		}

		free(*matrix);
		*matrix = NULL;
	}
}

char **createMatrix(int rows, int cols) {
	int row;
	tableType **matrix;

	// Allocate first column in a matrix, which is a column of pointers, where
	// each element points to an array that holds the columns of that row.
	matrix = (tableType **)calloc(rows, sizeof(tableType*));
	if (!matrix) {
		printf("Failed to create matrix. Insufficient memory.\n");
		return NULL;
	}

	for (row = 0; row < rows; row++) {
		// Allocate the columns (array) for current row.
		*(matrix + row) = (tableType *)calloc(cols, sizeof(tableType)); // matrix[row] = malloc
		if (!(matrix[row])) {
			printf("Failed to create matrix. Insufficient memory.\n");

			// Free previously allocated rows.
			freeMatrix((void ***)&matrix, rows);

			return NULL;
		}
	}

	return matrix;
}

table *createTable(int rowsCount, int colsCount, char **colNames) {
	table *t = (table *)malloc(sizeof(table));

	if (!t) {
		printf("Failed to create table. Insufficient memory.\n");
	} else {
		t->matrix = createMatrix(rowsCount, colsCount);

		if (!t->matrix) {
			free(t);
			return NULL;
		}

		t->rows = rowsCount;
		t->cols = colsCount;
		t->lastRow = -1;
		t->colNames = colNames;
	}

	return t;
}

void freeTable(table *t) {
	if (t) {
		freeMatrix((void***)&(t->matrix), t->rows);
		t->rows = t->cols = 0;
		t->lastRow = -1;
		free(t);
	}
}

int appendRow(table *t, int *rowIndex) {
	int success = FALSE;

	if (t->lastRow < (t->rows - 1)) {
		*rowIndex = (++(t->lastRow));
		success = TRUE;
	}

	return success;
}

void insertValue(table *t, int row, int col, tableType value) {
	t->matrix[row][col] = value;
}

tableType getValue(table *t, int row, int col) {
    return t->matrix[row][col];
}

void printTable(table *t) {
	int col;

	if (!t) {
		printf("NULL\n");
	} else {
		printf("%.*s\n|", ((COLUMN_WIDTH + 1) * t->cols) + 1, LINE);

		// Table titles
		for (col = 0; col < t->cols; col++) {
			printf("%-*s|", COLUMN_WIDTH, t->colNames[col]);
		}
		printf("\n");

		// Table cells
		printMatrix(t->matrix, t->rows, t->cols);
		printf("%.*s\n", ((COLUMN_WIDTH + 1) * t->cols) + 1, LINE);
	}
}
