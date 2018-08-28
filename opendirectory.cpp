#include"opendirectory.h"
#include <dirent.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<termios.h>
#include<sys/wait.h>
#include<string>
#include<stack>
using namespace std;
int  lowerlimit,upperlimit;
struct dirent **namelist;
dirent *prev;
dirent *current;
string root;

stack<char *> leftstack;
stack<char *> rightstack;

string getroot(){
	return root;
}
void setroot(string rt){
 root =rt;

}
int getlowerlimit(){
	return lowerlimit;
}

int getupperlimit(){
	return upperlimit;
}

void gohome(){
	int i,n,l;
	const char *cr=root.c_str();
	// printf("%s",cr);
	char *r2=realpath(".",NULL);
		int check=root.compare(r2);
		if(check!=0){
			while(!rightstack.empty()){
				rightstack.pop();
			}
			leftstack.push(r2);
		}
	chdir(cr);
    n=scandir(cr,&namelist,0,alphasort);
    current=namelist[0];
    if (n < 0){
        printf("No such Directory");
    return;
    }
    else {
    	if(n>20) l=20;
    	else l=n;
        for (i = 0; i < l; i++) {
            printFileType(namelist[i]); 
            printFilePermissions(namelist[i]);
            printFileName(namelist[i]);
            printUserName(namelist[i]);
            printGroupName(namelist[i]);
            printFileSize(namelist[i]);
            printFileTime(namelist[i]);
            //free(namelist[i]);
            }
            lowerlimit=0;
            upperlimit=n-1;
        }
	
	namelist[1]=current;
}

//to go forward
void goright(){

	int n,i,l;
	if(rightstack.empty()){
		printf("\e[23;1H");
		printf("\e[2K");
		printf("No directory to go forward");
		printf("\e[1;1H");
	}
	else{
		printf("\e[2J");
	    printf("\e[1;1H");
		dirent *temp;
		
		//temp=leftstack.top();
		char *fromstack=rightstack.top();
		char *tostack=realpath(".",NULL);
		leftstack.push(tostack);
		//char *path=realpath(temp->d_name,NULL);
		//printf("%s",fromstack);
		rightstack.pop();
		
		chdir(fromstack);
		n=scandir(".",&namelist,0,alphasort);
		//char *r1=root;
		char *r2=realpath(".",NULL);
		int check=root.compare(r2);
		if(check==0){
			namelist[1]=namelist[0];
		}
		if(n>19) l=20;
		else l=n;
	for (i = 0; i < l; i++) {
            printFileType(namelist[i]); 
            printFilePermissions(namelist[i]);
            printFileName(namelist[i]);
            printUserName(namelist[i]);
            printGroupName(namelist[i]);
            printFileSize(namelist[i]);
            printFileTime(namelist[i]);
            //free(namelist[i]);
        }
            lowerlimit=0;
            upperlimit=n-1;
            printf("\e[1;1H");
	}

}

//to go backwards
void goleft(){
	int n,i,l;
	if(leftstack.empty()){
		printf("\e[23;1H");
		printf("\e[2K");
		printf("No previous directory");
		printf("\e[1;1H");
	}
	else{
		printf("\e[2J");
	    printf("\e[1;1H");
		dirent *temp;
		
		//temp=leftstack.top();
		char *fromstack=leftstack.top();
		char *tostack=realpath(".",NULL);
		rightstack.push(tostack);
		//char *path=realpath(temp->d_name,NULL);
		//printf("%s",fromstack);
		leftstack.pop();
		
		chdir(fromstack);
		n=scandir(".",&namelist,0,alphasort);
		//char *r1=root;
		char *r2=realpath(".",NULL);
		int check=root.compare(r2);
		if(check==0){
			namelist[1]=namelist[0];
		}
		if(n>19) l=20;
		else l=n;
	for (i = 0; i < l; i++) {
            printFileType(namelist[i]); 
            printFilePermissions(namelist[i]);
            printFileName(namelist[i]);
            printUserName(namelist[i]);
            printGroupName(namelist[i]);
            printFileSize(namelist[i]);
            printFileTime(namelist[i]);
            //free(namelist[i]);
        }
            lowerlimit=0;
            upperlimit=n-1;
            printf("\e[1;1H");
	}
	
}

//open the file after pressing enter
void openFile(int c){
	pid_t pid;
	int s=0;
	int status;
	
				pid=fork();
				if(pid==0){
					printf("\e[22;1H");
				    printf("\e[2K");
				    printf("\n");
					execl("/usr/bin/xdg-open","xdg-open",namelist[c]->d_name,NULL);
					exit(1);
					printf("\e[1;1H");
				}
				waitpid(pid, &status, 0);
	
}
void snapshot(){

}

//print directory content in the given window
void printCustomDirectory(int lowerlimit,int currentlimit){
	for (int i = lowerlimit; i <= currentlimit; i++) {
            printFileType(namelist[i]); 
            printFilePermissions(namelist[i]);
            printFileName(namelist[i]);
            printUserName(namelist[i]);
            printGroupName(namelist[i]);
            printFileSize(namelist[i]);
            printFileTime(namelist[i]);
            //free(namelist[i]);
            }
}

//scan directory with path
void scanDirectory(const char *root,int flag){
	//struct dirent **namelist;
	int i,n,l;

	if(flag==0){
	chdir(root);
    n=scandir(root,&namelist,0,alphasort);
    current=namelist[0];
    if (n < 0){
        printf("No such Directory");
    return;
    }
    else {
    	if(n>20) l=20;
    	else l=n;
        for (i = 0; i < l; i++) {
            printFileType(namelist[i]); 
            printFilePermissions(namelist[i]);
            printFileName(namelist[i]);
            printUserName(namelist[i]);
            printGroupName(namelist[i]);
            printFileSize(namelist[i]);
            printFileTime(namelist[i]);
            //free(namelist[i]);
            }
            lowerlimit=0;
            upperlimit=n-1;
        }
	}
	namelist[1]=current;
}

//check if the current index is poinint to directory or not
bool checkDirectory(int c){
	int t;
	t=namelist[c]->d_type;
	if(t==DT_DIR){
		return true;
	}
	return false;
}

//scan directory after pressing enter with the help of indexs
void scanDirectory(int c){
	int i,n,t,l;

	//n=scandir(current->d_name,&namelist,0,alphasort);
	t=namelist[c]->d_type;
	dirent *temp;
	temp=namelist[c];
	//printf("%d",t==DT_DIR);
	if(t==DT_DIR){

		char *tostack=realpath(".",NULL);
		leftstack.push(tostack);
		free(namelist);
		
		chdir(temp->d_name);

		n=scandir(".",&namelist,0,alphasort);
		//char *r1=root;
		char *r2=realpath(".",NULL);
		int check=root.compare(r2);
		if(check==0){
			namelist[1]=namelist[0];
		}
		if(n>19) l=20;
		else l=n;
	for (i = 0; i < l; i++) {
            printFileType(namelist[i]); 
            printFilePermissions(namelist[i]);
            printFileName(namelist[i]);
            printUserName(namelist[i]);
            printGroupName(namelist[i]);
            printFileSize(namelist[i]);
            printFileTime(namelist[i]);
            //free(namelist[i]);
            }
            lowerlimit=0;
            upperlimit=n-1;
	}

}

//pass dirent pointer to that directory or file 
void printFileType(dirent *p){
	int t;
	t=p->d_type;
	if(t==DT_BLK) printf("bd ");     

              if(t==DT_CHR) printf("cd ");    

              if(t==DT_DIR) printf("d ");

			if(t==DT_FIFO) printf("p ");  

			if(t==DT_LNK) printf("l ");

			if(t==DT_REG) printf("f ");
      
      		if(t==DT_SOCK) printf("s "); 

            if(t==DT_UNKNOWN) printf("u ");
}

//pass dirent pointer to that directory or file
void printFileName(dirent *p){
	string s=p->d_name;
	if(s.length()>20) s.resize(20);
	printf("  %-20s",s.c_str());

}

//pass dirent pointer to that directory or file
void printFilePermissions(dirent *p){
	struct stat st;
	stat(p->d_name, &st);
	printf( (st.st_mode & S_IRUSR) ? "r" : "-");
	printf( (st.st_mode & S_IWUSR) ? "w" : "-");
    printf( (st.st_mode & S_IXUSR) ? "x" : "-");
    printf( (st.st_mode & S_IRGRP) ? "r" : "-");
    printf( (st.st_mode & S_IWGRP) ? "w" : "-");
    printf( (st.st_mode & S_IXGRP) ? "x" : "-");
    printf( (st.st_mode & S_IROTH) ? "r" : "-");
    printf( (st.st_mode & S_IWOTH) ? "w" : "-");
    printf( (st.st_mode & S_IXOTH) ? "x" : "-");	
}

//pass dirent pointer to that directory or file
void printUserName(dirent *p){
	struct stat st;
	stat(p->d_name, &st);
	struct passwd *pw = getpwuid(st.st_uid);
	printf(" %-10s ",pw->pw_name);
}

//pass dirent pointer to that directory or file
void printGroupName(dirent *p){
	struct stat st;
	stat(p->d_name, &st);
	struct group  *gr = getgrgid(st.st_gid);
	printf(" %-10s ",gr->gr_name);
}

//pass dirent pointer to that directory or file
void printFileSize(dirent *p){
	long double bz;
	long int kz;
	struct stat st;
	stat(p->d_name, &st);
	kz=st.st_size;
    if(kz>=1024) {
      	bz=kz%1024;
      	bz=bz/10000;
      	kz=kz/1024;
      	bz=bz+kz;
   	  	printf("%10LGK  ",bz);
    }
    else printf("%10li   ",kz);
}

//pass dirent pointer to that directory or file
void printFileTime(dirent *p){
	struct stat st;
	stat(p->d_name, &st);
	printf("%30s",ctime(&st.st_mtime));
}