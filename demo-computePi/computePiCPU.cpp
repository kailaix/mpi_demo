#include <iostream>
#include <time.h>
#include <iomanip>      // std::setprecision

using namespace std;

int main(){
	clock_t t = clock();
	double sum = 0.0;
	for(int i=300000000-1; i>= 0;i--)
		sum += 1.0/(2*i+1) * (i%2==0?1:-1);
	double pi = 4*sum;

	cout << "PI is " << setprecision(15) << pi << endl;
	cout << "Time taken: "<<  clock() - t <<  endl;
	return 1;
}
