#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    std::ifstream  src("vid.mp4", std::ios::binary);
    std::ofstream  dst("./home/vid.mp4",   std::ios::binary);
    // cout<<src.rdbuf();
    dst << src.rdbuf();
}