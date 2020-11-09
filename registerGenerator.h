#ifndef REGISTERGENERATOR_H
#define REGISTERGENERATOR_H
typedef struct RegisterGenerator {
    int next;
} RegisterGenerator;

RegisterGenerator * createRegisterGenerator();
char * generate(RegisterGenerator * generator);
#endif