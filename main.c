#include <stdio.h>
#include <stdlib.h>
#include "final.h"

int main()
{

tree rootc  = createtreenode(100,1,"/"); //  tree root creation

treeinit(&rootc);
char command[] = {"  /fdfd/fdfdfd   rm thing"};


int n =  3; // number of command elements
char* separation[4];

//printf("%d\n",pathfound(rootc,"/"));
//ls(rootc,"/","home");
char pathexist[50][19];
char lastele[25];

exist(pathexist,rootc,0,"Univ8mai1945",0,lastele);
displaytree(rootc,1);



    return 0;
}



