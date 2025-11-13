#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define NUM_BLOCKS 100
#define BLOCK_SIZE 512
#define MAX_NAME 40

typedef struct freeBlock
{
    int index;
    struct freeBlock *next;
}freeBlock;

typedef struct fileNode
{
    char name[MAX_NAME];
    int isDirectory;
    struct fileNode *next;
    struct fileNode *prev;
    struct fileNode *child;
    struct fileNode *parent;
    int blockIndex[50];
    int blockCount;
    int size;
}fileNode;

char virtualDisk[NUM_BLOCKS][BLOCK_SIZE];
freeBlock *freeMemoryBlocks=NULL;
fileNode *root=NULL;
fileNode *cwd=NULL;

fileNode* createNode(char *name,int isDir);
void initFreeMemoryBlocks();
fileNode* findNode(fileNode *cwd,char *name);
void addChild(fileNode *parent, fileNode *child);
void freeMemoryBlock(int index);
int allocateBlock();
void mkdirCmd(char *name);
void createCmd(char *name);
void writeCmd(char *name,char *data);
void readCmd(char *name);
void deleteCmd(char *name);
void rmdirCmd(char *name);
void lsCmd();
void cdCmd(char *name);
void pwdCmd();
void dfCmd();

int main()
{
    root=createNode("/",1);
    cwd=root;
    initFreeMemoryBlocks();

    char command[50],arg1[20],arg2[50];
    
    printf("VFS Ready!\n");
    while(1)
    {
        printf("/>");
        fgets(command,sizeof(command),stdin);
        if(command[strlen(command)-1]=='\n')command[strlen(command)-1]='\0';

        if(strcmp(command,"exit")==0)break;
        else if(sscanf(command,"mkdir %s",arg1)==1)mkdirCmd(arg1);
        else if(sscanf(command,"create %s",arg1)==1)createCmd(arg1);
        else if (sscanf(command, "write %s \"%[^\"]\"", arg1, arg2) == 2) writeCmd(arg1, arg2);
        else if (sscanf(command, "read %s", arg1) == 1) readCmd(arg1);
        else if (sscanf(command, "delete %s", arg1) == 1) deleteCmd(arg1);
        else if (sscanf(command, "rmdir %s", arg1) == 1) rmdirCmd(arg1);
        else if (sscanf(command, "cd %s", arg1) == 1) cdCmd(arg1);
        else if (strcmp(command, "ls") == 0) lsCmd();
        else if (strcmp(command, "pwd") == 0) pwdCmd();
        else if (strcmp(command, "df") == 0) dfCmd();
        else printf("Unknown command.\n");
    }
}

fileNode* createNode(char *name,int isDir)
{
    fileNode* node=malloc(sizeof(fileNode));
    strcpy(node->name,name);
    node->isDirectory=isDir;
    node->child=NULL;
    node->parent=NULL;
    node->next=NULL;
    node->prev=NULL;
    return node;
}

void initFreeMemoryBlocks()
{
    for(int i=0;i<NUM_BLOCKS;i++)
    {
        freeBlock* node=malloc(sizeof(freeBlock));
        node->index=i;
        node->next=freeMemoryBlocks;
        freeMemoryBlocks=node;
    }
}

fileNode* findNode(fileNode *parent,char *name)
{
    fileNode *node=parent->child;
    while(node)
    {
        if(strcmp(node->name,name)==0)
        {
            return node;
        }
        node=node->next;
    }
    return NULL;
}

void addChild(fileNode *parent, fileNode *child) 
{
    child->parent = parent;
    if (!parent->child)
        parent->child = child;
    else {
        fileNode *p = parent->child;
        while (p->next) p = p->next;
        p->next = child;
    }
}

int allocateBlock() {
    if (!freeMemoryBlocks) return -1;
    int idx = freeMemoryBlocks->index;
    freeBlock *temp = freeMemoryBlocks;
    freeMemoryBlocks = freeMemoryBlocks->next;
    free(temp);
    return idx;
}

void freeMemoryBlock(int index) {
    freeBlock *node = malloc(sizeof(freeBlock));
    node->index = index;
    node->next = NULL;
    if (!freeMemoryBlocks) {
        freeMemoryBlocks = node;
        return;
    }
    freeBlock *p = freeMemoryBlocks;
    while (p->next) p = p->next;
    p->next = node;
}

void mkdirCmd(char *name)
{
    if(findNode(cwd,name))
    {
        printf("Directory already exists!\n");
        return;
    }
    fileNode *node=createNode(name,1);
    addChild(cwd,node);
    printf("Directory '%s' created.\n", name);
}

void createCmd(char *name)
{
    if(findNode(cwd,name))
    {
        printf("File already exists!\n");
        return;
    }
    fileNode *node=createNode(name,0);
    addChild(cwd,node);
    printf("File '%s' created.\n", name);
}

void writeCmd(char *name,char *data)
{
    fileNode *file=findNode(cwd,name);
    if(!file || file->isDirectory)
    {
        printf("File does not exist!\n");
        return;
    }

    for (int i = 0; i < file->blockCount; i++) {
        freeMemoryBlock(file->blockIndex[i]);
    }

    file->blockCount = 0;
    int len = strlen(data);
    int needed = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    if (needed > 50) {
        printf("File too large.\n");
        return;
    }

    for (int i = 0; i < needed; i++) {
        int idx = allocateBlock();
        if (idx == -1) {
            printf("Disk full.\n");
            return;
        }
        file->blockIndex[i] = idx;
        file->blockCount++;
        int start = i * BLOCK_SIZE;
        strncpy(virtualDisk[idx], data + start, BLOCK_SIZE);
    }
    file->size = len;
    printf("Written %d bytes to '%s'.\n", len, name);
}

void readCmd(char *name)
{
    fileNode *file=findNode(cwd,name);
    if(!file || file->isDirectory)
    {
        printf("File does not exist!\n");
        return;
    }
    printf("Contents of %s: \n",name);
    for(int i=0;i<file->blockCount;i++)
    {
        printf("%s",virtualDisk[file->blockIndex[i]]);
    }
    printf("\n");
}

void deleteCmd(char *name)
{
    fileNode *prev = NULL, *curr = cwd->child;
    while (curr && strcmp(curr->name, name)!= 0) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr || curr->isDirectory) {
        printf("File not found.\n");
        return;
    }

    for (int i = 0; i < curr->blockCount; i++)
        freeMemoryBlock(curr->blockIndex[i]);

    if (prev) prev->next = curr->next;
    else cwd->child = curr->next;

    free(curr);
    printf("File deleted.\n");
}

void rmdirCmd(char *name) {
    fileNode *prev = NULL, *curr = cwd->child;
    while (curr && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr || !curr->isDirectory) {
        printf("Directory not found.\n");
        return;
    }
    if (curr->child) {
        printf("Directory not empty.\n");
        return;
    }
    if (prev) prev->next = curr->next;
    else cwd->child = curr->next;
    free(curr);
    printf("Directory removed.\n");
}

void lsCmd() {
    fileNode *node = cwd->child;
    if (!node) {
        printf("(empty)\n");
        return;
    }
    while (node) {
        printf("%s%s\n", node->name, node->isDirectory ? "/" : "");
        node = node->next;
    }
}

void cdCmd(char *name) {
    if (strcmp(name, "..") == 0) {
        if (cwd->parent) cwd = cwd->parent;
        return;
    }
    fileNode *node = findNode(cwd, name);
    if (!node || !node->isDirectory) {
        printf("Directory not found.\n");
        return;
    }
    cwd = node;
}

void pwdCmd() {
    char path[500] = "";
    fileNode *node = cwd;
    while (node) {
        char temp[500];
        sprintf(temp, "/%s%s", node->name, path);
        strcpy(path, temp);
        node = node->parent;
    }
    printf("%s\n", *path ? path : "/");
}

void dfCmd() {
    int used = 0;
    freeBlock *node = freeMemoryBlocks;
    while (node) {
        used++;
        node = node->next;
    }
    printf("Total: %d, Free: %d, Used: %d\n", NUM_BLOCKS, NUM_BLOCKS - used, used);
}