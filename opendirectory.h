#include <iostream>
#include <dirent.h>
#include <string>
using namespace std;

#ifndef INC_OPENDIRECTORY_H
#define INC_OPENDIRECTORY_H

void scanDirectory(const char *,int);
void printFileType(dirent *); 
void printFilePermissions(dirent *);
void printFileName(dirent *);
void printUserName(dirent *);
void printGroupName(dirent *);
void printFileSize(dirent *);
void printFileTime(dirent *);
int getlowerlimit();
int getupperlimit();
void scanDirectory(int);
bool checkDirectory(int);
void printCustomDirectory(int ,int);
void openFile(int);
string getroot();
void setroot(string);
void goleft();
void goright();
#endif  /*INC_MODULE1_H*/
