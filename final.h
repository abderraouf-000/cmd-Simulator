#include "string.h"
#ifndef FINAL_H_INCLUDED
#define FINAL_H_INCLUDED

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







int commandseparator(char command[],char* parts[])
{
// let 0 ind for the path name and 1 for cmdname ,2 for file name,3 for size (only fichier) ,
// we will use path scan for the path
    int n  = 3;
    for(int i = 0 ; i < n ; i++)
    {
        strcpy(parts[i],"");
    }



    int k = 0;
    int i = 0;
    int j  = 0;
    char ele[50];

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
//            printf("%s",ele);
            if(strcmp(ele,""))
            {
                strcpy(parts[k],ele);
                strcpy(ele,"\0");
                k++;
            }
            j = 0;
        }

        i++;
    }
    ele[j] = '\0';
    strcpy(parts[k],ele);

    for(int i = 0 ; i < n ; i++)
    {
        printf("%s\n",parts[i]);
    }


}



// function to add nodes to tree !!!
// problem it displays the first fils !!!
void treeinit(tree* rootc)
{
    addnodetree(&(*rootc),"home","/",20,1);
    addnodetree(&(*rootc),"bin","/",20,1);
    addnodetree(&(*rootc),"root","/",20,1);
    addnodetree(&(*rootc),"run","/",20,1);
    addnodetree(&(*rootc),"telechargement","/",20,1);
    addnodetree(&(*rootc),"Univ8mai1945","/home",20,1);
//    addnodetree(&(*rootc),"Bureau","/home/Univ8mai1945",20,1);
    addnodetree(&(*rootc),"Documents","/home/Univ8mai1945",20,1);
    addnodetree(&(*rootc),"telechargement","/home/Univ8mai1945",20,1);
//    addnodetree(&(*rootc),"telechargement","/home/Univ8mai1945",20,1);
    addnodetree(&(*rootc),"telechargement","/home/Univ8mai1945/Documents",20,1);
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



int pathsize(linked pathlist){

int n = 0;
while(pathlist){
        pathlist = pathlist->next;
    n++;
}

return n;
}

void ls(tree root,char path[],char foldername[]){
    // full path holds the full path to traverse
    char fullpath[60]=  "";
    char foldernamepath[18] = "";
    strcpy(foldernamepath,foldername);
                      // adding / to folder name
    strcat(foldernamepath,"/");

    strcpy(fullpath,path);
    strcat(fullpath,foldernamepath);

    linked pathlist;
    tree trav = root;
    printf("%s\n",fullpath);
    pathlist = pathscan(fullpath);
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
void disppatharr(char* path[],int n){

printf("\n");
printf("%s",path[0]);
for(int i = 1 ; i < n ; i++ ){
printf("%s/",path[i]);
}
printf("\n");

}
// "filsornot" if it is frere we will not add it to our array
void exist(char* path[],tree root,int i,char* name,int filsornot){

if(root){


if(!strcmp(root->nom,name)){
disppatharr(path,i);
}



if(!filsornot){
path[i]="";
}

path[i]=root->nom;
//printf("path %s , %d \n",path[i],i);






exist(path,root->fils,i+1,name,1);
exist(path,root->frere,i,name,0);
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
        pathelefound = 1;

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
