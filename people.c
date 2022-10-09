#include <stdio.h>
#include <string.h>
#include <ctype.h>


struct people {
    char name[30];
    char id[10];
    int age;
};
typedef struct people People;
FILE *PeopleArch;
People person;
int SIZE = sizeof(People);
long int regPeople = 0;

void add() {
    char name[30], id[10];
    int age;
    printf("Name: ");
    scanf(" %s", &name);
    printf("Id: ");
    scanf(" %s", &id);
    printf("Age: ");
    scanf("%d", &age);

    if (PeopleArch != NULL) {
        strcpy(person.name,name);
        strcpy(person.id, id);
        person.age = age;
        fseek(PeopleArch,0,2);
        fwrite(&person, SIZE, 1, PeopleArch);
        regPeople++;
}
    printf("Number of population: %ld\n", regPeople);
}
