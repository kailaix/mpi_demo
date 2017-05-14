#include "mpi.h"
#include <iostream>
#include <time.h>
#include <iomanip>      // std::setprecision
#include <stdlib.h>     /* srand, rand */
#include <cmath>
#define SIZE 100
using namespace std;

// 6 processors
int main(){
	
	MPI_Init(NULL,NULL);
	int world_size, rank;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	clock_t t;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name,&name_len);

	printf("Processor %s rank %d out of %d\n", processor_name,
		rank, world_size);

	float norm;
	int * A;
	int * b = new int[SIZE*6] ;
	int * PA = new int[SIZE*SIZE*6];


	

	srand(123);
	if(rank==0){
		// to save space and time, we only allocate space for rank==0
		A = new int[SIZE*SIZE*6*6];
		for(unsigned int i=0;i<SIZE*SIZE*6*6;i++)
			A[i] = rand()%100;
		for(unsigned int i=0;i<6*SIZE;i++)
			b[i] = rand()%100;
	}

	// it is very important to put MPI_Scatter and MPI_Bcast outside of rank==0
	// so that every one can see.

	MPI_Scatter(A,SIZE*SIZE*6,MPI_INT,PA,SIZE*SIZE*6,MPI_INT,
			0, MPI_COMM_WORLD);
	MPI_Bcast(b,SIZE*6,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	t = MPI_Wtime();


	double sum = 0.0;
	double rowsum;
	for(unsigned int i=0;i<SIZE;i++){
		rowsum = 0.0;
		for(unsigned int j=0;j<6*SIZE;j++)
		{
			rowsum += b[j]*PA[i*6*SIZE + j];
		}
		sum += rowsum*rowsum;
	}


	if (rank!=0){
		MPI_Send(&sum,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	
	if (rank==0){
		double temp;
		for(int i=1;i<world_size;i++){
			MPI_Recv(&temp, 1, MPI_DOUBLE, i,0,MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
			sum += temp;
		}		
		sum = pow(sum,0.5);
		printf("NORM=%1.15f,TIME=%0.8f\n",sum,MPI_Wtime()-t);
}
	
	delete [] A;
	delete [] PA;
	delete [] b;

	MPI_Finalize();
	return 1;
	}

