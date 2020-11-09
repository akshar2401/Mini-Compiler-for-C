#ifndef LABELGENERATOR_H
#define LABELGENERATOR_H

typedef struct LabelGenerator {
    int next;
} LabelGenerator;
LabelGenerator * createLabelGenerator();

void getIfLabelName(LabelGenerator * generator,  char * labels[]);
void getWhileLabelName(LabelGenerator * generator,  char * labels[]);
void getIfElseLabelName(LabelGenerator * generator, char * labels[]);
char * getLabelString(char * label);
#endif