#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utilities.h"
#include "LabelGenerator.h"

LabelGenerator * createLabelGenerator(){
    LabelGenerator * generator = (LabelGenerator * ) malloc(sizeof(LabelGenerator));
    generator->next = 1;
    return generator;
}
char * getLabelName(char * suffix, int labelNo){
      char * label[] = {
        "L",
        numToString(labelNo),
        "_",
        suffix
    };
    return concat(label, 4);
}
void  getIfLabelName(LabelGenerator * generator, char * labels[]){
    unsigned int label = generator->next;
    labels[0] = getLabelName("T", label);
    labels[1] = getLabelName("M", label);
    generator->next++;
}
void getWhileLabelName(LabelGenerator * generator,  char * labels[]){
    unsigned int label = generator->next;
    labels[0] = getLabelName("C", label);
    labels[1] = getLabelName("B", label);
    labels[2] = getLabelName("O", label);
    generator->next++;
}
void getIfElseLabelName(LabelGenerator * generator, char * labels[]){
    unsigned int label = generator->next;
    labels[0] = getLabelName("T", label);
    labels[1] = getLabelName("E", label);
    labels[2] = getLabelName("M", label);
    generator->next++;
}
char * getLabelString(char * label){
    char * string [] = {
        label,
        ":\n"
    };
    return concat(string, 2);
}