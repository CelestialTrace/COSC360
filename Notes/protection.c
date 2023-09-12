#include <stdlib.h>
#include <stdio.h>


typedef struct myStruct{
    int a;
    int b;
    int c;
    int *p;
} myStruct;

void dosomething(struct myS *ms);

void *memcpy(void *dist, const void *src, int size);
//if memory location of source and dist overlap then it will be undefined
//use for file buffer later
//copy byte by byte
//when copy over opaque structure where it's byte structure is unknown use memcopy over assignment operator


void *memmove(void *dist, const void *src, int size);
//also copy memory from one location into another, but memory allow overlap

void *memset(void *dist, char val, int size);
//it's char because it's 1 byte, it set variable byte by byte

//opaque structure, use pointer, there is no pass by reference
//if main have no access to structure's definition, then use a pointer
int main(){

    myStruct ms1; 
    myStruct ms2; 
   
    ms1.a = 100;
    ms1.b = 200;
    ms1.c = 300;

    ms2 = ms1;

    // memcpy(&ms2, &ms1, sizeof(myStruct));

    ms1.p = calloc(1, sizeof(int));

    *ms1.p = 300;
    printf(*ms1.p, *ms2.p);
    //both 300

    *ms2.p = 400;
    //now both, both would actually 400, NOT 300 400 
    //because memcpy is a shallow copy, where it doesn't allocate memory for a separate structure
    //memcpy 


    memset(ms1.p, 1, sizeof(*ms1.p));
    //deference ms1.p because at the location it's an int which is 4 byte, not an 8 byte generic pointer
    //above would set the 4 byte pointer at the dist, 1 byte at a time for each of the 4 byte to 1,
    // if were to be printed it would be 00000001 4 times, 
    //print *ms1.p = 1 + 1^8 + 1^16 + 1^24


    fread(dist, nmemb, size, fl);
    
    //to set up private functions:
    //forward declare the structure in .h and put definition in separate .c file(not main), instead of handing the definition itself to main by putting definition in .h
    //since there is no object, access protection, or class in C
}