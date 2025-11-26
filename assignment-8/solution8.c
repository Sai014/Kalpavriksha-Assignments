#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define TABLE_SIZE 1000

typedef struct Node
{
    int key;
    char value[20];
    struct Node *prev;
    struct Node *next;
}Node;

typedef struct Cache
{
    int capacity;
    int size;
    struct Node *head;
    struct Node *tail;
    struct Node *map[TABLE_SIZE];
}Cache;

Cache *cache=NULL;

void createCache(int capacity);
void putInCache(int key, char *value);
void getFromCache(int key);
void moveToHead(Cache *cache, Node *node);
void insertAtHead(Cache *cache, Node *node);
Node *removeTail(Cache *cache);

int main()
{
    char command[20];
    int args1;
    char args2[20];
    printf("Input\n");
    while(1)
    {
        fgets(command,sizeof(command),stdin);
        if(command[strlen(command)-1]=='\n')command[strlen(command)-1]='\0';

        if(strcmp(command,"exit")==0)exit(0);
        else if(sscanf(command,"createCache %d",&args1)==1)createCache(args1);
        else if(sscanf(command,"put %d %s",&args1,args2)==2)putInCache(args1,args2);
        else if(sscanf(command,"get %d",&args1)==1)getFromCache(args1);
    }
}

void createCache(int capacity)
{
    cache=malloc(sizeof(Cache));
    cache->capacity=capacity;
    cache->size=0;
    cache->head=cache->tail=NULL;

    for(int i=0;i<TABLE_SIZE;i++)
    {
        cache->map[i]=NULL;
    }
}

void putInCache(int key, char *value)
{
    Node *node=cache->map[key];
    if(node!=NULL)
    {
        strcpy(node->value,value);
        moveToHead(cache,node);
        return;
    }
    Node *newNode=malloc(sizeof(Node));
    newNode->key=key;
    strcpy(newNode->value,value);
    newNode->next=newNode->prev=NULL;

    insertAtHead(cache,newNode);
    cache->map[key]=newNode;
    cache->size++;

    if(cache->size>cache->capacity)
    {
        Node *removedNode=removeTail(cache);
        cache->map[removedNode->key]=NULL;
        free(removedNode);
        cache->size--;
    }

}

void getFromCache(int key)
{
    Node *node=cache->map[key];
    if(!node)
    {
        printf("NULL\n");
        return;
    }
    moveToHead(cache,node);
    printf("%s\n",node->value);

}

void moveToHead(Cache *cache, Node *node)
{
    if(cache->head==node)return;
    if(node->prev)node->prev->next=node->next;
    if(node->next)node->next->prev=node->prev;
    if(cache->tail==node)cache->tail=node->prev;

    node->prev=NULL;
    node->next=cache->head;
    if(cache->head)cache->head->prev=node;
    cache->head=node;
    if(cache->tail==NULL)cache->tail=node;
}

void insertAtHead(Cache *cache, Node *node)
{
    node->prev=NULL;
    node->next=cache->head;
    if(cache->head)cache->head->prev=node;
    cache->head=node;
    if(cache->tail==NULL)cache->tail=node;
}

Node *removeTail(Cache *cache)
{
    Node *tail=cache->tail;
    if(!tail)return NULL;
    if(tail->prev)tail->prev->next=NULL;
    cache->tail=tail->prev;
    if(cache->tail==NULL)cache->head=NULL;
    return tail;
}