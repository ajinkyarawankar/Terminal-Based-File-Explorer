#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<termios.h>

using namespace std;
int main(){
    
    printf("\e[1J");
    printf("advnlanvnlsdn k kbs v  vj   j k\n");
    printf("advnlanvnlsdn k kbs v  vj   j k\n");
    printf("advnlanvnlsdn k kbs v  vj   j k\n");
    printf("advnlanvnlsdn k kbs v  vj   j k\n");
    printf("advnlanvnlsdn k kbs v  vj   j k\n");
    printf("advnlanvnlsdn k kbs v  vj   j k\n");
    printf("advnlanvnlsdn k kbs v  vj   j k\n");
    printf("advnlanvnlsdn k kbs v  vj   j k");

	struct termios oldt,newt;
	tcgetattr(STDIN_FILENO,&oldt);
	char c;
	newt=oldt;
	newt.c_lflag = newt.c_lflag & ~(ECHO|ICANON);
	newt.c_lflag=1;

	
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	while(read(STDIN_FILENO,&c,1)==1 && c!=':'){
		// while(1){
		// 	scanf("%s",&c);
		// //cout<<"You typed "<<c<<endl;
		if(c==65) //up
			printf("\r\x1b[1A");

			
		if(c==66)  //down
				printf("\r\x1b[1B");
	
		if(c==67); //right
		

		if(c==68) ;//left
		if(c==10)
		printf("enter\n");

		if(c==127)
		printf("backspace\n");

		// if(c==27)
		// printf("esc\n");		

	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	//atexit(tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt));
	return 0;
}
