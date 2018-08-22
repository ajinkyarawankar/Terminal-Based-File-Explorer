#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

 
int main()
{
    std::system("ls -l >test.txt"); // execute the UNIX command "ls -l >test.txt"
    std::cout << std::ifstream("test.txt").rdbuf();

 int l=0;

	char buff[BUFSIZ];

	FILE *fp = popen("ifconfig","r");

	while ( fgets( buff, BUFSIZ, fp ) != NULL ) {
	if(l<3)
	  printf("%s", buff );
l++;

	}

	pclose(fp);

	

}
