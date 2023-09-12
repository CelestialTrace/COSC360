#include<stdio.h>
#include<math.h>

double stof(char* s){
    double num = 0;
    int i = 0;
    int leftDigit = 0;
    int rightDigit = 0;

    int leftSide = 1;

    while(s[i] != '\0'){
        if(s[i] != '.' && leftSide){
            leftDigit += 1;
        }else{
            if(!leftSide){
                rightDigit += 1;
            }
            leftSide = 0;
        }
        i += 1;
    }
    // printf("left: %d right: %d\n", leftDigit, rightDigit);


    int arrayIndex = 0;
    for(i = leftDigit; i > 0; i--){
        // printf("number: %d \n", (int)s[arrayIndex]-'0');
        num += ((int)s[arrayIndex] - '0') * pow(10, i-1);
        arrayIndex += 1;
    }
    // printf("%lf \n", num);

    
    arrayIndex += 1;
    if(!leftSide){
        for(i = 0; i < rightDigit; i++){
            num += ((int)s[arrayIndex] - '0') * pow(0.1, i+1);
            printf("number: %lf \n", ((int)s[arrayIndex] - '0') * pow(0.1, i+1));
            arrayIndex += 1;
        }
    }
    return num;
}

int main(int argc, char* argv[]){

    if(argc != 5){
        printf("invalid argv count");
        return -1;
    }
    // int input;

//    printf("argv: %s %s %s %s %s", argv[0], argv[1], argv[2], argv[3], argv[4]);

    // static char* fileName = "";
    // static char* argv1 = "";
    // static char* argv2 = "";
    // static char* argv3 = "";
    // static char* argv4 = "";
    static char* fileName;
    static double argv1;
    static double argv2;
    static int argv3;
    static int argv4;

    sscanf(argv[1], "%lf", &argv1);


    printf("%lf", argv1);
    int argvInput = 0;
    for(int i = 1; i < argc; i++){
        switch (i){
        case 0:
            if(sscanf(argv[i], "%s", fileName) == 1){
                argvInput += 1;
            }
            printf("qwer%s \n", argv1);
            break;
        case 1:
            sscanf(argv[i], "%s", argv1);
            printf("lol %s \n", argv1);
            
            break;
        case 2:
                printf("awf%s \n", argv1);
            if(sscanf(argv[i], "%s", argv2) == 1){
                argvInput += 1;
            }
            break;
        case 3:
                printf("booo%s \n", argv1);
            if(sscanf(argv[i], "%s", argv3) == 1){
                argvInput += 1;

            }
            break;
        case 4:
                printf("awefa%s \n", argv1);
            if(sscanf(argv[i], "%s", argv4) == 1){
                argvInput += 1;

            }
            break;
        default:
            break;
        }
        // printf("argv: %s %s %s %s", argv1, argv2, argv3, argv4);
    }

    int argvInput = sscanf(argv[i], "%s %s %s %s %s", fileName, argv1, argv2, argv3, argv4);

    if(argvInput != 5){
        printf("invalid argv type");
        return -1;
    }


    // float rdoPwr, aFactor;
    // int blastX, blastY; 

    // char* a;
    // char* b;
    // char* c;
    // char* d;

    // a = argv[1];
    // b = argv[2];
    // c = argv[3];
    // d = argv[4];

    // int i = 0;
    // while(a[i] != '\0'){
    //     printf("%c \n", a[i]);
    //     i += 1;
    // }

    // double num = stof(a);
    // printf("%lf", num);

    // rdoPwr = (float)a;
    // printf("%s %s %s %s \n", a, b, c, d);
    // printf("%c", a[1]);
   
    // printf("%f", *argv[1]);
    // rdoPwr = (float)*argv[1];
    // aFactor = (float)*argv[2];
    // blastX = (int)*argv[3];
    // blastY = (int)*argv[4];

    // printf("%f %f %d %d", rdoPwr, aFactor, blastX, blastY);

}