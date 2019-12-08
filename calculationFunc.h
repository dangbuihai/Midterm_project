#pragma once
/*nhom nguyen tuan trung*/

#ifndef calculationFunc
#define calculationFunc

int** calculateDistances(int** drivers, int** customers_initp, int** customers_finalp, int num_of_customers, int  num_of_drivers);
int** calculateTimeAndFee(int** input_mat, int** drivers, int** customers_initp, int** customers_finalp, int num_of_customers, int  num_of_drivers);

#endif // !calculation
