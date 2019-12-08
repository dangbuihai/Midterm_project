#include <stdio.h>
#include <stdlib.h>
#include "InOutFiles.h"
#include "calculationFunc.h"
#include "optimize.h"
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string>

int main(){

    int numOfCus=count("customer.txt");//count customers
    // printf_s("%d\n",numOfCus);
    int numOfDrv=count("driver.txt");//count drivers
    // printf_s("%d\n",numOfDrv);

    customer *c=(customer*)malloc(numOfCus*sizeof(customer));
    // printf_s("pass malloc c\n");
    // allocate memory for number of customers counted above
    driver *d=(driver*)malloc(numOfDrv*sizeof(driver));
    // printf_s("pass malloc d\n");
    //same as above
    constructC(numOfCus,c);
    // printf_s("pass construct c\n");
    constructD(numOfDrv,d);
    // printf_s("pass construct d\n");
    int **cusCipMat=allocate(numOfCus,2);//allocate memory for cip mattrix
    // printf_s("???\n");
    getCusCip(cusCipMat,c,numOfCus);//get values for cip mattrix

    int **cusCfpMat=allocate(numOfCus,2);//same
    getCusCfp(cusCfpMat,c,numOfCus);//same

    int **DrvDpMat=allocate(numOfDrv,2);//same
    getDrvDp(DrvDpMat,d,numOfDrv);//same
    // printf_s("so khach:%d\n",numOfCus);
    // for(int i=0;i<numOfCus;i++){
    //     printf_s("ten:%s\n", c[i].name);
    //     printf_s("sdt:%s\n",c[i].phone);
    //     printf_s("don tai:%d\t%d\n",c[i].cip[0],c[i].cip[1]);
    //     printf_s("tra tai:%d\t%d\n",c[i].cfp[0],c[i].cfp[1]);
    // }
    // printf_s("so tai xe: %d\n",numOfDrv);
    // for(int i=0;i<numOfDrv;i++){
    //     printf_s("ten:%s\n", d[i].name);
    //     printf_s("sdt:%s\n",d[i].phone);
    //     printf_s("bien so:%s\n", d[i].numberPlt);
    //     printf_s("vi tri hien tai:%d\t%d\n",d[i].dp[0],d[i].dp[1]);
    // }
    printMat(cusCipMat,numOfCus,2);
    printMat(cusCfpMat,numOfCus,2);
    printMat(DrvDpMat,numOfDrv,2);
    int **distances=calculateDistances(DrvDpMat,cusCipMat,cusCfpMat,numOfCus,numOfDrv);
    printMat(distances,numOfDrv,numOfCus);
    int **HungMat=hungarianAlgo(distances,numOfCus,numOfDrv);
    printMat(HungMat,numOfDrv,3);
    int **timeFeeMat=calculateTimeAndFee(HungMat,DrvDpMat,cusCipMat,cusCfpMat,numOfCus,numOfDrv);
    printMat(timeFeeMat,numOfCus,5);
    billForCus *Bills=(billForCus*)malloc(numOfCus*sizeof(billForCus));
    constructBill(numOfCus,Bills,timeFeeMat,c,d);
    printf_s("%s\n",Bills[0].cusName);      
    printBill(numOfCus,Bills);
    return 0;
}