#include <stdio.h>
#include"opendirectory.h"

int main(int argc, char const *argv[]){

	const char *root;
	if(argc==1)
	    root=".";
	else
		root= argv[1];
	scanDirectory(root,0);

}