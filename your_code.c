#include "your_code.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SymbolTable.h"


// Write the implementations of the functions that do the real work here
SymbolTable * table = NULL;
int yyerror(const char * );
ASTNode * getNode(){
        return (ASTNode * ) malloc(sizeof(ASTNode));
}
ASTNode* CreateNumNode(int num)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_NUM; 
        node->num = num;
        return node;
}


ASTNode* CreateIdentNode(char* name)
{       
        if(table == NULL || lookup(table, name) == 0){
                yyerror("Ident not declared");
        }
        ASTNode* identNode = (ASTNode * ) malloc(sizeof(ASTNode));
        identNode->name = name;
        identNode->type = ASTNODE_IDENT;
        return identNode;
        

}
ASTNode * CreateLHSNode(char * name){

  ASTNode * node  = CreateIdentNode(name);
  printf("Creating left-hand IDENT node for %s\n", name);
  return node;
}
void getOperation(ASTOp op, char operation []){
        switch(op){
                case ADD_OP:
                        strcpy(operation, "Addition");
                        break;
                case MULT_OP:
                        strcpy(operation, "Multiplication");
                        break;
                case SUB_OP:
                        strcpy(operation, "Subtraction");
                        break;
                case DIV_OP:
                        strcpy(operation, "Division");
                        break;
                case ASSSIGN_OP:
                        strcpy(operation, "Assignment");
                        break;
                case OR_OP:
                        strcpy(operation, "OR");
                        break;
                case AND_OP:
                        strcpy(operation, "AND");
                        break;
                default:
                        strcpy(operation, "");
                        break;
        }
      
}

ASTNode * createBinaryOPNode(ASTOp op, ASTNode * left, ASTNode * right){
        ASTNode * node = getNode();
        node->type = ASTNODE_ARITH_OP;
        node->op = op;
        node->left =left;
        node->right = right;
        return node;
}
ASTNode * CreateArithmeticOpNode(ASTNode * left, ASTNode * right, ASTOp op){
        ASTNode * node = createBinaryOPNode(op, left, right);
        char operation [100];
        getOperation(op, operation);
        printf("Creating %s node\n", operation);
        return node;
}
ASTNode * CreateAssignmentNode(ASTNode * left, ASTNode * right){
        ASTNode * node = getNode();
        node->type = ASTNODE_ASSIGN;
        node ->left = left;
        node->right = right;
        char operation[100];
        getOperation(ASSSIGN_OP, operation);

        printf("Creating %s node\n", operation);
        return node;
}
// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList)
{
        st->next =  stList;
        printf("Adding a Statement to a Statement list\n");
        return st;
}


void addDeclaration(char * name){
        if(table == NULL){
                table = createSymbolTable(1229);
        }
        const int status = insert(table, name, "int");
        
        if(status == -1){
                char prefix[] = "Multiple declarations of ";
                char * message = calloc(strlen(name) + strlen(prefix) + 2, sizeof(char));
                strcpy(message, prefix);
                strcat(message, "'");
                strcat(message, name);
                strcat(message, "'");

                yyerror(message);
                free(message);
        }else
        {       
                printf("Processing declaration of %s\n", name);
        }
        
}
ASTNode * CreateCompareNode(ASTNode* left, ASTOp op, ASTNode * right){
        ASTNode * node = getNode();
        node->type = ASTNODE_COMPARE;
        node->op = op;
        node->left = left;
        node->right = right;
        printf("Creating Compare node\n");
        return node;

}
ASTNode * CreateLogicalNode(ASTNode * left, ASTOp op, ASTNode * right){
        ASTNode * node = getNode();
        node->type = ASTNODE_LOGIC_OP;
        node->op = op;
        node->left = left;
        node->right = right;
        char operation[100];
        getOperation(op, operation);
        printf("Creating %s node\n", operation);
        return node;
}
ASTNode * CreateIFNode(ASTNode * left, ASTNode * right){
        ASTNode * node = getNode();
        node->type = ASTNODE_IF;
        node->left = left;
        node->right = right;
        printf("Creating if Statement node\n");
        return node;
}
ASTNode * CreateIfElseNode(ASTNode * left, ASTNode * right, ASTNode * next){
        ASTNode * node = getNode();
        node->type = ASTNODE_IFELSE;
        node->left = left;
        node->right = right;
        node->next = next;
        printf("Creating if-else Statement node\n");
        return node;
}

ASTNode * CreateWhileNode(ASTNode* left, ASTNode * right){
        ASTNode * node = getNode();
        node->type = ASTNODE_WHILE;
        node->left = left;
        node->right = right;
        printf("Creating while loop node\n");
        return node;
}
// Commented out in this assignment 
/*void GenerateILOC(ASTNode* node);
{

}*/

