#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "bucket.h"

typedef struct SymbolTable {
    int offset;
    int size;
    int count;
    int prime;
    double loadfactor;
    Bucket * entries;
    Bucket ** buckets;
} SymbolTable;

SymbolTable * createSymbolTable(unsigned int size);
int insert(SymbolTable * table, char name[], char type[]);
void printTable(SymbolTable * table);
Node * valueFor(SymbolTable * table, char * name);
bool lookup(SymbolTable * table,  char * name);
#endif
