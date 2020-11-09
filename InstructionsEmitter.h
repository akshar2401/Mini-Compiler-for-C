#ifndef INSTRUCTIONSEMITTER_H
#define INSTRUCTIONSEMITTER_H
#include "SymbolTable.h"
typedef enum Operations{
	ADD, 
	MULT, 
	SUB, 
	DIV, 
	ASSSIGN,
	EQUAL,
	NOTEQUAL,
	OR,
	AND,
	GT,
	LT,
	GTE,
	LTE,
}  Operations;

char * emitLoadForIdentifier(char * name, SymbolTable * table, char * reg);
char * emitLoadForNum(int num, char * reg);
char * emitStoreForAssignment(char * exprReg, SymbolTable * table, char * name);
char * emitBinaryInstruction(int operation, char * lreg, char * rreg, char * resultReg);
char * emitCBRInstruction(char * reg, char * lab1, char * lab2);
char * emitJumpInstruction(char * label);
#endif