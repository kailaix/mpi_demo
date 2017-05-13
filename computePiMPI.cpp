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
	if(rank==0){
		t = clock();
	}

	int start = rank *100000000, end = (1+rank)*100000000;
	double sum = 0.0;
	for(int i=start; i< end;i++)
		sum += 1.0/(2*i+1) * (i%2==0?1:-1);

	if(rank==0){
		double pi = sum;
		double recv_sum;
		for(int i=1;i<world_size;i++){
			MPI_Recv(&recv_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD,\
				MPI_STATUS_IGNORE);
			sum += recv_sum;
	}
}
	else{
		MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}
	
	

	if(rank==0){
		double pi = 4*sum;
		cout << "PI is " <<setprecision(15) << pi << endl;
		cout << "Time taken: "<<  clock() - t <<  endl;
	}
	return 1;
}
