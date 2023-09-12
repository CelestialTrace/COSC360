

#include <stdio.h>
#include <math.h>

struct Point{
    int x;
    int y;
};

static double distance(const struct Point *p1, const struct  Point *p2){
    double result;

    result = sqrt( pow((p2->y - p1->y), 2) + pow((p2->x - p1->x), 2) );
    return result;
};



int main(int argc, char* argv[]){

    if(argc != 5){
        printf("invalid argv count");
        return -1;
    }
    // int input;

   
    char fileName[12];
    double rdoPwr, aFactor;
    int blastX, blastY; 

    int argvInput = 0;
    for(int i = 0; i < argc; i++){
        switch (i){
            case 0:
                if(sscanf(argv[i], "%s", fileName) == 1){
                    argvInput += 1;
                }
                // printf("name: %s \n", fileName);
                break;
            case 1:
                if(sscanf(argv[i], "%lf", &rdoPwr) == 1){
                    argvInput += 1;
                }
                // printf("1: %lf \n", rdoPwr);
                
                break;
            case 2:
                if(sscanf(argv[i], "%lf", &aFactor) == 1){
                    argvInput += 1;
                }
                // printf("2: %lf \n", aFactor);
                break;
            case 3:
                if(sscanf(argv[i], "%d", &blastX) == 1){
                    argvInput += 1;
                }
                    // printf("3: %d \n", blastX);
                break;
            case 4:
                if(sscanf(argv[i], "%d", &blastY) == 1){
                    argvInput += 1;
                }
                    // printf("4: %d \n", blastY);
                break;
            default:
                break;
        }
    }

    if(argvInput != 5){
        printf("invalid argv type");
        return -1;
    }

    struct Point nuke;
    struct Point *n = &nuke;

    n->x = blastX;
    n->y = blastY;

    int humanX, humanY;
    char name[64];
    char input[6400];

    while(fgets(input, 6400, stdin)){
        int lineInput = sscanf(input, "%d %d %s", &humanX, &humanY, name);
        if(lineInput != 3){
            printf("invalid input type or count"); 
            return -1;
        }

        struct Point person;
        struct Point *p = &person;
        p->x = humanX;
        p->y = humanY;

        double dist = distance(n, p);

        double Sv = rdoPwr * pow(aFactor, dist);

        printf("%-16s:%9.4lf Sv. \n", name, Sv);

    }

}