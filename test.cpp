#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

// Armadillo documentation is available at:
// http://arma.sourceforge.net/docs.html

int
main(int argc, char** argv)
  {
	  
	double errcount = 0;
	for(int c=0; c<1000; c++){
		srand(c);
		 // generate data
		double data[1000][4];
		for(int i=0; i<1000; i++){
			double x1 = 2*rand()/((double)RAND_MAX)-1;
			double x2 = 2*rand()/((double)RAND_MAX)-1;
			double y = 0;
			double func = pow(x1,2.0) + pow(x2,2.0) -0.6;
			if(func<=0){
				y = -1;
			}else{
				y = 1;
			}
			data[i][0] = 1;
			data[i][1] = x1;
			data[i][2] = x2;
			data[i][3] = y;
		}

		// noise
		int ch[1000];
		for(int i=0; i<1000; i++){
			ch[i] = 0;
		}
		int count = 0;
		while(count!=100){
			int num = rand()%999;
			if(ch[num]==0){
				if(data[num][3]==-1){
					data[num][3] = 1;
				}else{
					data[num][3] = -1;
				}
				count++;
				ch[num] = 1;
			}else{

			}
		}

		mat Mdata(1000,3);
		for(int i=0; i<1000; i++){
			for(int j=0; j<3; j++){
				Mdata(i,j) = data[i][j];
			}
		}
		//pseudo inverse
		mat pseu = pinv(Mdata);
		double afterpseu[3][1000];
		for(int i=0; i<3; i++){
			for(int j=0; j<1000; j++){
				//cout<<pseu(i,j)<<endl;
				afterpseu[i][j] = pseu(i,j);
			}
		}
		//wlin
		double wlin[3]={0,0,0};
		for(int i=0; i<3; i++){
			for(int j=0; j<1000; j++){
				wlin[i] = wlin[i] + afterpseu[i][j] * data[j][3];
			}
		}
		//calculate ein
		for(int i=0; i<1000; i++){
			double answer = 0;
			double y = 0;
			answer = wlin[0]*data[i][0] + wlin[1]*data[i][1] + wlin[2]*data[i][2];
			if(answer>0){
				y = 1;
			}else{
				y = -1;
			}

			if(y==data[i][3]){

			}else{
				errcount++;
			}
		}
		
	}
		double ein = errcount/1000000;
		cout<<ein<<endl;
	



	
  system("pause");
  return 0;
  }