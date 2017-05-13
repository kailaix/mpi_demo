mpic++ computePiMPI.cpp -o computePiMPI
g++ computePiCPU.cpp
./update

sleep 5
./computePiCPU.cpp

mpirun -n 3 -f host_file ./computePiMPI
