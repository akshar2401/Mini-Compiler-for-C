
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bucket.h"
#include <stdbool.h>
Node * createNode(int offset, char name[], char  type[]){
    Node * node = (Node * ) malloc(sizeof(Node));
    node ->offset = offset;
    strcpy(node->name, name);
    strcpy(node->type,type);
    node->next = NULL;
    return node;

}

Bucket * createBucket() {
    Bucket * bucket = (Bucket *) malloc(sizeof(Bucket));
    bucket->count = 0;
    bucket->head = NULL;
    bucket->tail = NULL;
    return bucket;
    
}
int append(Bucket * bucket, int offset, char  name[], char type[]){
    Node * node = createNode(offset, name, type);
 

    if(bucket->count == 0){
        bucket->head = node;
        bucket->tail = node;
    }else{
        (bucket->tail)->next = node;
        bucket->tail = node;
    }
    bucket->count = bucket->count +1;
    return bucket->count;
}
int search(Bucket * bucket, char * name){
    Node * curr = bucket->head;
    int i = 0;
    while(curr != NULL){
        if(strcmp(curr->name, name) == 0){
            return i;
        }
        i++;
        curr = curr->next;
    }
    return -1;
}
Node * get(Bucket * bucket, char * name){
    Node * curr = bucket->head;
    while(curr != NULL){
        if(strcmp(curr->name, name) == 0){
           break;
        }
        curr = curr->next;
    }
    return curr;
}
bool hasElement(Bucket * bucket, char * name){
    return search(bucket, name) > -1;
}
int size(Bucket * bucket){
    return bucket->count;
}
void print(Bucket * bucket){
    if(bucket->count == 0){
        printf("Empty\n");
        return;
    }
    Node * curr = bucket->head;
    
    while (curr != NULL){
        printf("(%s, %d, %s)\n", curr->name, curr->offset, curr->type);
        curr = curr->next;
    }
}


void clearBucket(Bucket * bucket){
    
    Node * curr = bucket->head;
    while(curr != NULL){
        Node * temp = curr;
        curr = curr->next;
        free(temp);

    }
    free(bucket);
}
