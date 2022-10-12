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
    People auxPerson;
    printf("Name: ");
    scanf(" %s", name);
    printf("Id: ");
    scanf(" %s", id);
    printf("Age: ");
    scanf("%d", &age);

    if (PeopleArch != NULL) {
        // procurar ponto de inserção
        fseek(PeopleArch,0,0);
        int pos;
        do {
            pos = ftell(PeopleArch);
            fread(&person, SIZE, 1, PeopleArch);
            if (strcmp(person.id, id) == 0) {
                printf("Id already registered");
                return;
            }
            if (person.age > age)
                break;
        }
        while (!feof(PeopleArch));
        
        // ponto de inserção no fim do arquivo
        if (feof(PeopleArch)) {
            printf("INSERCAO NO FINAL\n");
            strcpy(person.name,name);
            strcpy(person.id, id);
            person.age = age;
            printf("posicao antes %ld\n", ftell(PeopleArch));
            fwrite(&person, SIZE, 1, PeopleArch);
            printf("posicao dps %ld\n", ftell(PeopleArch));
            printf("size %d\n", SIZE);
            regPeople++;
            return;
        }

        // inserção ordenada
        fclose(PeopleArch); 
        PeopleArch = fopen("population.dat", "r+b");

        char flag = 'C';
        int auxPos;
        fseek(PeopleArch, pos, 0);
        int i = pos;
        do {
            fread(&person, SIZE, 1, PeopleArch);
            auxPos = ftell(PeopleArch);
            fread(&auxPerson, SIZE, 1, PeopleArch);

            // deslocar só 1 item
            if (feof(PeopleArch)) {
                fseek(PeopleArch, auxPos, 0);
                fwrite(&person, SIZE, 1, PeopleArch);
                flag = 'B';
            }

            // deslocar +1 item
            else {
                fseek(PeopleArch, auxPos, 0);
                fwrite(&person, SIZE, 1, PeopleArch);
                auxPos = ftell(PeopleArch);
                fread(&person,SIZE,1,PeopleArch);

                if (feof(PeopleArch)) {
                    printf("fim2\n"); 
                    flag = 'B';
                }
                fseek(PeopleArch, auxPos, 0);
                fwrite (&auxPerson, SIZE, 1, PeopleArch);
                if (feof(PeopleArch)) {
                    printf("fim3\n"); 
                    flag = 'B';
                }
                printf("SEGUNDO WRITE");
                if (flag == 'B')
                    break;
                }
        }            
        while (flag != 'B');

        
        // escreve arquivo a ser inserido
        fseek(PeopleArch, i, 0);
        strcpy(person.name,name);
        strcpy(person.id, id);
        person.age = age;
        fwrite(&person, SIZE, 1, PeopleArch);
        regPeople++;
        fclose(PeopleArch);
        PeopleArch = fopen("population.dat", "a+b");
        return;   
    }
}


void listAll() {
    fseek(PeopleArch,0,0);

    do {
        fread(&person, SIZE, 1, PeopleArch);
        if (feof(PeopleArch))
            return;
        printf("%s\n", person.name);
        printf("%s\n", person.id);
        printf("%d\n", person.age);
        printf("-------------------\n\n");
    }
    while(!feof(PeopleArch));
}