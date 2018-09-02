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

using namespace std;

ofstream myfile;

struct dirent **namelistc;
//struct dirent **searchlist;
vector<string> searchlist;
int searchpos=0;
string rootc;
string searchFile;
int rlen;
int flag=0;
void setrootc(string rt){
 rootc =rt;
rlen=rootc.length();
}


void searchhelper(vector<string> v){
	const char *r=realpath(".",NULL);
	int size =v.size();
	if(size>1){
	searchFile=v[1].c_str();
    //free(searchlist);
    searchpos=0;
    search(r);
    chdir(r);
    	printf("\e[2J");
	    printf("\e[1;1H");
	  //  refresh();
	    if(searchpos>0)
	    {
	    // 	string ss=searchlist[i];
	    // 	ss.erase(0,rlen);
	    // 	ss="~"+ss;
    	// printf("%s\n",ss.c_str());
    	setvector(searchlist,searchpos);
    	}
    	refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("search success");
    	if(searchpos==0){
    		printf("\e[24;1H");
    	printf("\e[2K");
    	printf("no result found");
    	}
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
    
	
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
          //      printf("%s",check);
                if(check.compare(searchFile)==0){
                	const char *sl=realpath(namelist[i]->d_name,NULL);
                		searchlist.push_back(sl);
                		searchpos++;
                }
               	
            }
}
chdir("..");

}


void snapshothelper(vector<string> v){
	flag=0;
	int size =v.size();
	if(size>2){
	string filename=rootc;
	filename=filename+"/";
	filename=filename+v[2];
	
	// ifstream f(filename.c_str());
 //    if(f.good()){remove(filename.c_str());}
const char *r1=realpath(".",NULL);
    myfile.open(filename.c_str()); 
    string arg=v[1];
    if(arg.length()==1){
    	
    	arg=r1;
    }
    else {
    	arg=r1;
    	arg=arg+"/"+v[1];
    }
   
    if(rootc.compare(arg)==0) myfile<<"Root";
    // else {
    // 	string temp=r1;
    // 	temp.erase(0,rlen);
    // 	myfile<<temp;
    // }
    struct stat st;
    if(stat(arg.c_str(),&st)==0){
        snapshot(arg.c_str());
    }
    else flag=1;
        chdir(r1);
        myfile.close();
    	printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("snapshot success");
    	if(flag==1) {
    		printFail();
    		flag=0;
    	}
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
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

void snapshot(const char *r){

string p=r;
string temp=p;
temp.erase(0,rlen);
myfile<<"\n"<<temp<<"\n";

	struct dirent **namelist;
    string path;
    int n;
    chdir(r);
    n=scandir(".",&namelist,0,alphasort);
    for(int i=2;i<n;i++){
    	myfile<<namelist[i]->d_name<<"\t";
    }
    for(int i=2;i<n;i++){
    	if (namelist[i]->d_type == DT_DIR) {
                
                path=r;
                path=path+"/"+namelist[i]->d_name;
                snapshot(path.c_str());
            }
    }
chdir("..");

}



void delete_all(const char *dirname){

	struct dirent **namelist;
    string path;
    int n;
    chdir(dirname);
    n=scandir(".",&namelist,0,alphasort);
    for(int i=2;i<n;i++){

            if (namelist[i]->d_type == DT_DIR) {
                
                path=dirname;
                path=path+"/"+namelist[i]->d_name;
                delete_all(path.c_str());
                rmdir(path.c_str());
            }
            else
            {
               
                path=dirname;
                path=path+"/"+namelist[i]->d_name;
               	remove(path.c_str());
            }
}
chdir("..");
}

void delete_dir(vector<string> v){
	int size =v.size();
	if(size>1){
	string c=rootc+"/"+v[1];
	const char *r1=c.c_str();
	struct stat st;
	if(stat(r1,&st)==0){
    delete_all(r1);
    rmdir(r1);
	}
	else{
		flag=1;
	}
    	printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("delete success");
    	if(flag==1) {printFail();
    		flag=0;}
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
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
void movehelper(vector<string> v){
	flag=0;
	int size =v.size();
	if(size>2){
	const char *copyroot;
	copyroot=realpath(".",NULL);
	string dirn=copyroot;
	dirn=dirn+"/"; 
	dirn=dirn+v[1];
	string desn=rootc;
	desn=desn+"/";
	string vs=v[size-1];
	char ch=vs[0];
	if(ch=='~'){
		string vp=vs.substr(1,vs.length()-1);
	desn=desn+vp;
	for(int i=1;i<size-1;i++)
	{	
		struct stat st;
		copyroot=realpath(".",NULL);
		string dirn=copyroot;
		dirn=dirn+"/"; 
		dirn=dirn+v[i];
		desn=desn+"/";
		if(stat(dirn.c_str(),&st)==0){
		if(S_ISDIR(st.st_mode)){
			movedirectory(dirn.c_str(),(desn+v[i]).c_str());
			rmdir(dirn.c_str());
		}
		else{
			movefile(dirn.c_str(),(desn+v[i]).c_str());
		}
	}
	else{
		flag=1;
	}
	}
	}	
	else goto CI; 
	chdir(copyroot);
		printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("move success");
    	if(flag==1) printFail();
    	flag=0;
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
	else{
		CI:
		printf("\e[23;1H");
    	printf("\e[2K");
        printf("d command invalid");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
}

void movedirectory(const char *dirname,const char *desname){
	struct dirent **namelist;
    string path,despath;
    int n;
    chdir(dirname);
    struct stat st;
    stat(dirname,&st);

    mkdir(desname,st.st_mode);
    n=scandir(".",&namelist,0,alphasort);
    for(int i=2;i<n;i++){

            if (namelist[i]->d_type == DT_DIR) {
                despath=desname;
                despath=despath+"/"+namelist[i]->d_name;
                path=dirname;
                path=path+"/"+namelist[i]->d_name;
                movedirectory(path.c_str(),despath.c_str());
                rmdir(path.c_str());
            }
            else
            {
                despath=desname;
                despath=despath+"/"+namelist[i]->d_name;
                path=dirname;
                path=path+"/"+namelist[i]->d_name;
               	movefile(path.c_str(),despath.c_str());
            }
}
chdir("..");
}

void movefile(const char *path,const char *despath){

	ifstream f(despath);
    if(f.good()){}
                else{
                std::ifstream  src(path, std::ios::binary);
                std::ofstream  dst(despath, std::ios::binary);
                dst << src.rdbuf();
            }
    ifstream f2(despath);
    if(f2.good()){}
    	else{
    		flag=1;
    	}
            remove(path);
    	}


void copydirectory(const char *dirname,const char *desname){

    struct dirent **namelist;
    string path,despath;
    int n;
    chdir(dirname);
    struct stat st;
    stat(dirname,&st);

    mkdir(desname,st.st_mode);
    n=scandir(".",&namelist,0,alphasort);
    for(int i=2;i<n;i++){

            if (namelist[i]->d_type == DT_DIR) {
                despath=desname;
                despath=despath+"/"+namelist[i]->d_name;
                path=dirname;
                path=path+"/"+namelist[i]->d_name;
                copydirectory(path.c_str(),despath.c_str());
            }
            else
            {
                despath=desname;
                despath=despath+"/"+namelist[i]->d_name;
                path=dirname;
                path=path+"/"+namelist[i]->d_name;
               	copyfile(path.c_str(),despath.c_str());
            }
}
chdir("..");
}

void copyfile(const char *path ,const char *despath){
	ifstream f(despath);
    if(f.good()){}
                else{
                std::ifstream  src(path, std::ios::binary);
                std::ofstream  dst(despath, std::ios::binary);
                dst << src.rdbuf();
}
ifstream f2(path);
    if(f2.good()){}
    else{
    	flag=1;
    }

}

void printFail(){
	printf("\e[24;1H");
    	printf("\e[2K");
    	printf("operation failed for some file due to incorrect source or destination");
}
void copyhelper(vector<string> v){

	flag=0;
    int size =v.size();
	if(size>2){
	const char *copyroot;
	copyroot=realpath(".",NULL);
	string dirn=copyroot;
	dirn=dirn+"/"; 
	dirn=dirn+v[1];
	string desn=rootc;
	desn=desn+"/";
	string vs=v[size-1];
	char ch=vs[0];
	if(ch=='~'){
		string vp=vs.substr(1,vs.length()-1);
	desn=desn+vp;
	for(int i=1;i<size-1;i++)
	{	
		struct stat st;
		copyroot=realpath(".",NULL);
		string dirn=copyroot;
		dirn=dirn+"/"; 
		dirn=dirn+v[i];
		desn=desn+"/";
		if(stat(dirn.c_str(),&st)==0){
		if(S_ISDIR(st.st_mode)){
			copydirectory(dirn.c_str(),(desn+v[i]).c_str());
		}
		else{
			copyfile(dirn.c_str(),(desn+v[i]).c_str());
		}
	}
	else{
		flag=1;
	}
	}
	}	
	else goto CI; 
	chdir(copyroot);

		printf("\e[2J");
	    printf("\e[1;1H");
	    refresh();
	    printf("\e[23;1H");
    	printf("\e[2K");
    	printf("copy success");
    	if(flag==1) printFail();
    	flag=0;
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
	else{
		CI:
		printf("\e[23;1H");
    	printf("\e[2K");
        printf("d command invalid");
        printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
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
        printf("command invalid");
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
	ifstream f(r3);
	if(f.good()){
		printf("\e[23;1H");
    	printf("\e[2K");
    	printf("file already exist");
    	printf("\e[22;1H");
    	printf("\e[2K");
    	printf(":");
	}
	else{
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