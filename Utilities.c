#include "Utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int getDigitCount(int num){
    int count = 0;
    while (num > 0){
        num /= 10;
        count++;
    }
    return count;

}
char * numToString(int num){
    char * numString = (char * ) calloc(getDigitCount(num) + 3, sizeof(char));
    sprintf(numString, "%d", num);
    return numString;
}
char * concat(char * strings[], int n) {
    
    int i;
    
    int totalLength = 0;
    for(i = 0; i < n; i++){
        totalLength += strlen(strings[i]) + 1;
    }
    char * res = (char * ) calloc(totalLength, sizeof(char));
    
    for(i = 0; i < n; i++){
        strcat(res, strings[i]);
    }
    return res;
}
