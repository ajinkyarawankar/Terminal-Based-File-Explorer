#include <iostream>
#include<fstream>
using namespace std;
int main(){
ofstream myfile;
myfile.open ("./jhv/filename.txt");
if(myfile.is_open())
{

printf("if");
}
else{
printf("else");

}
	myfile.close();

}