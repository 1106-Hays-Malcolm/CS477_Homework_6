#include <stdio.h>
#define FILE_NAME "revenue_pc_out.txt"

int readFromFile(char* choiceArr, int* moneyArr, FILE* fp) {
    
    int m;
    char endC;
    
    char c, c2;
    int numChoices = 0;
    fscanf(fp, "%c%c", &c, &c2);
    for (; c != '\n'; fscanf(fp, "%c%c", &c, &c2)) {
        choiceArr[numChoices] = c;
        numChoices++;
    }

    return numChoices;
}

int main() {
    FILE* fp = fopen(FILE_NAME, "r");

    char choices[10];
    int money[10];
    int numChoices = readFromFile(choices, money, fp);

    for (int i = 0; i < numChoices; i++) {
        int day = i + 1;
        printf("Day %d: ", day);

        if (choices[i] == 'n') {
            printf("None");
        } else if (choices[i] == 'c') {
            printf("Construction");
        } else if (choices[i] == 'r') {
            printf("Repairs");
        }

        printf("\n");
    }

    fclose(fp);
    return 0;
}