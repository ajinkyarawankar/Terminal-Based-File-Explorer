#include"opendirectory.h"
#include <dirent.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>


//using namespace std;


void scanDirectory(const char *root,int flag){
	struct dirent **namelist;
	int i,n;

	if(flag==0){

    n=scandir(root,&namelist,0,alphasort);
    if (n < 0){
        printf("No such Directory");
    return;
    }
    else {
        for (i = 0; i < n; i++) {
            printFileType(namelist[i]); 
            printFilePermissions(namelist[i]);
            printFileName(namelist[i]);
            printUserName(namelist[i]);
            printGroupName(namelist[i]);
            printFileSize(namelist[i]);
            printFileTime(namelist[i]);
            free(namelist[i]);
            }
        }
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

			//if(t==DT_LINK) printf("l");

			if(t==DT_REG) printf("f ");
      
      		if(t==DT_SOCK) printf("s "); 

            if(t==DT_UNKNOWN) printf("u ");
}

//pass dirent pointer to that directory or file
void printFileName(dirent *p){
	printf("%-20s",p->d_name);
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
	printf("%30s\n",ctime(&st.st_mtime));
}