#include <stdio.h>
#include<iostream>
#include<string.h>
#include<unistd.h>
#include"opendirectory.h"
#include"commandmode.h"
#include<termios.h>
#include<sys/wait.h>
#include <sstream>
#include<vector>
#include<map>
using namespace std;
int main(int argc, char const *argv[]){

	map<string,int> m;
	m[":goto"]=0;

	const char *root;
	char *current_root;
	int lowerlimit,upperlimit,currentlimit=19,current=0;
	if(argc==1)
	    root=realpath(".",NULL);
	else
		root=realpath(argv[1],NULL);

	setroot(root);
	setrootc(root);
	printf("\e[1J");
	printf("\e[1;1H");

	struct termios oldt,newt;
	tcgetattr(STDIN_FILENO,&oldt);
	char c;
	string s;
	newt=oldt;
	newt.c_lflag = newt.c_lflag & ~(ICANON);
	newt.c_lflag=1;
	



	scanDirectory(root,0);

	printf("\e[1;1H");

	lowerlimit=getlowerlimit();
	upperlimit=getupperlimit();
	currentlimit=currentlimit<upperlimit?currentlimit:upperlimit;
NONCANONICAL:
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	printf("\e[1;1H");
	while(1){
	//scanf("%s",&c);	
		c=getchar();

        //right arrow
		if(c==67){
			goright();
			lowerlimit=getlowerlimit();
			upperlimit=getupperlimit();
			current=lowerlimit;
		}
        //left arrow
		if(c==68){
			goleft();
			lowerlimit=getlowerlimit();
			upperlimit=getupperlimit();
			current=lowerlimit;
		}

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
			else{
				
				openFile(current);
				sleep(1);
				printf("\e[1;1H");
				current=lowerlimit;
			}
		}
		
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


		if(c==104){
			printf("\e[2J");
	        printf("\e[1;1H");
			gohome();
			printf("\e[1;1H");
			lowerlimit=getlowerlimit();
			upperlimit=getupperlimit();
			currentlimit=19;
			currentlimit=currentlimit<upperlimit?currentlimit:upperlimit;
			current=0;
		}

		if(c==':') {
			printf("\e[22;1H");
			printf("\e[2K");
			printf(":");
			break;
		}

	}


	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);


//canonical mode 
	while(1){

		string command;
		getline(cin,s);
		if(s.compare("exit")==0){
			printf("\e[25;1H");
			break;
		}
    
    string word;
    vector<string> commands;
    stringstream iss(s);
    while (iss >> word)
        commands.push_back(word);
    int size=commands.size();
    if(size>1){
    	string cs=commands[0];
    	switch(m[cs]){
    		case 0:
    					gotot(commands[1]);
    					lowerlimit=getlowerlimit();
						upperlimit=getupperlimit();
						currentlimit=19;
						currentlimit=currentlimit<upperlimit?currentlimit:upperlimit;
						current=lowerlimit;
						goto NONCANONICAL;
    	}
    }
    else{
    	printf("\e[23;1H");
    	printf("\e[2K");
    	printf("invalid command");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    }
		printf("\e[22;1H");
		printf("\e[2K");
		printf(":");

	}

}