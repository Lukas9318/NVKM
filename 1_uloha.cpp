#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <time.h>
using namespace std;

double Y(int n, double m);
double F(int n, double m);
double Polenie_intervalov(double a1, double a2, double accurancy);
double NON_Polenie_intervalov(double a, double right_border);

const int N = 100;
const double L = 5.0;
const double dx = L/(N-1);
double *x, *y;

int main()
{
	x = new double[N];
	y = new double[N];
	y[0]=0;
	y[1]=1;

	clock_t t0=clock();
	NON_Polenie_intervalov(0.0,50.0);
	clock_t t1=clock();

	clock_t t2=clock();
	Polenie_intervalov(5.0,7.0,0.0001);
	clock_t t3=clock();

	cout<<"NON_Polenie_intervalov takes: "<<(double)(t1-t0)/CLOCKS_PER_SEC<<" sec."<<endl;
	cout<<"Polenie_intervalov takes: "<<(double)(t3-t2)/CLOCKS_PER_SEC<<" sec."<<endl;
	cout << endl;

	system("xmgrace data.txt");
	delete[] x,y;
	return 0;
}


//// FUNCTIONS ////
double Y(int n, double m) {return ((12-10*m)*y[n-1]-m*y[n-2])/(m);}
double F(int n, double m) {return (1+m*((L/(n-1))*(L/(n-1))/12));}
double Polenie_intervalov(double a1, double a2, double accurancy)
{
	ofstream file("data.txt");
	double S=0;
	double norma = 0;
	cout << "Solution from " << a1 << " to " << a2 << " with accuracy " << accurancy;
	while((a2-a1)>accurancy)
		{	
			for(int j=2;j<N;j++) y[j] = Y(j,F(N,a2));
			double Y1 = y[N-1];
			S = (a1+a2)/2;
			for(int j=2;j<N;j++) y[j] = Y(j,F(N,S));
			double Y2 = y[N-1];
			if(Y1*Y2<0) a1=S;
			else a2=S;	
		}
	cout << " is a(E)=" << S << endl;
	for(int i=0;i<N;i++) x[i] = i*(L/(N-1)); //Rozdelenie intervalu L na N casti.
	for(int i=0;i<N;i++) norma = norma + y[i]*y[i]*dx; //Calculating of normalisation cons.
	for(int j=0;j<N;j++) file << x[j] << "	" << y[j]/sqrt(norma) << endl;
	file.close();
	return 0;	
}

double NON_Polenie_intervalov(double a, double right_border)
{
	cout << "Solutions from "<< a << " to " << right_border << endl;
	float r;
	int s = 1;
	while(a<right_border)
 	{
		for(int i=2;i<N;i++) y[i]=Y(i,F(N,a));
		if(x[N-1]=L && y[N-1]<0.005 && y[N-1]>-0.005)
			{
				if(abs(a-r)>0.1) 
					{
						cout << "n=" << s <<": " << a << endl;
						s=s+1;
					}
				r = a;
			} 
		a = a+0.0001;
	}
	cout << endl;
	return 0;
}
