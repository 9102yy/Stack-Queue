#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
class Complex{
	private:
		
	public:
		double real;
		double imag;
		double value;
		Complex(){real=0;imag=0;}
		Complex(double i,double j){real = i; imag = j;}
		
		void init(double i,double j){
			real=i;imag=j;
		}
		
		void comrand(){
			real = pow(-1 ,1 + rand() % 2) * (rand() % 100);
			imag = pow(-1 ,1 + rand() % 2) * (rand() % 100);
		}
		
		double abscomplex(){
			double t;
			t = real*real + imag*imag;
			value = sqrt(t);
			return value;
		}
}; 
