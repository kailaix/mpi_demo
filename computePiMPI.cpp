#include "mpi.h"
#include <iostream>
#include <time.h>
#include <iomanip>      // std::setprecision

using namespace std;

int main(){
	
	MPI_Init(NULL,NULL);
	int world_size, rank;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	clock_t t;
	double pi;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name,&name_len);

	printf("Processor %s rank %d out of %d\n", processor_name,
		rank, world_size);

	if(rank==0){
		t = clock();
	}

	int start = rank *100000000, end = (1+rank)*100000000;
	double sum = 0.0;
	for(int i=start; i< end;i++)
		sum += 1.0/(2.0*i+1.0) * (i%2==0?1:-1);

	if(rank==0){
		pi = sum;
		double recv_sum;
		for(int i=1;i<world_size;i++){
			MPI_Recv(&recv_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD,\
				MPI_STATUS_IGNORE);
			pi += recv_sum;
	}
}
	else{
		MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}
	
	

	if(rank==0){
		pi = 4*pi;
		int tt = clock() - t;
		printf("PI is %1.15f\nTime taken: %d\n", pi, tt);
	}
	MPI_Finalize();
	return 1;
}
