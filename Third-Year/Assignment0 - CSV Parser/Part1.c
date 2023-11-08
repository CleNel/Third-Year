#include <stdio.h>

int main () {

    char name [50];
    int age;

    printf("Name >> ");
    scanf("%49s" , name);
    printf("Age >> ");
    scanf("%d" , &age);

    printf("Hello %s (%d)\n", name, age);

}