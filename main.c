#include "people.c"


int main() {
    PeopleArch = fopen("population.dat", "a+b");
    char option;

    do {
        printf("\n\n> > > Population management < < <\n\n");
        printf("Select an option:\n\n");
        printf("A - Add\n");
        printf("R - Remove\n");
        printf("M - Modify\n");
        printf("S - Search a person\n");
        printf("L - List everyone\n");
        printf("E - Exit\n\n");
        scanf(" %c", &option);
        option = toupper(option);

        switch (option) {
        case 'A':
            add();
            break;
        
        case 'R':
            break;
        
        case 'M':
            break;

        case 'S':
            break;

        case 'L':
            break;
        }
    }
    while (option != 'E');
    fclose(PeopleArch);
    return 0;
}
