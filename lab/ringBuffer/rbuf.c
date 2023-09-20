/*
the rbuf program creates a circular buffer and support functions such as push, pop, read, write, etc..

Ring Buffer program
name: Zichen Fu
date: 9/19/23
*/
#include "rbuf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
the ring buffer structure contain info about ring buffer as well as the memory
holding the values of ring buffer
*/
struct RingBuffer
{
    int at;
    int size;
    int capacity;
    int __reserved;
    char *buffer;
};

/*create the rb struct in memory as well as memory for its values*/
struct RingBuffer *rb_new(int capacity)
{
    struct RingBuffer *rb;
    if (capacity <= 0) {
        // Capacity is invalid.
        return NULL;
    }
    if (!(rb = (struct RingBuffer *)malloc(sizeof(*rb)))) {
        // Out of memory.
        return NULL;
    }
    // If we get here, all is well with the memory.
    rb->at = 0;
    rb->size = 0;
    rb->capacity = capacity;
    rb->buffer = (char *)calloc(rb->capacity, sizeof(char));
    if (!rb->buffer) {
        // We were able to create the structure in memory,
        // but not the buffer. We need both, so free the
        // structure and return NULL (error).
        free(rb);
        return NULL;
    }
    return rb;
}

/*free the memory allocated for rb struct and memory of its value*/
void rb_free(struct RingBuffer *rb)
{
    free(rb->buffer);
    free(rb);
}

/*return the at index, which indicates the first element of the ring buffer*/
int rb_at(const struct RingBuffer *rb){
    return rb->at;
}

int rb_size(const struct RingBuffer *rb)
{
    return rb->size;
}

int rb_capacity(const struct RingBuffer *rb){
    return rb->capacity;
}

/*push element after the last element of rb*/
bool rb_push(struct RingBuffer *rb, char data){
    if(rb->size != rb->capacity){
        int Index = (rb->at + rb->size) % rb->capacity;
        rb->buffer[Index] = data;
        rb->size += 1;
    }else{
        return false;
    }
}

/*pop element at the "at" index, then decrement size by 1, increment "at" by 1*/
bool rb_pop(struct RingBuffer *rb, char *data){
    if(rb->size != 0 && rb->buffer + rb->at != NULL){
        *data = rb->buffer[rb->at];
        rb->at = (rb->at + 1) % rb->capacity;
        
        rb->size -= 1;
        return true;
    }else if(rb->size != 0){
        rb->at = (rb->at + 1) % rb->capacity;
        rb->size -= 1;
        return false;
    }else{
        return false;
    }
}

//it's up to user to verify size first before calling seek
char rb_peek(const struct RingBuffer *rb){
    if(rb->buffer + rb->at != NULL){
        return rb->buffer[rb->at];
    }else{
        return '0';
    }
}

/*ignore specified number of element in the rb by incrementing "at",
it will increment by which ever is smaller between rb's size or num
*/
void rb_ignore(struct RingBuffer *rb, int num){
    
    if(num > 0){
        if(num >= rb->size){
            rb->at = (rb->at + rb->size) % rb->capacity;
        }else{
            rb->at = (rb->at + num) % rb->capacity;
        }
    }
}

/*read the ring buffer and store it into buf*/
int rb_read(struct RingBuffer *rb, char *buf, int max_bytes){
    int byteRead = 0;
    /*rightByte = byte space to the right
      leftByte = byte space to the left*/
    if(max_bytes >= rb->size){/*read all of rb*/
       
        int rightByte = rb->capacity - rb->at;
        int leftOverByte = rb->size - rightByte;

        if(rb->size <= rightByte){/*only read right*/
            memcpy(buf, rb->buffer + rb->at, rb->size);
            byteRead += rb->size;
        }else{
            memcpy(buf, rb->buffer + rb->at, rightByte);
            memcpy(buf + rightByte, rb->buffer, leftOverByte);

            byteRead = rightByte + leftOverByte;
        }

        rb->at = (rb->at + rightByte + leftOverByte) % rb->capacity;
        rb->size -= rightByte + leftOverByte;
    }else{/*when you don't read all the byte in rb*/

        int rightByte = rb->capacity - rb->at; //including byte at "at"
        if(max_bytes <= rightByte){/*only read right*/
            if(memcpy(buf, rb->buffer + rb->at, max_bytes) != NULL){
                byteRead = max_bytes;
                rb->at += max_bytes;
            }else{
                printf("right read fail");
                return 0;
            }
            rb->size -= max_bytes;

        }else{/*read right and some left*/
            if(memcpy(buf, rb->buffer + rb->at, rightByte) != NULL){
                byteRead += rightByte;
            }else{
                printf("right read fail");
            }

            int leftOverByte = max_bytes - (rightByte);

            if(memcpy(buf + rightByte, rb->buffer, leftOverByte) != NULL){
                byteRead += leftOverByte;
            }else{
                printf("left read fail");
            }

            rb->at += (rb->at + rightByte + leftOverByte) % rb->capacity;
            rb->size -= rightByte + leftOverByte;
        }
    }
    return byteRead;
}

/*write values in buf into rb*/
int rb_write(struct RingBuffer *rb, const char *buf, int bytes){
    int byteWrite = 0;
    int remain = rb->capacity - rb->size;
    int insertIndex = (rb->at + rb->size) % rb->capacity;

    int rightByte = rb->capacity - insertIndex;
    if(bytes <= rightByte){/*only write to the right*/
        memcpy(rb->buffer + insertIndex, buf, bytes);
        byteWrite = bytes;

    }else{/*write left and right*/
        memcpy(rb->buffer + insertIndex, buf, rightByte);
        int remainBytes = bytes - rightByte;
        int leftByte = rb->capacity - rightByte;

        byteWrite += rightByte;

        if(remainBytes <= leftByte){/*write the rest*/
            memcpy(rb->buffer, buf + rightByte, remainBytes);
            byteWrite += remainBytes;
        }else{/*write as much as possible*/
            memcpy(rb->buffer, buf + rightByte, leftByte);
            byteWrite += leftByte;
        }
    }
    if(bytes < remain){
        rb->size += bytes;
    }else{
        rb->size = rb->capacity;
    }
    return byteWrite;
}


void rb_clear(struct RingBuffer *rb){
    rb->at = 0;
    rb->size = 0;
}

