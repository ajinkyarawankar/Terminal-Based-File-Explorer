#include"commandmode.h"
#include"opendirectory.h"
#include<iostream>
#include<string>
#include<dirent.h>
#include <unistd.h>
using namespace std;

struct dirent **namelistc;
string rootc;
void setrootc(string rt){
 rootc =rt;

}
void gotot(string p){
	int n;
	const char *root2;
	string check=rootc+p;
	root2=check.c_str();
	chdir(root2);
    n=scandir(root2,&namelistc,0,alphasort);

    free(namelistc);
    if (n < 0){

    	printf("\e[23;1H");
    	printf("\e[2K");
        printf("No such Directory");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    return;
    }
    else{
    	chdir("..");
    	printf("\e[2J");
	    printf("\e[1;1H");
	    scandirectory(root2);
    }
}