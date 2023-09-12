/*vector c file where it contains functions of that a general vector from
the c++ library such as push, remote, etc...
vector lab
Zichen Fu
9/12/2023*/

#include"vector.h"

//struct of vector holding information such as size and pointers to values
typedef struct Vector{
   int size;
   int capacity;
   int64_t *values;
} Vector;
//size is current number of element in vector
//capacity is total size of vector allocation


//create a vector with 0 inital capacity
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

// what calloc essentially does, not it set all value to 0, which malloc doesn't
// void *mycalloc(int elements, int size){
//     int total = elements * size;
//     return memset(malloc(total), 0, total);
// }

//free the vector and its values
void vector_free(Vector *vec){
    free(vec->values);
    free(vec);   
}

//push values to the back of vector, if size exceed capacity it will reallocate
void vector_push(Vector *vec, int64_t value){
    if(vec->size == vec->capacity){
        vector_resize(vec, vec->size+1);

        // int64_t *index = vec->values + (sizeof(int64_t) * vec->size);
        // *index = value;
        vec->values[vec->size] = value;
        vec->size += 1;
    }else{
        // int64_t *index = vec->values + (sizeof(int64_t) * vec->size);
        // *index = value;
        vec->values[vec->size] = value;
        vec->size += 1;
    }
}

//insert value into the vector, if size exceed capacity it will have to reallocate
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

//remote elements from vector if index within range
bool vector_remove(Vector *vec, int index){
    if(index < 0 || index > vec->size-1){
        printf("invalid index of removal");
        return false;
    }

    for(int i = index; i < vec->size-1; i++){
        vec->values[i] = vec->values[i+1];
    }
    vec->size -= 1;
    return true;
}

//set elements within a vector given its index and value, also check for range
bool vector_set(Vector *vec, int index, int64_t value){
    if(index < 0 || index > vec->size-1){
        printf("invalid index of set");
        return false;
    }

    vec->values[index] = value;
    return true;
}

//get value at a specified index
bool vector_get(Vector *vec, int index, int64_t *value){
    if(index < 0){
        printf("invalid get index");
        return -1;
    }
    int64_t *location = vec->values + (sizeof(int64_t) * index);

    if(location != NULL){
        //set value pointer to the location of the index
        // *value = *location;
        *value = vec->values[index];
        return true;
    }else{
        return false;
    }

}

//given a value it will return the index of its first occurrence if it exist
int vector_find(Vector *vec, int64_t value){
    for(int i = 0; i < vec->size; i++){
        if(vec->values[i] == value){
            return i;
        }
    }

    return -1;
}

int vector_capacity(Vector *vec){
    return vec->capacity;
}

int vector_size(Vector *vec){
    return vec->size;
}

//resize the vector, if new size exceed capacity it will reallocate
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
        vec->capacity = new_size;
    }
    else{
        vec->size = new_size;
    }
       
}

//set capacity to size if less than size, but if it exceed vector size it will reallocate 
void vector_reserve(Vector *vec, int new_capacity){
    if(new_capacity <= vec->size){
        vec->capacity = vec->size;
    }else{
        //in resize if old new cap is greater than old cap it change the size also to the new cap  
        int64_t *newVec = (int64_t *)calloc(new_capacity, sizeof(int64_t));
        
        for(int i = 0; i < vec->size; i++){
            newVec[i] = vec->values[i];
        }
        free(vec->values);
        vec->values = newVec;
        newVec = NULL;
        vec->capacity = new_capacity;
    }
}

void vector_clear(Vector *vec){
    vec->size = 0;
}

//a standard comparison function
static bool comp_ascending(int64_t left, int64_t right){
    // Consider left <= right to mean left is in place with right. Meaning
    // we swap if left > right.
    return left <= right;
}

//use the vector sort which is selection sort with comparison function to sort elements
void vector_sort(Vector *vec){
    vector_sort_by(vec, comp_ascending);
}

//selection sort function
void vector_sort_by(Vector *vec, bool(*comp)(int64_t left, int64_t right)){
     int i;
    int j;
    int min;
    int64_t tmp;

    for (i = 0; i < vec->size - 1; i++) {
        min = i;
        for (j = i + 1; j < vec->size; j++) {
            if (!comp(vec->values[min], vec->values[j])) {
                min = j;
            }
        }
        if (min != i) {
            tmp = vec->values[min];
            vec->values[min] = vec->values[i];
            vec->values[i]   = tmp;
        }
    }
}

//search an element within the vector and return index if exist
int vector_bsearch(Vector *vec, int64_t value){
    if(vec->size < 0){
        printf("vector size is less the 0");
        return -1;
    }
    int min = 0;
    int max = vec->size-1;
    int index;

    while(true){
        if(max-min == 1){
            if(vec->values[min] == value){
                return min;
            }else if(vec->values[max] == value){
                return max;
            }else{
                return -1;
            }
        }

        if((max - min + 1) % 2 == 0){
            index = min + (max-min)/2;
        }else{
            index = min + (max-min)/2;
        }

        if(value > vec->values[index]){
            min = index;
        }else if( value < vec->values[index]){
            max = index;
        }else{
            return index;
        }
    }
   
}
