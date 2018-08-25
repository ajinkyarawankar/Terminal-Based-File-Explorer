#include <stdio.h>
#include<iostream>
#include<string.h>
#include<unistd.h>
#include"opendirectory.h"
#include<termios.h>

using namespace std;
int main(int argc, char const *argv[]){

	const char *root;
//	char *current_root;
	int lowerlimit,upperlimit,currentlimit=19,current=0;
	if(argc==1)
	    root=".";
	else
		root= argv[1];
	
	printf("\e[1J");
	printf("\e[1;1H");
	struct termios oldt,newt;
	tcgetattr(STDIN_FILENO,&oldt);
	char c;
	newt=oldt;
	newt.c_lflag = newt.c_lflag & ~(ICANON);
	newt.c_lflag=1;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);



	scanDirectory(root,0);

	printf("\e[1;1H");

	lowerlimit=getlowerlimit();
	upperlimit=getupperlimit();
	currentlimit=currentlimit<upperlimit?currentlimit:upperlimit;

	while(1){
	//scanf("%s",&c);	
		c=getchar();
		//up arrow
		if(c==65) {
			if(current!=lowerlimit){
				cout<<"\r\x1b[1A";
				current=current-1;
			}
			else{
				if(lowerlimit!=0){
					//move one up
					lowerlimit--;
					currentlimit--;
					current--;
					printf("\e[2J");
	        		printf("\e[1;1H");
					printCustomDirectory(lowerlimit,currentlimit);
					printf("\e[1;1H");
					

				}
			}
	    }
		//down arrow
		if(c==66){
			if(current!=currentlimit) {
				cout<<"\r\x1b[1B";
				current=current+1;
			}
			else{
				if(currentlimit<upperlimit){
					//move one down
					lowerlimit++;
					currentlimit++;
					current++;
					printf("\e[2J");
	        		printf("\e[1;1H");
					printCustomDirectory(lowerlimit,currentlimit);
					//printf("\e[1;1H");
					printf("\r\x1b[1A");
					
		
				}
			}
		} 
		if(c==10){
			if(checkDirectory(current)){
			printf("\e[2J");
	        printf("\e[1;1H");
			scanDirectory(current);
			lowerlimit=getlowerlimit();
	        upperlimit=getupperlimit();
	        current=0;
	        printf("\e[1;1H");
	        currentlimit=19;
	        currentlimit=currentlimit<upperlimit?currentlimit:upperlimit;
			//printf("%d",current);
			}
		}
		//printf("%c\n",c);
		if(c==127){
			printf("\e[2J");
	        printf("\e[1;1H");
			scanDirectory(1);
			lowerlimit=getlowerlimit();
	        upperlimit=getupperlimit();
	        current=0;
	        printf("\e[1;1H");
	        currentlimit=19;
	        currentlimit=currentlimit<upperlimit?currentlimit:upperlimit;
		}
		if(c==':') {
			printf("\n");
			break;
		}

	}


	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

}