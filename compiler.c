#include "compiler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "Utilities.h"
#include "registerGenerator.h"
#include "InstructionsEmitter.h"
#include "LabelGenerator.h"


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
        ASTNode * node = getNode();
        node->type = ASTNODE_STMT;
        node->left = st;
        node->right = stList;
        printf("Adding a Statement to a Statement list\n");
        return node;
}


void addDeclaration(char * name){
        if(table == NULL){
                table = createSymbolTable(1229);
        }
        const int status = insert(table, name, "int");
        
        if(status == -1){
                char prefix[] = "Multiple declarations of ";
                char * message = calloc(strlen(name) + strlen(prefix) + 4, sizeof(char));
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
        ASTNode * ifelseBodyNode = getNode();
        ifelseBodyNode->type = ASTNODE_IFELSELOOPBODY;
        ifelseBodyNode->left = right;
        ifelseBodyNode->right = next;
        node->right = ifelseBodyNode;
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

char * generateCode(ASTNode * node, RegisterGenerator* regGen, LabelGenerator * labGen, FILE * output){
    char * lreg = NULL;
    char * rreg = NULL;
    char * reg = NULL;
    char * labels []= {"", "", "", ""};
    switch(node->type){
        case ASTNODE_IDENT:
            reg = generate(regGen);
            fputs(emitLoadForIdentifier(node->name, table, reg), output);
            return reg;
        case ASTNODE_NUM:
            reg = generate(regGen);
            fputs(emitLoadForNum(node->num, reg), output);
            return reg;
        case ASTNODE_ASSIGN:
            rreg = generateCode(node->right, regGen, labGen, output);
            fputs(emitStoreForAssignment(rreg, table, node->left->name), output);
            return "";
        case ASTNODE_STMT:
            generateCode(node->left, regGen, labGen, output);
            if(node->right){
                generateCode(node->right, regGen, labGen,output);
            }
            return "";
        case ASTNODE_ARITH_OP:
        case ASTNODE_COMPARE:
        case ASTNODE_LOGIC_OP:
            lreg = generateCode(node->left, regGen, labGen,output);
            rreg = generateCode(node->right, regGen,labGen,output);

            reg = generate(regGen);
            fputs(emitBinaryInstruction((int) node->op, lreg, rreg, reg), output);
            return reg;
        case ASTNODE_IF:
            getIfLabelName(labGen, labels);
            lreg = generateCode(node->left, regGen, labGen,output);
            fputs(emitCBRInstruction(lreg, labels[0], labels[1]), output);
            fputs(getLabelString(labels[0]), output);
            generateCode(node->right, regGen, labGen,output);
            fputs(getLabelString(labels[1]), output);
            return "";
        case ASTNODE_WHILE:
            getWhileLabelName(labGen,labels);
            fputs(getLabelString(labels[0]), output);
            lreg  = generateCode(node->left, regGen, labGen,output);
            fputs(emitCBRInstruction(lreg, labels[1], labels[2]), output);
            fputs(getLabelString(labels[1]), output);
            generateCode(node->right, regGen, labGen,output);
            fputs(emitJumpInstruction(labels[0]), output);
            fputs(getLabelString(labels[2]),output);
            return "";
        case ASTNODE_IFELSE:
            getIfElseLabelName(labGen, labels);
            lreg = generateCode(node->left, regGen, labGen, output);
            fputs(emitCBRInstruction(lreg, labels[0], labels[1]), output);
             fputs(getLabelString(labels[0]), output);
            generateCode(node->right->left, regGen, labGen,output);
            fputs(emitJumpInstruction(labels[2]), output);
            fputs(getLabelString(labels[1]), output);
            generateCode(node->right->right, regGen, labGen,output);
            fputs(getLabelString(labels[2]), output);
            return "";
        default:
            return "";
    }
}
void GenerateILOC(ASTNode* node, FILE * output){
        RegisterGenerator * regGen = createRegisterGenerator();
        LabelGenerator * labelGen = createLabelGenerator();
        if(node == NULL){
	  fputs("", output);
	} else{
	        generateCode(node, regGen, labelGen, output);
	}
        fclose(output);
}
