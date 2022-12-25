#include "string.h"
#ifndef FINAL_H_INCLUDED
#define FINAL_H_INCLUDED
#include <ctype.h>
#include <string.h>

static int space = 100 ;
typedef struct treenode* tree;
struct treenode
{
    char nom[16];
    int rep;
    int taille;
    tree fils;
    tree frere;
};
typedef struct nodech* linked ;
struct nodech
{
    char name[16];
    linked next;
};
linked pathscan(char[]);
tree createtreenode (int ,int ,char[]);
linked addnodelinked(linked,char[]);
//void exist(char**,tree,int,char*,int,char*);
// display with levels :
void levelprint(int i)
{
    while(i != 0)
    {
        printf("-");
        i--;
    }

}
void displaytree(tree rootc,int i)
{
    if(rootc)
    {
        levelprint(i);
        printf("%s\n",rootc->nom);
        displaytree(rootc->fils,i+1);
        displaytree(rootc->frere,i);

    }

}


void displaytreehelper(tree root,char path[],char name[])
    {
        linked pathlist;
        pathlist = pathscan(path);
        tree trav = root;

// loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {


                if(!strcmp(pathlist->name,trav->nom))
                {
                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }
                }
            }

            if(pathlist == NULL)      // deleting from les freres
            {
                while(trav != NULL)
                {
                    if(!strcmp(trav->nom,name)){
                    trav = trav->fils;
                    if(!trav || !trav->rep){
                        printf("The folder or the file is empty ! \n");
                    }
                    displaytree(trav,1);
                    }
                    trav = trav->frere;
                }
            }
    }














// test if it is a command or not
int isitcmd(char cmd[])
{
    int n = 10;
    char commandsnames[][15] = {"rm","ls","mkdir","mkfile","cpfile","cpdir","exist","help","exit"};
    for(int i  = 0 ; i <  n ;  i ++ )
    {
        if(!strcmp(cmd,commandsnames[i]))return 1;
    }
    return 0;
}


void mkdir(tree* root,char name[],char path[])
    {
        linked pathlist;
        printf("%s , %d \n",name,strlen(name));
        tree newnode = createtreenode(0,1,name);
        pathlist = pathscan(path);

        tree trav = *root;

        if((*root)->fils == NULL )
        {
//if(!strcmp(pathlist->name,trav->nom))
            (*root)->fils = newnode;
//else {printf("Wrong path or not found !!");}
        }

        else
        {

// loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {


                if(!strcmp(pathlist->name,trav->nom))
                {

                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }
                }
            }

            if(pathlist == NULL)      // inserting in frere last position
            {
                while(trav->frere != NULL)
                {
                    if(!strcmp(name,trav->nom) && trav->rep==1){
                        printf("There is a Folder with the same name !! \n");
                        return;
                    }
                    trav = trav->frere;

                }
                   if(!strcmp(name,trav->nom) && trav->rep==1){
                        printf("There is a Folder with the same name !! \n");
                        return;
                    }
                trav->frere = newnode;
            }
            else
            {
                trav->fils = newnode;
            }

        }

    }









// save the command parts in a linked list
linked commandseparator(char command[])
{
// 1 : cmd name , 2 :
//
    linked commandparts = NULL;
    int i = 0;
    int j  = 0;
    char ele[70];


    while(command[i] != '\0')
    {
        if(command[i] != ' ')
        {
            ele[j] = command[i];
            j++;
        }
        else
        {
            ele[j] = '\0';
            if( strcmp(ele,""))
            {
               commandparts =  addnodelinked(commandparts,ele);
                strcpy(ele,"\0");
            }
            j = 0;
        }

        i++;
    }
    ele[j] = '\0';
//    printf("%s",ele);
            if( strcmp(ele,""))
            {
               commandparts =  addnodelinked(commandparts,ele);
            }
return commandparts;
}



// function to add nodes to tree !!!
// problem it displays the first fils !!!
void treeinit(tree* rootc)
{
    addnodetree(&(*rootc),"home","/",0,1);
    addnodetree(&(*rootc),"bin","/",0,1);
    addnodetree(&(*rootc),"root","/",0,1);
    addnodetree(&(*rootc),"run","/",0,1);
    addnodetree(&(*rootc),"telechargement","/",0,1);
    addnodetree(&(*rootc),"Univ8mai1945","/home",0,1);
    addnodetree(&(*rootc),"Bureau","/home/Univ8mai1945",0,1);
    addnodetree(&(*rootc),"Documents","/home/Univ8mai1945",0,1);
    addnodetree(&(*rootc),"telechargement","/home/Univ8mai1945",0,1);
//    addnodetree(&(*rootc),"telechargement","/home/Univ8mai1945",20,1);
    addnodetree(&(*rootc),"telechargement","/home/Univ8mai1945/Documents",0,1);
}

// function to create a node for our tree !!!
tree createtreenode(int nodesize,int isfolder,char name[])
{
    tree node = malloc(sizeof(struct treenode));
    strcpy(node->nom,name);
    node->rep = isfolder;
    node->taille = nodesize;
    node->fils = NULL;
    node->frere = NULL;
    return node;
}



int commandsize(linked cmd){

int n = 0;
while(cmd){
cmd = cmd->next;
n++;
}
return n;
}


void ls(tree root,char path[]){
    // full path holds the full path to traverse
    linked pathlist;
    tree trav = root;
    pathlist = pathscan(path);
while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {


                if(!strcmp(pathlist->name,trav->nom))
                {

                    pathlist = pathlist->next;
                    trav = trav->fils;

                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }

                }
                else if(!pathlist){
                    while(trav != NULL)
                    {
                        if(trav->rep){
                        printf("%s (rep)->",trav->nom);
                        }else{
                        printf("%s (file)->",trav->nom);
                        }
                        trav = trav->frere;
                    }

                }


            }


}




void deletingtreenode(tree* delnode){
if(*delnode){
deletingtreenode(&((*delnode)->fils));
deletingtreenode(&((*delnode)->frere));
space = space + (*delnode)->taille;
free(*delnode);
}

}

void copying(tree origin,tree* copied){
if(origin){
*copied = createtreenode(origin->taille,origin->rep,origin->nom);
copying(origin->fils,&((*copied)->fils));
copying(origin->frere,&((*copied)->frere));
}
}


// paste initialized to 0 to indicate the stATE Is it paste mode or copy mode to avoid repetition
// copy state :  copy-pointer = NULL , paste = 0
void copyorigin(tree root,char originpath[],char originname[],char copypath[],tree copypointer){
        linked pathlist;
        pathlist = pathscan(originpath);
        tree trav = root;
// loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {
                if(!strcmp(pathlist->name,trav->nom))
                {
                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }
                }
            }
            while(trav != NULL){

               if(!strcasecmp(trav->nom,originname)){
                   tree copypoint = createtreenode(trav->taille,trav->rep,trav->nom);
                   copying(trav->fils,&(copypoint->fils));
                   paste(root,copypath,copypoint);
                    }
                    trav = trav->frere;
            }
}


void paste(tree root , char copypath[],tree cpypoint){

        linked pathlist;
        pathlist = pathscan(copypath);
        tree trav = root;
 // loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {
                if(!strcmp(pathlist->name,trav->nom))
                {
                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }
                }
            }
            if(pathlist == NULL)      // inserting in frere last position
            {
                while(trav->frere != NULL)
                {

                    if(!strcasecmp(cpypoint->nom,trav->nom)){
                        printf("There is a File with the same name !! ");
                        return;
                    }

                    trav = trav->frere;
                }
//                space = space - nodesize;
                 if(!strcasecmp(cpypoint->nom,trav->nom)){
              printf("There is a File with the same name !! ");
                     return;
                    }

                trav->frere = cpypoint;
            }
            else
            {
                trav->fils = cpypoint;
//                space = space - nodesize;
            }
}


void rm(tree* root,char path[],char name[])
    {
        linked pathlist;
        pathlist = pathscan(path);
        tree prev = NULL; // to allow insertion after deletion to preserve the link
        linked lastpath; // to save the "pere" to know where we insert fils or frere , prev = lastpath => in fils
        tree trav = *root;

// loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {


                if(!strcmp(pathlist->name,trav->nom))
                {
                    prev = trav;
                    lastpath = pathlist;
                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        prev = trav;
                        trav = trav->frere;
                    }
                }
            }

            if(pathlist == NULL)      // deleting from les freres
            {
                while(trav != NULL)
                {

                    if(!strcasecmp(trav->nom,name)){
                         if(!strcasecmp(prev->nom,lastpath->name)){
                         prev->fils  =  trav->frere;
                        }
                    else{
                        prev->frere =  trav->frere;
                    }
                         tree travorigin = trav; // to save the adress of the trav pointer
                         trav = trav->fils;       //to delete it after deleting it's children
                         deletingtreenode(&(trav));
                         space = space + travorigin->taille;
                         free(travorigin);
                        return;
                    }
                    else{
                    prev = trav;
                    trav = trav->frere;
                    }

                }


            }

    }



void rmoptional(tree* root,char path[])
    {
        linked pathlist;
        pathlist = pathscan(path);
        tree trav = *root;

// loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {


                if(!strcmp(pathlist->name,trav->nom))
                {
                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }
                }
            }

            if(pathlist == NULL)      // deleting from les freres
            {
                while(trav != NULL)
                {


                    rm(&(*root),path,trav->nom);
                    trav = trav->frere;

                }


            }

    }
















void pathconcatname(char fullpath[],char path[],char name[]){
//    char foldernamepath[30];
    strcat(name,"/");
    strcpy(fullpath,path);
    strcat(fullpath,name);

}



 void mkfile(tree* root,char name[],char path[],int nodesize)
    {

        linked pathlist;
        tree newnode = createtreenode(nodesize,0,name);
        if(nodesize > space){
            printf("No More Available Space !! \n ");
            return;
        }
        pathlist = pathscan(path);

        tree trav = *root;

        if((*root)->fils == NULL )
        {
//if(!strcmp(pathlist->name,trav->nom))
            (*root)->fils = newnode;
//else {printf("Wrong path or not found !!");}
        }

        else
        {

// loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {


                if(!strcmp(pathlist->name,trav->nom))
                {

                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }
                }
            }

            if(pathlist == NULL)      // inserting in frere last position
            {
                while(trav->frere != NULL)
                {

                    if(!strcasecmp(name,trav->nom) && trav->rep == 0 ){
                        printf("There is a File with the same name !! \n");
                        return;
                    }

                    trav = trav->frere;
                }

                     if(!strcasecmp(name,trav->nom) && trav->rep == 0 ){
                        printf("There is a File with the same name !! \n");
                        return;
                    }
                trav->frere = newnode;
                 space = space - nodesize;
            }
            else
            {
                trav->fils = newnode;
                space = space - nodesize;
            }

        }

    }











void disppatharr(char* path[],int n,int isfolder){
    if(isfolder){
printf("Folder is Found !  : ");
    }
    else if(!isfolder){
 printf("File is Found !  : ");
    }
printf("%s",path[0]);
for(int i = 1 ; i < n ; i++ ){
printf("%s/",path[i]);
}
printf("\n");

}

// "filsornot" if it is frere we will not add it to our array
void exist(char* path[],tree root,int i,char* name,int filsornot,int* found){
if(root){
if(!strcmp(root->nom,name)){
disppatharr(path,i,root->rep);
*found = 1;
}
if(!filsornot){
path[i]="";
}
path[i]=root->nom;
exist(path,root->fils,i+1,name,1,found);
exist(path,root->frere,i,name,0,found);
}
}







// to test if the path exists
int pathfound(tree root,char path[])
{
    linked pathlist;
    pathlist = pathscan(path);
    tree trav = root;

    int pathelefound;
    if((root)->fils == NULL && !strcmp(pathlist->name,trav->nom))
    {

        return 1;
    }
    else if((root)->fils == NULL && strcmp(pathlist->name,trav->nom)){return 0;}

    else
    {
        if(!pathlist) pathelefound = 0;

        else{
        pathelefound = 1;
        }
// loop to arrive last name in our path.
        while(trav!= NULL && pathlist != NULL && trav -> fils != NULL && pathelefound == 1)
        {

            pathelefound = 0;
            if(!strcmp(pathlist->name,trav->nom))
            {

                pathlist = pathlist->next;
                pathelefound = 1;
                trav = trav->fils;
            }

            if(pathlist)
            {
                while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                {
                    pathelefound = 0;
                    trav = trav->frere;
                    if(!strcmp(trav->nom,pathlist->name))pathelefound = 1;
                }
            }
        }



    }

return pathelefound;

}

    void addnodetree(tree* root,char name[],char path[],int nodesize,int isfolder)
    {
        linked pathlist;
        tree newnode = createtreenode(nodesize,isfolder,name);
        pathlist = pathscan(path);

        tree trav = *root;

        if((*root)->fils == NULL )
        {
//if(!strcmp(pathlist->name,trav->nom))
    (*root)->fils = newnode;
//else {printf("Wrong path or not found !!");}
        }
        else
        {
// loop to arrive last name in our path.
            while(trav!= NULL && pathlist != NULL && trav -> fils != NULL)
            {


                if(!strcmp(pathlist->name,trav->nom))
                {

                    pathlist = pathlist->next;
                    trav = trav->fils;
                }

                if(pathlist)
                {
                    while(trav->frere != NULL && strcmp(trav->nom,pathlist->name))
                    {
                        trav = trav->frere;
                    }
                }
            }

            if(pathlist == NULL)      // inserting in frere last position
            {
                while(trav->frere != NULL)
                {
                    trav = trav->frere;
                }
                trav->frere = newnode;
            }
            else
            {
                trav->fils = newnode;
            }
        }
    }



    linked addnodelinked(linked head,char name[])
    {
        linked newnode  = malloc(sizeof(struct nodech));
        linked traversal = head ;
        strcpy(newnode->name,name);
        newnode-> next = NULL;
        if(head == NULL)return newnode;
        else
        {
            while(traversal -> next != NULL)
            {
                traversal  = traversal->next;
            }
            traversal->next = newnode;
            return head;
        }

    }
    linked pathscan(char path[])
    {
        int oneslash =0;
        linked pathlisthead  = NULL;
        int i = 0;
        if(path[0] == '/'){
        pathlisthead = addnodelinked(pathlisthead,"/");
        i++;
        }
        int j  = 0;
        char ele[16];
        while(path[i] != '\0')
        {
            if(path[i] != '/')
            {
                oneslash  = 1;
                ele[j] = path[i];
                j++;
            }
            else if ( oneslash == 1 && path[i] == '/')
            {

                ele[j] = '\0';
                if(strcmp(ele,"\0"))
                {
                    pathlisthead = addnodelinked(pathlisthead,ele);
                }
                strcpy(ele,"\0");
                j = 0;
            }
                else if( oneslash == 0 && path[i] == '/'){
                     ele[j] = path[i];
                    j++;
                }

            i++;
        }
        ele[j] = '\0';
        if(strcmp(ele,"\0"))
        {
            pathlisthead = addnodelinked(pathlisthead,ele);
        }
        return pathlisthead;
    }


#endif // FINAL_H_INCLUDED
