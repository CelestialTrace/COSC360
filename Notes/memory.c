#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

#include <errno.h>
//errno is an integer to classify error type

//usr/include/errno.h

//mmap : place file into memory
//mmap: use it when you need to protect the memory, link memory space with a file else we read from a string
mem = mmap(NULL, 120, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, 0, 0);
perror("mmap");
//return void* which is a generic pointer, it can be any type
//void* addr, where heap starts, normally put null since linux can ignore this command
//size_t length : size

//prot: protection, PROT_EXEC, PROT_READ, PROT_WRITE, PROT_NONE
//format in parameter: PROT_READ | PROT_WRITE | PROT_EXEC


//flags:
// MAP_ANONYMOUS:hand memory if want to read from memory, doesn't write back to file, no backing storage 
// MAP_SHARED: share across all thread, write back to the file
// MAP_PRIVATE : write to memory Not to the file, 
// MAP_FIXED : fix the memory at an address else an error, 
// MAP_STACK : create a stack, no backing file

//file descriptor, number that operating system use to determine where to output, std out, err, file, etc...
//offset

//void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
//map entire file into memory address space

//use virtual memory instead of physical, for protection: r, w, x, and continous memory
// mmap divide storage by page size, which is 5^12 byte

munmap(mem, 120);
//deallocate  mmap


#include <stdint.h>
//provide:
//int8_t : 8bits signed
//uint8_t : 8bits unsigned
//int64_t : 64bits signed

struct myStruct{
    int i;
    int j;
    int k;
};

//typedef (structure type) (data type)
//alias a type for easier code
typedef struct myStruct myStruct;

//combine typedef and struct into 1 line
typedef struct myS{
    int a;
    int b;
    int c;
} myS;

//in C when you create structure it doesn't create a type, so you have to
//use typedef to specify
int main(){
    //before typedef syntax of struct: struct myStruct *ms;
    myStruct *ms; //pointer of 8bytes holding memory address of struct
    //struct myStruct ms; //created/allocated on the stack
    //struct myStruct *ms; //created memory address/pointer

    //with typedef
    myS mS;
    mS.i = 100;


    ms = (struct myStruct*)malloc(sizeof(*ms));
    //(type cast)malloc(size)
    //malloc will return void* 
    //if you went to memory address allocated by malloc, you can't assume it's 0


    //print: sizeof(ms) = 8 byte : memory address of struct
    //print: sizeof(*ms) = 12 byte : the structure its point to

    //if ms is at 1000, 
    //ms++ will advance the heap pointer by 12 which is the size of ms

    //is ms++ is placed before free, then it will segfault
    free(ms);


    //calloc: clears your memory to 0
    ms = (struct myStruct*)calloc(10, sizeof(ms));
    //allocate 120 bytes and clear it to 0
    //calloc hands back a pointer to the first memory address    

    //ms[2].i : base + offset * size
    //if base = 1000, given above: offset is 2, size = 12
    //it have to do it for both "ms[2]" and ".i"


    //stack starts at top(very large address), allocate on stack subtracts 
    //heap starts at bottom, move up when allocating

    //calloc = new obj[#];
    //malloc = new obj;

    //malloc/calloc is user space function, have to ask system for memory

    //malloc, calloc: to check if they hand back valid memory address, check if return pointer is null
    //mmap is not a c function so it will not return null, it will return -1 
}