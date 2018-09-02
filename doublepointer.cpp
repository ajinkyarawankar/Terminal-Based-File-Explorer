#include"commandmode.h"
#include"opendirectory.h"
#include<iostream>
#include<string>
#include <dirent.h>
#include <unistd.h>
#include<vector>
#include<sys/stat.h>
#include<fstream>
#include<dirent.h>
#include <sys/stat.h>
#include<stdlib.h>
using namespace std;

ofstream myfile;

struct dirent **namelistc;
vector<string> searchlist;
// struct dirent *searchlist[200];
int searchpos=0;
string rootc;
string searchFile;
int rlen;
void setrootc(string rt){
 rootc =rt;
rlen=rootc.length();
}

void search(const char *apath){

	struct dirent **namelist;
    string path;
    int n;
    chdir(apath);
    n=scandir(".",&namelist,0,alphasort);
    for(int i=2;i<n;i++){

            if (namelist[i]->d_type == DT_DIR) {
                
                path=apath;
                path=path+"/"+namelist[i]->d_name;
                search(path.c_str());
            }
            else
            {
               
                string check=namelist[i]->d_name;
               // printf("%s",check);
                if(check.compare(searchFile)==0){
                	const char *sl=realpath(namelist[i]->d_name,NULL);
                		searchlist.push_back(sl);
                		searchpos++;
                }
               	
            }
}
chdir("..");

}

void searchhelper(vector<string> v){
	const char *r=realpath(".",NULL);
	int size =v.size();
	if(size>1){
	searchFile=v[1].c_str();
    //free(searchlist);
    searchpos=0;
    search(r);
    	printf("\e[2J");
	    printf("\e[1;1H");
	    // refresh();
	    // printf("\e[23;1H");
    	// printf("\e[2K");
    	// printf("search success");
    	// printf("\e[22;1H");
    	// printf("\e[2K");
    	// printf(":");
    // printf("\e[23;1H");
    // 	printf("\e[2K");
    for(int i=0;i<searchpos;i++){
    	printf("%s",(searchlist[i]).c_str());
    	
    // }
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




int main(){

	vector<string> v;
	v.push_back("hey");
	v.push_back("test");
	searchhelper(v);

	return 0;
}