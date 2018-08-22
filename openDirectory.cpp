#include <dirent.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
//using namespace std;

struct dirent **namelist;
struct stat st;
int i,n;

int main(int argc, char const *argv[])
{
	int t;
	const char *root;
	char *c;
	long int kz;
	long double bz;
	if(argc==1)
	    root=".";
	else
		root= argv[1];
		n=scandir(root,&namelist,0,alphasort);
    if (n < 0)
        perror("");
    else {
        for (i = 0; i < n; i++) {
        	stat(namelist[i]->d_name, &st);
        	t=namelist[i]->d_type;
              if(t==DT_BLK) printf("bd ");     

              if(t==DT_CHR) printf("cd ");    

              if(t==DT_DIR) printf("d ");

			if(t==DT_FIFO) printf("p ");  

			//if(t==DT_LINK) printf("l");

			if(t==DT_REG) printf("f ");
      
      		if(t==DT_SOCK) printf("s "); 

            if(t==DT_UNKNOWN) printf("u ");
      
            c=namelist[i]->d_name;
         //    if(c[0]=="." && c[1]!="."){
        	// }
        	// else 
        	    printf( (st.st_mode & S_IRUSR) ? "r" : "-");
			    printf( (st.st_mode & S_IWUSR) ? "w" : "-");
    			printf( (st.st_mode & S_IXUSR) ? "x" : "-");
    			printf( (st.st_mode & S_IRGRP) ? "r" : "-");
    			printf( (st.st_mode & S_IWGRP) ? "w" : "-");
    			printf( (st.st_mode & S_IXGRP) ? "x" : "-");
    			printf( (st.st_mode & S_IROTH) ? "r" : "-");
    			printf( (st.st_mode & S_IWOTH) ? "w" : "-");
    			printf( (st.st_mode & S_IXOTH) ? "x" : "-");
        	  printf("  %-20s ", namelist[i]->d_name);
        	  struct passwd *pw = getpwuid(st.st_uid);
              struct group  *gr = getgrgid(st.st_gid);
        	  printf(" %-10s ",pw->pw_name);
        	  printf(" %-10s ",gr->gr_name);
        	  kz=st.st_size;
        	  if(kz>=1024) {
        	  	bz=kz%1024;
        	  	bz=bz/10000;
        	  	kz=kz/1024;
        	  	bz=bz+kz;

        	  	printf("%10LGK  ",bz);
        	  }
        	  else printf("%10li   ",kz);
      		  printf("%30s\n",ctime(&st.st_mtime));

            free(namelist[i]);
            }
        }
    free(namelist);
	return 0;
}

   