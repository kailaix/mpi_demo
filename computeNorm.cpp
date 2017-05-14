#include "mpi.h"
#include <iostream>
#include <time.h>
#include <iomanip>      // std::setprecision
#include <stdlib.h>     /* srand, rand */
#include <cmath>
#define SIZE 50u
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
	// printf("Allocate b\n");
	int * b = new int[SIZE*6] ;
	// printf("Allocate PA\n");
	int * PA = new int[SIZE*SIZE*6];


	// MPI_Barrier(MPI_COMM_WORLD);
	t = clock();

	srand(123);
	if(rank==0){
		// printf("Allocate A\n");
		A = new int[SIZE*SIZE*6*6];
		for(unsigned int i=0;i<SIZE*SIZE*6*6;i++)
			A[i] = rand()%100;
		for(unsigned int i=0;i<6*SIZE;i++)
			b[i] = rand()%100;
		delete [] A;
	}

	MPI_Scatter(A,SIZE*SIZE*6,MPI_INT,PA,SIZE*SIZE*6,MPI_INT,
			0, MPI_COMM_WORLD);
	MPI_Bcast(b,SIZE*6,MPI_INT,0,MPI_COMM_WORLD);

	// printf("broadcast completed for rank %d\n",rank);

	MPI_Barrier(MPI_COMM_WORLD);

	// printf("after Barrier rank %d\n",rank);

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

	// printf("compute completed for rank %d\n",rank);

	if (rank!=0){
		// printf("rank %d, sum=%1.15f\n",rank, sum);
		MPI_Send(&sum,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	
	if (rank==0){
		double temp;
		for(int i=1;i<world_size;i++){
			MPI_Recv(&temp, 1, MPI_DOUBLE, i,0,MPI_COMM_WORLD,
				MPI_STATUS_IGNORE);
			sum += temp;
			// printf("temp=%1.15f\n",temp);
		}		
		sum = pow(sum,0.5);
		printf("NORM=%1.15f,TIME=%d\n",sum,(int)(clock()-t));
}
	
	delete [] PA;
	delete [] b;

	MPI_Finalize();
	return 1;
	}
