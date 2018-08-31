#include"commandmode.h"
#include"opendirectory.h"
#include<iostream>
#include<string>
#include<dirent.h>
#include <unistd.h>
#include<vector>
#include<sys/stat.h>
#include<fstream>
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

void addfooter(){

		printf("\e[25;1H");
    	printf("\e[2K");
        printf("Made by Ajinkya");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");


}

void create_dir(vector<string> v){
	int size =v.size();
	if(size>2){
	// const char *r1 =v[1].c_str();
	// const char *r2 =v[2].c_str();
	//const char *r1 =v[1].c_str();
	string a2=v[2];
	int l=a2.length();
	//const char *r2 =(a2.substr(2,l-2)).c_str();
	char c=a2[0];
	if(c=='~')
		a2=rootc+"/"+a2.substr(1,l-1)+"/"+v[1];
	else if(c=='.')
		{
			char* path=realpath(".",NULL);
			a2=path;
			a2=a2+"/"+v[1];
		}
	else{
		goto END;
	}
	const char* r3=a2.c_str();

	int status;
    status = mkdir(r3,0777);
    if(status==0){
    	printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("create_dir success");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    }
    else{
    	printf("\e[23;1H");
    	printf("\e[2K");
    	printf("create_dir failed");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    }
	}
	else{
		END:
		printf("\e[23;1H");
    	printf("\e[2K");
        printf("r command invalid");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
}

void create_file(vector<string> v){
	int size =v.size();
	if(size>2){
	string a2=v[2];
	int l=a2.length();
	char c=a2[0];
	if(c=='~')
		a2=rootc+"/"+a2.substr(1,l-1)+"/"+v[1];
	else if(c=='.')
		{
			char* path=realpath(".",NULL);
			a2=path;
			a2=a2+"/"+v[1];
		}
	else{
		goto END;
	}
	const char* r3=a2.c_str();
	ofstream myfile;
	myfile.open (r3);
	if(myfile.is_open())
	{

		printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("create_file success");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
	else{
		printf("\e[23;1H");
    	printf("\e[2K");
    	printf("create_file failed");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");

	}
	myfile.close();
   
	}
	else{
		END:
		printf("\e[23;1H");
    	printf("\e[2K");
        printf("r command invalid");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
}