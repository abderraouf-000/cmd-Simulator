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


char pathexist[50][19];
char lastele[25];
int found = 0;
//
exist(pathexist,rootc,0,"telechargement",1,&found);
if(!found)printf("File is not found !!");
mkdir(&rootc,"no","/root");
//printf("%d\n",pathfound(rootc,"/"));
mkfile(&rootc,"prayer","/bin",50);
ls(rootc,"/bin","");
printf("%d",space);
rm(&rootc,"/bin","prayer");
displaytree(rootc,1);




    return 0;
}



