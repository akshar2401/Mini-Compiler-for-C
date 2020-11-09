#include "registerGenerator.h"
#include <stdlib.h>
#include <string.h>
#include "Utilities.h"
#include <stdio.h>
RegisterGenerator * createRegisterGenerator(){
    RegisterGenerator * generator = (RegisterGenerator * ) malloc(sizeof(RegisterGenerator));
    generator->next = 1;
    return generator;
}

char * generate(RegisterGenerator * generator){
   unsigned int currRegister = generator->next;
   generator->next++;
   char * number = numToString(currRegister);
    char * name = (char * ) calloc(1  + strlen(number) + 2, sizeof(char));
    strcat(name, "r");
    strcat(name, number);
    free(number);
   return name;
}

