//this header file contains useful func
#ifndef _UTIL_H_
#define _UTIL_H_

//generate a rand string with lenght = max_c
void rand_string(char *s, int max_c);

//sum of the char of a string (doesn't count \0)
int sum_string(char *s);

//sum of an integer vector
int sum_integers(int *v,int n);

#endif