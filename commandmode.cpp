#include"commandmode.h"
#include"opendirectory.h"
#include<iostream>
#include<string>
#include<dirent.h>
#include <unistd.h>
#include<vector>
using namespace std;

struct dirent **namelistc;
string rootc;
void setrootc(string rt){
 rootc =rt;

}

void delfile(vector<string> v){
	int size =v.size();
	if(size>1){
	string c=rootc+"/"+v[1];
	const char *r1=c.c_str();
	int status;
    status = remove(r1);
    if(status==0){
    	printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("remove success");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    }
    else{
    	printf("\e[23;1H");
    	printf("\e[2K");
    	printf("remove failed");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    }
	}
	else{
		printf("\e[23;1H");
    	printf("\e[2K");
        printf("d command invalid");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
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

void rname(vector<string> v){

	int size =v.size();
	if(size>2){
	const char *r1 =v[1].c_str();
	const char *r2 =v[2].c_str();
	int status;
    status = rename(r1,r2);
    if(status==0){
    	printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("rename success");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    }
    else{
    	printf("\e[23;1H");
    	printf("\e[2K");
    	printf("rename failed");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    }
	}
	else{
		printf("\e[23;1H");
    	printf("\e[2K");
        printf("r command invalid");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
}