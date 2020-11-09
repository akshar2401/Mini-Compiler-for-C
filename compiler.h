#ifndef COMPILER
#define COMPILER
#include <stdio.h>
#include "SymbolTable.h"
typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_IFELSE,ASTNODE_WHILE, ASTNODE_STMT, ASTNODE_IFELSELOOPBODY} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum{
	ADD_OP, 
	MULT_OP, 
	SUB_OP, 
	DIV_OP, 
	ASSSIGN_OP,
	EQUAL_OP,
	NOTEQUAL_OP,
	OR_OP,
	AND_OP,
	GT_OP,
	LT_OP,
	GTE_OP,
	LTE_OP,
	} ASTOp; 



typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type; 
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child
	
	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // a pointer used to link statement nodes together in a statement list

// Depending on your implementation, you may need to add other fields to this struct 

};


// Add functions to create the different kinds of ASTNodes 
// These functions are called by the code embedded in the grammar.
// Here are some samples:  
ASTNode* CreateNumNode(int num);
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateArithmeticOpNode(ASTNode * left, ASTNode * right, ASTOp op);
ASTNode * CreateAssignmentNode(ASTNode * left, ASTNode * right);
ASTNode * CreateLHSNode(char * name);
void addDeclaration(char * name);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode * CreateCompareNode(ASTNode* left, ASTOp op, ASTNode * right);
ASTNode * CreateLogicalNode(ASTNode * left, ASTOp op, ASTNode * right);
ASTNode * CreateIFNode(ASTNode * left, ASTNode * right);
ASTNode * CreateIfElseNode(ASTNode * left, ASTNode * right, ASTNode * next);
ASTNode * CreateWhileNode(ASTNode* left, ASTNode * right);
//ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);

// Need a function to add a declaration to your symbol table
//void AddDeclaration(char* name);

// This is the function that generates ILOC code after the construction of the AST
void GenerateILOC(ASTNode* node, FILE * output);
#endif
