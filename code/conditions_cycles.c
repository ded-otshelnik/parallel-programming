#include <stdio.h>

int main(){
    // if-else construction with trivial condition
    if (1){
        printf("It always will do this code");
    }
    else{
        printf("It never will do this code");
    }

    // it's a const, NULL = 0
    if (!NULL){
        printf("It always will do this code");
    }
    else{
        printf("It never will do this code");
    }

    // if-else construction with condition
    int num = 2;
    char ch = 'A';
    // (int) ch = 65
    if ((1 + 1) == num && ch == 65){
        printf("It always will do this code");
    }
    else{
        printf("It never will do this code");
    }

    // ternary operator
    printf("%s", ((1 + 1) == num && ch == 65 ? "Left value" : "Right value"));

    // switch-case
    switch (ch)
    {
        // it works because multiple cases
        // can use the same code block
        case 'a':
        case 'A':{
            printf("It's A letter");
            break;
        }
        default:{
            break;
        }
    }

    // infinite while with break
    while (1){
        if (num == 5){
            break;
        }
        num++;
    }
    // it equals to
    while (num != 5){
        num++;
    }

    // do-while
    do {
        num--;
    } 
    while(num != 0);

    // usual for
    for (int i = 0; i < 10; i++){
        printf("%i ", i);
    }
    // more exotic for
    for (int i = 0, num = 2; i < 10; i++, num *= 2){
        printf("%d %d", i, num);
    }
    // for with continue
    for (int i = 0, num = 2; i < 10; i++, num *= 2){
        if (i % 2 == 0){
            continue;
        }
        // it will print only even in first place
        printf("%d %d", i, num);
    }

    return 0;
}