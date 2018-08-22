#include <iostream>
#include <dirent.h>

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

#endif  /*INC_MODULE1_H*/
