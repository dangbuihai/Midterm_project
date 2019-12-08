#pragma once
#ifndef optimize
#define optimize

int** hungarianAlgo(int** input_mat, int num_of_rows, int num_of_cols);
int** allocate(int number_of_row, int number_of_cols);
void freeAl(int** arr, int number_of_rows,int number_of_cols);
void printMat(int** arr, int num_of_rows, int num_of_cols);
int** scanMat(int** arr, int num_of_rows, int num_of_cols);
void copyMat(int** mat1, int** mat2, int row, int col);
#endif // !optimize.h
