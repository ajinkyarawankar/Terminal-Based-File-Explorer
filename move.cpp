#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<termios.h>

using namespace std;
int main(){

	printf("\e[1J");
	printf("\e[1;1H");
	printf("dusgiuugvbs\n");
	printf("dusgiuugvbs\n");
	printf("dusgiuugvbs\n");
	printf("dusgiuugvbs\n");
	printf("\e[1;1H");
	struct termios oldt,newt;
	tcgetattr(STDIN_FILENO,&oldt);
	char c;
	newt=oldt;
	newt.c_lflag = newt.c_lflag & ~(ICANON);
	newt.c_lflag=1;
	// newt.c_iflag=1;
	// newt.c_oflag=1;

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	
	//while(read(STDIN_FILENO,&c,1)==1 && c!=':'){
	while(1){
	//scanf("%s",&c);	
		c=getchar();
		if(c==65) cout<<"\r\x1b[1A";
		if(c==66) cout<<"\r\x1b[1B";
		//printf("%c\n",c);
		

	}
	//cout<<"You typed :";
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	//atexit(tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt));
	return 0;
}