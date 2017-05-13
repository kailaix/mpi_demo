// This file can be used to test whether the slaves are connected to master

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
	
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name,&name_len);

	cout << "Processor "<<processor_name<<" rank "<<rank << 
	 		" out of "<<world_size<<" processors"<<endl<<flush;
	return 1;
}
