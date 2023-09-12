#include"vector.h"


//include a print function
void print(Vector *v){
    int size = vector_size(v);
    int64_t value;
    for(int i = 0; i < size; i++){
        if(vector_get(v, i, &value)){

            printf("%lld \n", value);
        }else{
            printf("reference out of bound");
        }
        
    }

}


int main(){

   
    
    int64_t value;
    Vector *v = vector_new_with_capacity(5);
    // Vector *v = vector_new();
    vector_push(v, 11);   
    vector_push(v, 9);
    vector_push(v, 25);
    vector_push(v, 3215);
    vector_push(v, 100);

    print(v);

    vector_insert(v, 5, 6);

    vector_remove(v, 2);
    print(v);


    
}

//resize works on size
//reallocating, copy memory, freeing old

//typecast to int to free
//free the vector in main, the library should not be responsible for error checking for free memory

//user should error check on user space side which is main,

//capacity should resize base according user adding more element
//vector library shouldn't free memory
//reallocate when size hits capacity and user push in more value
//when shrink just shrink the size

//size 10
//free buffer when reserve smaller than capacity

//reserve works on capacity