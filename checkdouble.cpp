#include<iostream>
using namespace std;
int main(){
	int **da;
	int *db[100];
	int a=1;
	int b=2;
	da[0]=&a;
	da[1]=&b;
	
	int c=*da[0];
	int d=*da[1];
	// db=new int*[2];
	// db[0]=&c;
	// db[1]=&d;
	
		cout<<*da[0]<<endl;
	cout<<*da[1]<<endl;
	// cout<<*db[0]<<endl;
	// cout<<*db[1];

	return 0;
}