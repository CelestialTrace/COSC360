#include"vector.h"

typedef struct Vector{
   int size;
   int capacity;
   int64_t *values;
} Vector;


Vector *vector_new(void){
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->size = 0;
    v->capacity = 0;

    v->values = (int64_t *)calloc(0, sizeof(int64_t));
    return v;
}


//below, 
//*v is the pointer to the vector
//v->values is the pointer pointing to the values in memory
//
Vector *vector_new_with_capacity(int capacity){
    //allocate memory for the structure itself holding info about size, capacity, and pointer pointing to the start of the memory holding all values of vector
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->size = 0;
    v->capacity = capacity;

    //allocate memory for the growable/shrinkable memory where the values are stored
    v->values = (int64_t *)calloc(v->capacity, sizeof(int64_t));
    return v;
}
//size is current number of element in vector
//capacity is total size of vector allocation

// what calloc essentially does, not it set all value to 0, which malloc doesn't
// void *mycalloc(int elements, int size){
//     int total = elements * size;
//     return memset(malloc(total), 0, total);
// }

void vector_free(Vector *vec){
    free(vec->values);
    free(vec);   
}

void vector_push(Vector *vec, int64_t value){
    if(vec->size == vec->capacity){
        vector_resize(vec, vec->size+1);

        // int64_t *index = vec->values + (sizeof(int64_t) * vec->size);
        // *index = value;
        vec->values[vec->size-1] = value;
    }else{
        // int64_t *index = vec->values + (sizeof(int64_t) * vec->size);
        // *index = value;
        vec->values[vec->size] = value;
        vec->size += 1;
    }
}

void vector_insert(Vector *vec, int index, int64_t value){

    if(index < 0){
        printf("invalid index of insertion");
        return;
    }

    if(index > vec->size-1){
        vector_push(vec, value);
    }else{
        if(vec->size == vec->capacity){
            vector_resize(vec, vec->size+1);
            for(int i = index; i < vec->size+1; i++){
                int64_t tmp = vec->values[i];
                vec->values[i] = value;
                value = tmp;
            }

        }else{
            for(int i = index; i < vec->size+1; i++){
                int64_t tmp = vec->values[i];
                vec->values[i] = value;
                value = tmp;
            }
            vec->size += 1;
        }
    }

}

bool vector_remove(Vector *vec, int index){
    if(index < 0 || index > vec->size-1){
        printf("invalid index of removal");
        return false;
    }

    for(int i = index; i < vec->size; i++){
        vec->values[i] = vec->values[i+1];
    }
    vec->size -= 1;
    return true;
}

bool vector_get(Vector *vec, int index, int64_t *value){
    int64_t *location = vec->values + (sizeof(int64_t) * index);

    // int64_t *val = vec->values;
    // for(int i = 0; i < vec->capacity; i++){
    //     printf("%p ", *val);
    //     val += sizeof(int64_t);
    // }

    if(location != NULL){
        //set value pointer to the location of the index
        // *value = *location;
        *value = vec->values[index];
        return true;
    }else{
        return false;
    }

}

int vector_capacity(Vector *vec){
    return vec->capacity;
}

int vector_size(Vector *vec){
    return vec->size;
}

void vector_resize(Vector *vec, int new_size){

    if(new_size > vec->capacity){
        int64_t *newVec = (int64_t *)calloc(new_size, sizeof(int64_t));
        
        //Not using memcpy. memcpy(newVec, vec->values, vec->size*sizeof(int64_t));
        for(int i = 0; i < vec->size; i++){
            newVec[i] = vec->values[i];
        }
        free(vec->values);
        vec->values = newVec;
        newVec = NULL;
        vec->size = new_size;
        vec->capacity = new_size;
    }
    else if(new_size < vec->size){
        vec->size = new_size;
    }else if(new_size > vec->size){
        int64_t *newVec = (int64_t *)calloc(vec->capacity, sizeof(int64_t));
        
        for(int i = 0; i < vec->size; i++){
            newVec[i] = vec->values[i];
        }
        free(vec->values);
        vec->values = newVec;
        newVec = NULL;
        vec->size = new_size;
    }
       
}

void vecotr_clear(Vector *vec){
    vec->size = 0;
}
