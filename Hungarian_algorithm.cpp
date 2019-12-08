#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"optimize.h"
//allocate func
int** allocate(int number_of_row, int number_of_cols) {
	int** arr = (int**)malloc(number_of_row* sizeof(int*));
	for (int i = 0; i < number_of_row; ++i) {
		arr[i] = (int*)calloc(number_of_cols, sizeof(int));
	}
	if (arr == NULL)
	{
		printf_s("can not allocate memory...");
		exit(0);
	}
	return arr;
}
//free func
void freeAl(int** arr,int number_of_rows,int number_of_cols) {
	for (int i = 0; i < number_of_rows; ++i) {
		free(arr[i]);
	}
	free(arr);
}
//printMat
void printMat(int** arr, int num_of_rows, int num_of_cols)
{
	printf_s("\n");
	for (int i = 0; i < num_of_rows; ++i) {
		for (int j = 0; j < num_of_cols; ++j) {
			printf("%-4d", arr[i][j]);
		}
		printf("\n");
	}
}
//scanMat
int** scanMat(int** arr, int num_of_rows, int num_of_cols)
{
	for (int i = 0; i < num_of_rows; i++) {
		for (int j = 0; j < num_of_cols; j++) {
			printf_s("a[%d][%d]=", i + 1, j + 1);
			scanf_s("%d%*c", &arr[i][j]);
		}
		printf_s("\n");
	}
	return arr;
}
//copy mat
void copyMat(int** arr1, int** arr2,int numofrows,int numofcols) {
	for (int i = 0; i < numofrows; ++i) {
		for (int j = 0; j < numofcols; ++j) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

//===========================MAIN PART====================================//
//find minimum element  //errors
int findMin(int *arr, int size) {
	int min=arr[0];
	for (int i = 0; i < size; ++i) {
		min = min <= arr[i] ? min : arr[i];
	}

	return min;
}
int findMax(int*arr, int size) {
	int max = arr[0];
	for (int i = 0; i < size; ++i) {
		max = max >= arr[i] ? max : arr[i];
	}
	return max;
}
//subtract func in step 1 and 2
int** subtractMat1(int** mat, int num_of_rows, int num_of_cols) {
	int min = 0;
	int i, j, k = 0;
	int** col_arr = allocate(num_of_cols, num_of_rows);
	//subtract rows
	for (i = 0; i < num_of_rows; ++i) {
		min = findMin(mat[i], num_of_cols);
		for (j = 0; j < num_of_cols; ++j) {
			mat[i][j] =mat[i][j]-min;
		}
	}
	//subtract cols
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			col_arr[j][i] = mat[i][j];
		}
	}
	for (i = 0; i < num_of_rows; ++i) {
		min = findMin(col_arr[i], num_of_cols);
		for (j = 0; j < num_of_cols; ++j) {
			mat[j][i] = mat[j][i] - min; 
		}
	}
	
	freeAl(col_arr,num_of_cols,num_of_rows);
	return mat;
} 
//subtract func in step 4
int** subtractMat2(int** mat,int** masked_mat, int num_of_rows, int num_of_cols) {
	//1 find non_crossed element
	//2 sort in array
	//3 find min and  subtract array to min
	//4 add min to intesection of crossed line
	//5 copy to mat
	int** ans = allocate(num_of_rows, num_of_cols);
	int* temp = (int*)calloc(num_of_rows*num_of_cols, sizeof(int));
	int i, j, k=0;
	int min = 0, temp1 = 0;
//==============================================
	for (i = 0; i < num_of_rows;++i) {
		for (j = 0; j < num_of_cols; ++j) {
			//1,2
			if (masked_mat[i][j] == 0) {
				temp1=mat[i][j];
				temp[k] = temp1;
				++k;//number of non-zero element
			}
		}
	}
	min = findMin(temp, k);
	//3 subtract
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (masked_mat[i][j] == 0) {
				mat[i][j] -= min;
			}
			if (masked_mat[i][j] == 2) {
				mat[i][j] += min;
			}
		}
	}
	//5
	copyMat(ans, mat,num_of_rows,num_of_cols);
	return ans;
}

//draw minimun line through all zero elements in step 3  //fix here
int countCrossedLinesbyCol(int** mat, int num_of_rows, int num_of_cols) {
	int num = 0;
	int i, j, k = 0;
	int* colZero, * rowZero, * crossedRow, * crossedCol;
	colZero = (int*)calloc(num_of_cols, sizeof(int));
	rowZero = (int*)calloc(num_of_rows, sizeof(int));
	crossedRow = (int*)calloc(num_of_rows, sizeof(int));
	crossedCol = (int*)calloc(num_of_cols, sizeof(int));
	int** crosedMat = allocate(num_of_rows, num_of_cols);
	int** processMat = allocate(num_of_rows, num_of_cols);
	copyMat(processMat, mat, num_of_rows, num_of_cols);
	//count zero in col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (processMat[j][i] == 0) {
				colZero[i] += 1;
			}
		}
	}
	//draw line in row by assign -1 for all elements
	int temp1, temp2;
	temp1 = num_of_cols;
	temp2 = colZero[0];
	for (i = 1; i < num_of_cols; ++i) {
		temp2 = temp2 < colZero[i] ? temp2 : colZero[i];
	}//find min number of colZero
	while (temp1 > temp2) {
		for (i = 0; i < num_of_cols; ++i) {
			if (colZero[i] == temp1) {
				for (j = 0; j < num_of_cols; ++j) {
					processMat[j][i] = (-1);
					crosedMat[j][i] += 1;
				}
			}
		}
		--temp1;
	}
	//count zero in row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (processMat[i][j] == 0) {
				rowZero[i] = rowZero[i] + 1;
			}
		}
	}
	//draw line in col by assign -1 for all elements
	for (i = 0; i < num_of_rows; ++i) {
		if (rowZero[i] > 0) {
			for (j = 0; j < num_of_cols; ++j) {
				processMat[i][j] = -1;
				crosedMat[i][j] += 1;
			}
		}
	}
	//calculate number of line
		//for row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (processMat[i][j] == -1) {
				crossedRow[i] += 1;
			}
		}
	}
	//for col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (processMat[j][i] == -1) {
				crossedCol[i] += 1;
			}
		}
	}
	//sum up 2 type
	for (i = 0; i < num_of_rows; ++i) {
		if (crossedRow[i] == num_of_cols) {
			num += 1;
		}
	}
	if (num != num_of_cols) {
		for (i = 0; i < num_of_cols; ++i)
		{
			if (crossedCol[i] == num_of_rows) {
				num += 1;
			}
		}
	}
	printf_s("\ncrossed mat: \n"); printMat(processMat, num_of_cols, num_of_rows);//test
	copyMat(mat, crosedMat, num_of_rows, num_of_cols);//copy crossed mat to temp
	freeAl(crosedMat, num_of_rows, num_of_cols);
	freeAl(processMat, num_of_rows, num_of_cols);
	free(colZero); free(rowZero); free(crossedCol); free(crossedRow);
	return num;
}
int countCrossedLinesByRow(int** mat, int num_of_rows, int num_of_cols) {
	int num = 0;
	int i, j, k = 0;
	int* colZero, * rowZero, * crossedRow, * crossedCol;
	colZero = (int*)calloc(num_of_cols, sizeof(int));
	rowZero = (int*)calloc(num_of_rows, sizeof(int));
	crossedRow = (int*)calloc(num_of_rows, sizeof(int));
	crossedCol = (int*)calloc(num_of_cols, sizeof(int));
	int** crosedMat = allocate(num_of_rows, num_of_cols);
	int** processMat = allocate(num_of_rows, num_of_cols);
	copyMat(processMat, mat, num_of_rows, num_of_cols);
	//count zero in row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (processMat[i][j] == 0) {
				rowZero[i] += 1;
			}
		}
	}
	//draw line in row by assign -1 for all elements
	int temp1, temp2;
	temp1 = num_of_rows;
	temp2 = rowZero[0];
	for (i = 1; i < num_of_rows; ++i) {
		temp2 = temp2 < rowZero[i] ? temp2 : rowZero[i];
	}//find min number of rowZero
	while (temp1 > temp2) {
		for (i = 0; i < num_of_rows; ++i) {
			if (rowZero[i] == temp1) {
				for (j = 0; j < num_of_cols; ++j) {
					processMat[i][j] = (-1);
					crosedMat[i][j] += 1;
				}
			}
		}
		--temp1;
	}
	//count zero in col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (processMat[j][i] == 0) {
				colZero[i] = colZero[i] + 1;
			}
		}
	}
	//draw line in col by assign -1 for all elements
	for (i = 0; i < num_of_cols; ++i) {
		if (colZero[i] > 0) {
			for (j = 0; j < num_of_rows; ++j) {
				processMat[j][i] = -1;
				crosedMat[j][i] = crosedMat[j][i] + 1;
			}
		}
	}
	//calculate number of line
		//for row
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (processMat[i][j] == -1) {
				crossedRow[i] += 1;
			}
		}
	}
	//for col
	for (i = 0; i < num_of_cols; ++i) {
		for (j = 0; j < num_of_rows; ++j) {
			if (processMat[j][i] == -1) {
				crossedCol[i] += 1;
			}
		}
	}
	//sum up 2 type
	for (i = 0; i < num_of_rows; ++i) {
		if (crossedRow[i] == num_of_cols) {
			num += 1;
		}
	}
	if (num != num_of_cols) {
		for (i = 0; i < num_of_cols; ++i)
		{
			if (crossedCol[i] == num_of_rows) {
				num += 1;
			}
		}
	}
	printf_s("\ncrossed mat: \n"); printMat(processMat, num_of_cols, num_of_rows);//test
	copyMat(mat, crosedMat, num_of_rows, num_of_cols);//copy crossed mat to temp
	freeAl(crosedMat, num_of_rows, num_of_cols);
	freeAl(processMat, num_of_rows, num_of_cols);
	free(colZero); free(rowZero); free(crossedCol); free(crossedRow);
	return num;
}
//===========================================================================================
int** assignMat(int** assignable_mat, int num_of_rows, int num_of_cols) {
	/*make the assign point become -8(for team8) :D*/
	int** ans = allocate(num_of_rows, num_of_cols);
	int** temp1 = allocate(num_of_rows, num_of_cols);
	int** temp2 = allocate(num_of_rows, num_of_cols);
	int i, j, k, pos = 0;
	int count1 = 0, count2 = 0, minRow = 0, minCol = 0;
	int numOfTask = num_of_cols;
	int* countRow, *countCol;
	countRow = (int*)calloc(num_of_rows, sizeof(int));
	countCol = (int*)calloc(num_of_cols, sizeof(int));
	copyMat(temp1, assignable_mat, num_of_rows, num_of_cols);
	copyMat(temp2, assignable_mat, num_of_rows, num_of_cols);
	//count zero in each row and col
	for (i = 0; i < num_of_rows; ++i) {
		for (j = 0; j < num_of_cols; ++j) {
			if (ans[i][j] == 0) {
				countRow[i] += 1;
				countCol[j] += 1;
			}
		}
	}
	minRow = findMin(countRow, num_of_cols);
	minCol = findMin(countCol, num_of_rows);
	for (int y = 1; y <= numOfTask; ++y) {
		for (i = 0; i < num_of_rows; ++i) {
			if (countRow[i] == minRow) {
				for (j = pos; j < num_of_cols; ++j) {
					if (temp1[i][j] == 0) {
						++count1;
						//draw -1 line through all num of elements in 2 line intersect in temp1[i][j]
						for (k = 0; k < numOfTask; ++k) {
							temp1[i][k] = -1;
							temp1[k][j] = -1;
						}
						temp1[i][j] = -8;//assign the choosen zero by -8
						//reset the countRow array to zero to count again(after assign)
						for (int a = 0; a < num_of_rows; ++a) {
							countRow[a] = 0;
						}
						//count again
						for (int a = 0; a < num_of_rows; ++a) {
							for (int b = 0; b < num_of_cols; ++b) {
								if (temp1[a][b] == 0) {
									countRow[a] += 1;
								}
							}
						}
					}
				}
				//set the covered row'value equal numofrow+1 in oder to make the other row can be the minimum
				for (int a = 0; a < num_of_rows; ++a) {
					if (countRow[a] == 0) {
						countRow[i] = num_of_rows + 1;
					}
				}
				//find min again
				minRow = findMin(countRow, num_of_rows);
			}
		}
	}
	for (int x = 1; x <= numOfTask; ++x) {
		for (i = 0; i < num_of_cols; ++i) {
			if (countCol[i] == minCol) {
				for (j = 0; j < num_of_rows; ++j) {
					if (temp2[j][i] == 0) {
						++count2;
						//draw -1 line through all num of elements in 2 line intersect in temp2[i][j]
						for (k = 0; k < numOfTask; ++k) {
							temp2[j][k] = -1;
							temp2[k][i] = -1;
						}
						temp2[j][i] = -8;//assign the choosen zero by -8
						//reset the countCol array to zero to count again(after assign)
						for (int a = 0; a < num_of_cols; ++a) {
							countCol[a] = 0;
						}
						//count again
						for (int a = 0; a < num_of_cols; ++a) {
							for (int b = 0; b < num_of_rows; ++b) {
								if (temp2[b][a] == 0) {
									countCol[a] += 1;
								}
							}
						}
					}
				}
				//set the covered col'value equal numofcol+1 in oder to make the other col can be the minimum
				for (int a = 0; a < num_of_cols; ++a) {
					if (countCol[a] == 0) {
						countCol[i] = num_of_cols + 1;
					}
				}
				//find min again
				minCol = findMin(countCol, num_of_rows);
			}
		}
	}
	if (count1 == numOfTask) {
		copyMat(ans, temp1, num_of_rows, num_of_cols);
	}
	if (count2 == numOfTask) {
		copyMat(ans, temp2, num_of_rows, num_of_cols);
	}
	free(countRow); free(countCol); freeAl(temp1, num_of_rows, num_of_cols); freeAl(temp2, num_of_rows, num_of_cols);
	return ans;
}
/*==================================================================*/
int** makeSquare(int** mat, int row, int col) {
	//num of cus less than num of drivers
	if (row > col) {
		for (int i = 0; i < row; ++i) {
			mat[i] = (int*)realloc(mat[i], row * sizeof(int));
		}
		for (int i = 0; i < row; ++i) {
			for (int j = col; j < row; ++j) {
				mat[i][j] = 0;
			}
		}
	}
	//num of driver less than num of cus
	if (col > row) {
		mat = (int**)realloc(mat, sizeof(int*) * col);
		for (int i = row; i < col; ++i) {
			mat[i] = (int*)calloc(col , sizeof(int));
		}
	}
	return mat;
}
/*==================================================================*/

int** hungarianAlgo(int** input_mat, int num_of_rows, int num_of_cols) //fix here
{//===> prepare part
	int i, j, k = 0;
	int tmp1, tmp2;
	int numberOfCrossedLine=0;
	int temp1 = num_of_rows, temp2 = num_of_cols;
	int numTask = num_of_rows <= num_of_cols ? num_of_cols : num_of_rows;//num of task equal the bigger one
	int** processMat = allocate(num_of_rows, num_of_cols);
	int** tempMat1, ** tempMat2, ** tempMat;
	int	**preAns, ** finalResult;
	//copy to process mat
	copyMat(processMat, input_mat, num_of_rows, num_of_cols);
	//check whether the input_mat is square or not, if not make it squared
	if (num_of_rows != num_of_cols) {
		input_mat = makeSquare(input_mat, num_of_rows, num_of_cols);
		processMat = makeSquare(processMat, num_of_rows, num_of_cols);
		num_of_cols = numTask;
		num_of_rows = numTask;
	}//the num_of_rows now is same as num_of_cols
	tempMat1 = allocate(num_of_rows, num_of_cols); 
	tempMat2 = allocate(num_of_rows, num_of_cols); 
	tempMat = allocate(num_of_rows, num_of_cols);
	preAns = allocate(num_of_rows, num_of_cols);
	finalResult = allocate(numTask, 3);
//======>step1
	preAns = subtractMat1(processMat, num_of_rows,num_of_cols);
	 do {
		copyMat(tempMat1, processMat, num_of_rows, num_of_cols);
		tmp1 = countCrossedLinesByRow(tempMat1, num_of_rows, num_of_cols); printf_s("\ntmp1: %d", tmp1);
		copyMat(tempMat2, processMat, num_of_rows, num_of_cols);
		tmp2= countCrossedLinesbyCol(tempMat2, num_of_rows, num_of_cols); printf_s("\ntmp2: %d", tmp2);
		if (tmp1 <= tmp2) {
			numberOfCrossedLine = tmp1;
			copyMat(tempMat, tempMat1, num_of_rows, num_of_cols);
		}
		else{
			numberOfCrossedLine = tmp2;
			copyMat(tempMat, tempMat2, num_of_rows, num_of_cols);
		}
		printf_s("\ncrossed mat:"); printMat(tempMat, num_of_rows, num_of_cols);
		printf_s("\nnumber of crossed lines: %d\n", numberOfCrossedLine);
		if (numberOfCrossedLine != numTask) {
			processMat = subtractMat2(processMat, tempMat, num_of_rows, num_of_cols); printf_s("\nafter using sub_mat 2:\n");
			printMat(processMat, num_of_rows, num_of_cols);
		}
	} while (numberOfCrossedLine != (numTask));
		copyMat(preAns, processMat, num_of_rows, num_of_cols); printf_s("\nbefore assign:\n");
		printMat(processMat, num_of_rows, num_of_cols);
	if (numberOfCrossedLine == numTask) {
		//we can assign
		preAns = assignMat(processMat, num_of_rows, num_of_cols);
		printMat(preAns, num_of_rows, num_of_cols);
		//convert to output mat(2xn)
		printf_s("\n/==========result=========/\n");
		for (i = 0; i < num_of_rows; ++i) {
			for (j = 0; j < num_of_cols; ++j) {
				if (preAns[i][j] == -8) {
					printf_s("\ndriver %d[%d] will take customer %d[%d]", i + 1, i, j + 1, j);
					finalResult[k][0] = i;
					finalResult[k][1] = j;
					finalResult[k][2] = input_mat[i][j];
					++k;
				}
			}
		}
	}
	freeAl(tempMat, num_of_rows, num_of_cols); freeAl(tempMat1, num_of_rows, num_of_cols); freeAl(tempMat2, num_of_rows, num_of_cols);
	freeAl(processMat, num_of_rows, num_of_cols);
	freeAl(preAns, num_of_rows, num_of_cols);
	num_of_rows = temp1;
	num_of_cols = temp2;
	return finalResult;
}
