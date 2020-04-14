#ifndef BUCKET_H
#define BUCKET_H
#include <stdbool.h>

#define MAX_LENGTH 1000
typedef struct Node {
    int offset;
    char name[MAX_LENGTH];
    char  type[MAX_LENGTH];
    struct Node * next;
} Node;

typedef struct Bucket{
    int count;
    Node * head;
    Node * tail;
} Bucket;

Bucket * createBucket();
int search(Bucket * bucket, char * name);
int append(Bucket * bucket, int offset, char * name, char * type);
bool hasElement(Bucket * bucket, char * name);
int size(Bucket * bucket);
Node * get(Bucket * bucket, char * name);
void print(Bucket * bucket);
void clearBucket(Bucket * bucket);
#endif
