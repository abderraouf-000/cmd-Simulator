#include <stdio.h>
#include <stdlib.h>
#include "final.h"
#include <ctype.h>
char username[30] ="Machine";
int main()
{

tree rootc  = createtreenode(100,1,"/"); //  tree root creation
treeinit(&rootc);


//printf("%d",pathfound(rootc,"/home/Univ8mai194"));
//printf("Enter the user-name : ");
//gets(username);
//char command[] = {"  /fdfd/fdfdfd   rm thing"};
//
//
//int n =  3; // number of command elements
//char* separation[4];
//
//
//char pathexist[50][19];
//char lastele[25];
//int found = 0;
////
//exist(pathexist,rootc,0,"telechargement",1,&found);
//if(!found)printf("File is not found !!");
//mkdir(&rootc,"no","/root");
////printf("%d\n",pathfound(rootc,"/"));
////mkfile(&rootc,"prayer","/bin",50);
////ls(rootc,"/bin","");
////printf("%d",space);
////rm(&rootc,"/bin","prayer");
//
//copyorigin(rootc,"/home","Univ8mai1945","/",NULL);
//
//displaytree(rootc,1);

char incommand[100];
while(strcasecmp(incommand,"exit")){


printf("%s /: ",username);
gets(incommand);
linked cmdparts = commandseparator(incommand);
char cmdname[16];
char cmdpath[70];
char cmdfname[16];
strcpy(cmdname,cmdparts -> name);
cmdparts = cmdparts->next;


if(!strcasecmp(cmdname,"tree")){
        if(!cmdparts){
            displaytree(rootc,1);
        }
else if(commandsize(cmdparts) == 2){
char fullpath[70];
char fname[18];
strcpy(cmdpath,cmdparts->name);
cmdparts = cmdparts->next;
strcpy(fname,cmdparts->name);
pathconcatname(fullpath,cmdpath,fname);

        if(pathfound(rootc,fullpath)){
displaytreehelper(rootc,cmdpath,cmdparts->name);
        }
        else{
            printf("Path is wrong !\n");
        }
    }
    else{
        printf("Command is wrong ! \n");
    }
}


if(!strcasecmp(cmdname,"exist")){
while(cmdparts){
        printf("--------%s-------- \n ",cmdparts->name);
        char existpath[20][40];
        int found = 0 ;
        exist(existpath,rootc,0,cmdparts->name,1,&found);
        if(!found)printf("File or Folder not found ! \n");
cmdparts= cmdparts->next;
}

}


// if only address we delete all the path otherwise we choose the files and folders
if(!strcasecmp(cmdname,"rm")){
if(cmdparts){

strcpy(cmdpath,cmdparts->name);
cmdparts = cmdparts->next;
// in the case of only address
if(commandsize(cmdparts) == 0 && pathfound(rootc,cmdpath)){
rmoptional(&rootc,cmdpath);
}
else{
if(cmdparts){


if(pathfound(rootc,cmdpath)){
while(cmdparts){
char fullpath[70];
char fname[18] ;
strcpy(fname,cmdparts->name);
pathconcatname(fullpath,cmdpath,fname);

if(!pathfound(rootc,fullpath)){
printf("Path is wrong !! \n");
break;
}
rm(&rootc,cmdpath,cmdparts->name);
cmdparts = cmdparts->next;
}

}


   else{
    printf("Path is wrong ! \n");
  }


}
   else{
    printf("Command is wrong !\n");
    }
}
}
else{
    printf("Action not Allowed in Normal-user mode !\n");
}
                }




if(!strcasecmp(cmdname,"ls")){
if(commandsize(cmdparts)!= 2){
    printf(" command is Wrong or not found ! \n");
}
else{
    char fullpath[70];
    char foldernamepath[30];
    strcpy(foldernamepath,(cmdparts->next)->name);
    strcat(foldernamepath,"/");
    strcpy(fullpath,cmdparts->name);
    strcat(fullpath,foldernamepath);
if(pathfound(rootc,fullpath)){
   ls(rootc,fullpath);
   printf("\n");
}
else{
printf("Path or command is Wrong or not found ! \n");
}
}
}
// problem is that when you create two files with the same name directly it does not give an error : i use last to solve it

if(!strcasecmp(cmdname,"mkdir")){

    if(commandsize(cmdparts) == 2){
    strcpy(cmdpath,cmdparts->name);
    if(pathfound(rootc,cmdpath)){
        mkdir(&rootc,(cmdparts->next)->name,cmdparts->name);
        }

    else{
        printf("Path not found or files with the same name! \n");
    }

    }
    else{
printf("command is wrong ! \n");
    }

}


if(!strcasecmp(cmdname,"storage")){
    printf("%d\n",space);
}



if(!strcasecmp(cmdname,"mkfile")){
    if(commandsize(cmdparts)== 3){
    strcpy(cmdpath,cmdparts->name);
    if(pathfound(rootc,cmdpath)){

    cmdparts = cmdparts->next;
    strcpy(cmdfname,cmdparts->name);
    cmdparts = cmdparts->next;
    // converting the size string to a number
    char* endptr;
    int filesize = strtol(cmdparts->name,&endptr,10);
    if(!strcmp(endptr,"")){
    mkfile(&rootc,cmdfname,cmdpath,filesize);
    }

    else{
        printf("Error :command is Wrong !!\n");
    }

    }
    else{
        printf("Path is wrong ! \n");
    }
    }
    else{
        printf("command is wrong ! \n");
    }
}






if(!strcasecmp(cmdname,"help")){
    if(!cmdparts){
printf("ls : les arguments = chemin , nom / role = Afficher le contenu d'un Dossier \n");
printf("rm : les arguments = chemin , nom(fichier , dossier) / role = Supprimer un fichier ou un dossier\n");
printf("mkdir-mkfile : les arguments = chemin , nom dossier (resp. fichier) / role =  Ajouter un dossier (resp. fichier ) \n");
printf("cpdir-cpfile : les arguments = chemin du dossier(resp. fichier) , nom dossier (resp. fichier) , chemin cible / role =  Ajouter un dossier (resp. fichier ) \n");
printf("exist: les arguments = nom dossier (resp. fichier) ; role =  Retourner le chemin du dossier,fichier \n");
printf("exit: exit the termimal \n");
    }
    else{
            printf("Command arguments are wrong ! ");
    }
                               }


if(!strcasecmp(cmdname,"clear")){
    system("clear");
}




}








    return 0;
}



