#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "Utilities.h"
#include "InstructionsEmitter.h"

char * getInstructionForOperation(Operations operation){
    switch(operation){
        case ADD:
            return "add";
        case MULT:
            return "mult";
        case DIV:
            return "div";
        case SUB:
            return "sub";
        case EQUAL:
            return "cmp_EQ";
        case NOTEQUAL:
            return "cmp_NE";
        case LT:
            return "cmp_LT";
        case GT:
            return "cmp_GT";
        case LTE:
            return "cmp_LE";
        case GTE:
            return "cmp_GE";
        case AND:
            return "and";
        case OR:
            return "or";
        default:
            return "";
    }
}

char * emitLoadForIdentifier(char * name, SymbolTable * table, char * reg){
    Node * symbolNode = valueFor(table, name);
    char * instruction[] = {
        "    loadAI rarp, ",
        numToString(symbolNode->offset),
        " -> ",
        reg,
        "\n"

    };
    return concat(instruction, 5);
}
char * emitLoadForNum(int num, char * reg){
    char * instruction[] = {
        "    loadi ",
        numToString(num),
        " -> ",
        reg,
        "\n"
     
    };
    return concat(instruction, 5);
}
char * emitStoreForAssignment(char * exprReg, SymbolTable * table, char * name){
    char * instruction [] = {
        "    storeAI ",
        exprReg,
        " -> rarp, ",
        numToString(valueFor(table, name)->offset),
        "\n"
    };
    return concat(instruction, 5);
}
char * emitBinaryInstruction(int operation, char * lreg, char * rreg, char * resultReg){
    char * instruction [] = {
        "    ",
        getInstructionForOperation(operation),
        " ",
        lreg,
        ", ",
        rreg,
        " -> ",
        resultReg,
        "\n"
    };
    return concat(instruction, 9);
}
char * emitCBRInstruction(char * reg, char * lab1, char * lab2){
    char * instructions[] = {
        "    cbr ",
        reg,
        " -> ",
        lab1,
        ", ",
        lab2,
        "\n"
    };
    return concat(instructions, 7);
}
char * emitJumpInstruction(char * label){
    char * instruction []= {
        "    jumpi -> ",
        label,
        "\n"
    };
    return concat(instruction, 3);
}