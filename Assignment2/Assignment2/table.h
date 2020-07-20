//
// Created by Haim Adrian
//

#ifndef ASSIGNMENT2_TABLE_H
#define ASSIGNMENT2_TABLE_H

typedef char tableType;

typedef struct s_table {
	tableType **matrix; // The matrix we wrap
	char **colNames; // Name of each column in this table. Used for printTable
	int rows; // Amount of rows in this table
	int cols; // Amount of cols in this table
	int lastRow; // Reference to the last row in the table. Use it for dynamic (O(1)) insert.
} table;

table *createTable(int rowsCount, int colsCount, char **colNames);
void freeTable(table *t);
int appendRow(table *t, int *rowIndex);
void insertValue(table *t, int row, int col, tableType operation);
tableType getValue(table *t, int row, int col);
void printTable(table *t);

#endif //ASSIGNMENT2_TABLE_H
