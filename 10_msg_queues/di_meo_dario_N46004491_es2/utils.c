#include "utils.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void rand_string(char *s, int max_c){
    int i;
    for(i = 0; i<max_c; i++){
        s[i] = 'a' + (rand()%26);
    }
    s[i] = '\0';
}   
//sum of the char of a string (doesn't count \0)
int sum_string(char *s){
    int sum = 0;
    int i = 0;
    while(s[i] != '\0'){
        sum += s[i++];
    }
    return sum;
}
//sum of an integer vector
int sum_integers(int *v,int n){
    int sum = 0;
    int i=0;
    for(i = 0; i<n; i++){
        sum += v[i];
    }
    return sum;
}