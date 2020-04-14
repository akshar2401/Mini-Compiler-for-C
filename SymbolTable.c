#include "SymbolTable.h"
#include "bucket.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const int PRIME_FACTOR = 153;
void freeBuckets(SymbolTable * table){
    int i;
    for(i= 0; i < table->size; i++){
        clearBucket(table->buckets[i]);

    }
    free(table->buckets);
  
}
void fillBuckets(SymbolTable * table, bool free){
    if(free == 1){
        freeBuckets(table);
    }
    table->buckets = calloc((size_t)table->size, sizeof(Bucket *));
    int i;
    for(i = 0; i < table->size; i++){
        table->buckets[i] = createBucket();
    }
}
SymbolTable * createSymbolTable(unsigned int size){
    SymbolTable * table = (SymbolTable *) malloc(sizeof(SymbolTable));
    table->offset = 0;
    table->size = size;
    table->prime = PRIME_FACTOR;
    table->count = 0;
    table->entries= createBucket();
    table->loadfactor = table->count/(double)table->size;
    fillBuckets(table, false);
    return table;
}


unsigned int computeHash(char * key, int p, int numBuckets){
    long hashVal = 0;
    int n = strlen(key);
    int i;
    for(i = 0; i < n; i++){
        hashVal += (long)pow(p, n- (i+1)) * key[i];
        
        hashVal %= numBuckets;

    }

   

    return (int) hashVal;
}
bool isPrime(int n){
    unsigned int count = 2;
    int i;
    for (i = 2; i < ((int)sqrt(n)) +1; i++){
        if (n % i == 0){
            if (i != n/i) count += 2;
            else count++;

        }
    }
    return count == 2;
}
int nextPrime(int start) {
    int i = start + 1;
    while (isPrime(i) == 0){
        i++;
    }
    return i;
}
bool resize(SymbolTable * table){
    if(table->loadfactor > 0.75){
        Bucket ** buckets = table->buckets;
        table->size = nextPrime(table->size * 2 - 1);
        table->count = 0;
        table->buckets = calloc((size_t)table->size, sizeof(Bucket *));
        int i;
        for(i = 0; i < table->size; i++){
            table->buckets[i] = createBucket();
        }
        free(buckets);
        Node * current = table->entries->head;
        while(current != NULL){
            insert(table, current->name, current->type);
            current = current->next;
        }
        return true;
    }
    return false;
}
int insert(SymbolTable * table, char name[], char type[]){
    unsigned int offset = table->offset + (4 * table->count);
    int hash = computeHash(name, table->prime, table->size);

    Bucket * bucket = table->buckets[hash];
    if(hasElement(bucket, name) == 0){
         
        append(table->entries, offset, name, type);
        append(bucket, offset, name, type);
        table->count++;
        table->loadfactor = table->count/(double)table->size;
        resize(table);// resize if loadfactor is above 0.75

        return table->count;
    }else{
        return -1;
    }
}

void printTable(SymbolTable * table){
    int i;
    for(i = 0; i < table->size; i++){
        if(size(table->buckets[i]) > 0){
            printf("Bucket %d:\n", i + 1);
            print(table->buckets[i]);
        }

    }
}

Bucket * bucket(SymbolTable * table, int number){
    return table->buckets[number];
}
Node * valueFor(SymbolTable * table, char * name){
    int hash = computeHash(name, table->prime, table->size);
    
    Bucket * res = bucket(table, hash);
    return get(res, name);
}
bool lookup(SymbolTable * table,  char * name){
    int hash = computeHash(name, table->prime, table->size);
    return hasElement(bucket(table, hash), name);
}
