#include<iostream>
#include<string>
#include<vector>
using namespace std;

#ifndef INC_COMMANDMODE_H
#define INC_COMMANDMODE_H

void gotot(string);
void setrootc(string);
void rname(vector<string>);
void delfile(vector<string>);
void addfooter();
void create_dir(vector<string>);
void create_file(vector<string>);
void copyhelper(vector<string>);
void copydirectory(const char *,const char *);
void copyfile(const char *,const char *);
void movehelper(vector<string>);
void movefile(const char *,const char *);
void movedirectory(const char *,const char *);
void delete_dir(vector<string>);
void delete_all(const char *);
void snapshothelper(vector<string>);
void snapshot(const char *);
void searchhelper(vector<string>);

#endif