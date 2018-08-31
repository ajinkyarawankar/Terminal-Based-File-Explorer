#include <iostream>
#include <fstream>
#include<sys/stat.h>
#include<dirent.h>
#include<string>
#include<string.h>
#include<unistd.h>
using namespace std;


void copydirectory(const char* dirname,const char* desname){

    struct dirent **namelist;
    string path,despath;
    int n;
    chdir(dirname);
    mkdir(desname,0777);
    n=scandir(".",&namelist,0,alphasort);
    for(int i=2;i<n;i++){
            cout<<namelist[i]->d_name<<endl;
            printf("%s/%s\n",dirname,namelist[i]->d_name);
            printf("%s/%s\n",desname,namelist[i]->d_name);
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
                ifstream f(despath);
    if(f.good()){}
                else{
                std::ifstream  src(path, std::ios::binary);
                std::ofstream  dst(despath,   std::ios::binary);
                dst << src.rdbuf();
                }
            }
}
chdir("..");
}


void copyhelper(const char* dirname,const char* desname){

const char *copyroot;
copyroot=realpath(".",NULL);
string dirn=copyroot;
dirn=dirn+"/"; 
dirn=dirn+dirname;
string desn=copyroot;
desn=desn+"/";
desn=desn+desname;
copydirectory(dirn.c_str(),desn.c_str());
chdir(copyroot);

}

int main()
{
    copyhelper("home","baby/home");

//     ifstream f("filenamedbkjbk.txt");
//     cout<<f.good();


//    // std::ifstream  src("vid2.mp4", std::ios::binary);
//    // std::ofstream  dst("./home/vid.mp4",   std::ios::binary);
//    //  dst << src.rdbuf();
//     //remove("vid2.mp4");
//     // remove("./home/deltest");

//    // mkdir("./home/cnd", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//     // int status;
//     //  status = rename("vid2.mp4", "vid2.mp4");
//     // if(status==0){
//     // 	printf("success");
//     // }
//     // else{
//     // 	printf("fail");
//     //     printf("svFSvsfv");
//     // printf("svFSvsfv");
//     // }



// }



// // #include <iostream>
// // #include <fstream>
// // #include <experimental/filesystem>
// // namespace fs = std::experimental::filesystem;
 
// // int main()
// // {
// //  //   fs::create_directories("sandbox/dir/subdir");
// //  //   std::ofstream("sandbox/file1.txt").put('a');
// // //   fs::copy("vid.mp4", "/home"); // copy file
// //  //   fs::copy("sandbox/dir", "sandbox/dir2"); // copy directory (non-recursive)
// //     // sandbox holds 2 files and 2 directories, one of which has a subdirectory
// //     // sandbox/file1.txt
// //     // sandbox/file2.txt
// //     // sandbox/dir2
// //     // sandbox/dir
// //     //    sandbox/dir/subdir
// //     fs::copy("home", "testcopy", fs::copy_options::recursive);
// //     // sandbox/copy holds copies of the above files and subdirectories
// //   //  fs::remove_all("sandbox");
// // }



return 0;
}