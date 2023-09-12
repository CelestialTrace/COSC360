//buffer is a region of memory used to temporarily hold data while it is being moved from one place to another
//buffer is used when there is a difference between the rate at which data is received and the rate at which is can be processed
//if we remove buffer we will have either data loss or lower bandwidth utilization

#include <stdio.h>
#include <string.h>

int main(){

    int age = 21;
    char name[] = "chad";
    char bloodtype = 'J';
    float gpa = '1.3';


    printf("one and only %d and name is %s with blood %c and %f iq \n", age, name, bloodtype, gpa);

    char string1[25]; //bytes
    char string2[5];
    int someInt;
    float someFloat;
    scanf("%s %s %d %f", string1, string2, &someInt, &someFloat ); //the scanf will only get up to any white spaces, so if your input will have white space
                        //use fget() instead which can read any white spaces
    
    fgets(string1, 25, stdin); //parameter: (variable_name, size, stdin)
                            //fget() will get the entire line including the new line character

    //reading in multiple lines using c from stdin
    int x, y;
    char name[64];
    char input[68];
    while(fgets(input, 68, stdin)){
        sscanf(input, "%d %d %s", &x, &y, name);
        printf("%d %d %s \n", x, y, name);
    }

    // strlwr() convert to lower case
    // strupr() convert to upper case
    // strcat(str1, str2) appends str2 to str1
    // strcpy(str1, str2) copy str2 to str1
    // strncpy(str1, str2, 4) copy n characters from str2 into str1
    // strrev() reverse a string


    //typedef : creating a variable type of your own in combination with struct

    typedef struct{
        int mass;
        char name[15];
        int age;
        char type[10];
    }planets;

    planets alphaSen = {9900, "alphaSen", 40000, "water"};

//write to file
    FILE *pF = fopen("file.txt", "w"); // r:read, w:write, a:append
    
    fprintf(pF, "blablabla");

    fclose(pF);

//read file
    FILE *pF = fopen("file.txt", "r");
    char buffer[255];

    if(pF == NULL){
        printf("unable to open file");
    }

    while(fgets(buffer, 255, pF) != NULL){
        printf("%s", buffer);
    }


    fclose(pF);

    //malloc
    int *ptr;
    ptr = (int*) malloc(5 * sizeof(int));

    //calloc
    ptr = (int*) calloc(15 * sizeof(int));


    return 0; 
}

// \n = newline
// \t = tab

//format specifier: c:char: d:int/bool, s:string, lf:double, %(number):minLength, %(.number):decimal precision. 

//ternary operator: condition ? value return if true : value return if false;
//example: x == y ? equal : not equal
