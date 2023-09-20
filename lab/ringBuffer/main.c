#include <stdio.h>
#include <string.h>
#include "rbuf.h"

#define CAP 5

int main() {
    struct RingBuffer *rb = rb_new(CAP);
    char bytes[CAP];
    int n;
    char c;

    rb_push(rb, 'A');
    rb_push(rb, 'l');
    rb_push(rb, 'p');
    rb_push(rb, 'h');
    rb_push(rb, 'a');

   
    // rb_pop(rb, &c);
    // printf("rb_pop: popped '%c'\n", c);
    rb_push(rb, 'D');
    rb_push(rb, 'o');
    rb_push(rb, 'g');

    rb_pop(rb, &c);
    printf("rb_pop: popped '%c'\n", c);

    n = rb_read(rb, bytes, CAP + 5);

    printf("rb_read: returned %d bytes '%.*s'\n", n, n, bytes);


    n = rb_write(rb, "Hello World", strlen("Hello World"));

    printf("rb_write: wrote %d bytes.\n", n);

    n = rb_read(rb, bytes, CAP);

    printf("rb_read: returned %d bytes '%.*s'\n", n, n, bytes);

    
    printf("%c\n", rb_peek(rb));

    rb_free(rb);

    rb_free(rb);

    return 0;
}

//NOTES:
//read ringbuffer of the data you gave to buffer

/*FIFO
 push add from back, doesn't increment at 
 pop from the front, increment at pointer to the next element that was pushed
 */
 
//ignore same as clear the size

//read: split into 2 section, after the at pointer then before the at pointer
/*
 "at" specify where start reading, 
 index is based on at, at indicate the start
 use memcpy right then left
 buffer + bytes read already, 
 right: beginning buffer +rb at, size: capacity - at
 left: at + size, total capacity - at, size cal:maxbyte -( capacity - at)

 (at + size) % capacity = end point of push
 */

/*read: move at pointer to read
  write: doesn't affect at pointer
*/

/*capacity of rb never change, if it run out of space it just does
use memcpy for read and write not push and pop
*/