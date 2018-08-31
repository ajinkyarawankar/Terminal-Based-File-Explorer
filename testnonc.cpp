#include <stdio.h>
#include<iostream>
#include<string.h>
#include<unistd.h>
#include<termios.h>

using namespace std;
int main(int argc, char const *argv[]){

	struct termios oldt,newt;
	tcgetattr(STDIN_FILENO,&oldt);
	char c;
	newt=oldt;
	newt.c_lflag = newt.c_lflag & ~(ECHO | ICANON);
	newt.c_lflag=1;
	
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

while(1){

	c=getchar();
	printf("%d\n",c);
	if(c==10) break;
}

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);



	return 0;
}