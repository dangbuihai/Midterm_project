#include<stdio.h>
#include<math.h>
#include"optimize.h"
#include"calculationFunc.h"
#define vel 30
#define price 10000
int** calculateDistances(int** drivers, int** customers_initp, int** customers_finalp, int num_of_customers, int  num_of_drivers) {
	int** distances = allocate(num_of_drivers, num_of_customers);
	int distance = 0, distanceFinal = 0, distanceStart = 0;
	for (int i = 0; i < num_of_drivers; i++)
		for (int j = 0; j < num_of_customers; j++)
		{
			//for (int k = 0; k < cols; k++)
			//	distances[i][j] = distances[i][j] + abs(drivers[i][k] - customers[j][k]);
			for (int k = 0; k < 2; ++k)
			{
				distanceStart = distanceStart + abs(drivers[i][k] - customers_initp[j][k]);
				distanceFinal = distanceFinal + abs(customers_initp[j][k] - customers_finalp[j][k]);//i fix some error here
				distance = distanceFinal + distanceStart;
			}
			distances[i][j] = distance;
			distance = distanceFinal = distanceStart = 0;
		};
	return distances;
}

int** calculateTimeAndFee(int** input_mat, int** drivers, int** customers_initp, int** customers_finalp,int number_of_drivers,int num_of_cus)
{
	int numberOfTask = number_of_drivers <= num_of_cus ? num_of_cus : number_of_drivers;
	int distanceStart = 0;
	int distanceFinal = 0;
	int** ans = allocate(numberOfTask, 5);
	copyMat(ans, input_mat, numberOfTask, 2);
	//the 1st and 2nd for position for position
	for (int i = 0; i < numberOfTask; ++i) {
		for (int a = 0; a < number_of_drivers; ++a) {
			for (int b = 0; b < num_of_cus; ++b) {
				if (ans[i][0] == a && ans[i][1] == b) {
					for (int c = 0; c < 2; ++c) {
						distanceStart = distanceStart + abs(drivers[a][c] - customers_initp[b][c]);
						distanceFinal = distanceFinal + abs(customers_initp[b][c] - customers_finalp[b][c]);
					}
					ans[i][2] = (int)((distanceStart * 60) / vel);
					ans[i][3] = (int)((distanceFinal * 60) / vel);
					ans[i][4] = (int)(distanceFinal * price);
					distanceFinal = 0;
					distanceStart = 0;
				}
			}
		}
	}
	return ans;
}
