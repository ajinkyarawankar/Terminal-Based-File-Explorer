#include <iostream>
#include <fstream>
#include<sys/stat.h>
int main()
{
  //  std::ifstream  src("vid2.mp4", std::ios::binary);
   // std::ofstream  dst("./home/vid.mp4",   std::ios::binary);
    //dst << src.rdbuf();
    //remove("vid2.mp4");
    // remove("./home/deltest");

   // mkdir("./home/cnd", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    int status;
     status = rename("vid2.mp4", "vid2.mp4");
    if(status==0){
    	printf("success");
    }
    else{
    	printf("fail");
        printf("svFSvsfv");
    printf("svFSvsfv");
    }



}



// #include <iostream>
// #include <fstream>
// #include <experimental/filesystem>
// namespace fs = std::experimental::filesystem;
 
// int main()
// {
//  //   fs::create_directories("sandbox/dir/subdir");
//  //   std::ofstream("sandbox/file1.txt").put('a');
// //   fs::copy("vid.mp4", "/home"); // copy file
//  //   fs::copy("sandbox/dir", "sandbox/dir2"); // copy directory (non-recursive)
//     // sandbox holds 2 files and 2 directories, one of which has a subdirectory
//     // sandbox/file1.txt
//     // sandbox/file2.txt
//     // sandbox/dir2
//     // sandbox/dir
//     //    sandbox/dir/subdir
//     fs::copy("home", "testcopy", fs::copy_options::recursive);
//     // sandbox/copy holds copies of the above files and subdirectories
//   //  fs::remove_all("sandbox");
// }