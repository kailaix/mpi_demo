#include <iostream>
#include <time.h>
#include <iomanip>      // std::setprecision
#include <stdlib.h>     /* srand, rand */
#include <cmath>
#include "stdio.h"
#define SIZE 100
using namespace std;

// 6 processors
int main(){
	
	
	int	*A = new int[SIZE*SIZE*6*6];
	int *b = new int[6*SIZE];
	srand(123);
	for(unsigned int i=0;i<SIZE*SIZE*6*6;i++)
		A[i] = rand()%100;
	for(unsigned int i=0;i<6*SIZE;i++)
		b[i] = rand()%100;

	clock_t t = clock();
	double sum = 0.0;
	double rowsum;
	for(unsigned int i=0;i<6*SIZE;i++){
		rowsum = 0.0;
		for(unsigned int j=0;j<6*SIZE;j++)
		{
			rowsum += b[j]*A[i*6*SIZE + j];
		}
		sum += rowsum*rowsum;
	}

	// printf("compute completed for rank %d\n",rank);
	printf("NORM=%1.15f,TIME=%0.8f\n",pow(sum,0.5),(float)(clock()-t)/CLOCKS_PER_SEC);

	return 1;
}
