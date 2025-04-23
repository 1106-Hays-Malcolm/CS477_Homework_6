// Name: Malcolm Hays
// Due Date: 04/23/2025
// Assignment: Homework 6

#include <stdio.h>
#define FILE_NAME "revenue_pc_out.txt"


// Read the choices from a file so we can reconstruct the solution
int readFromFile(char* choiceArr, int* moneyArr, FILE* fp) {

    char dummy[100];

    // Remove the first line of the file
    fscanf(fp, "%s\n", dummy);
    
    char c, c2;
    int numChoices = 0;
    fscanf(fp, "%c%c", &c, &c2);
    // We keep reading from the file until we hit the end of the line
    for (; c != '\n'; fscanf(fp, "%c%c", &c, &c2)) {
        choiceArr[numChoices] = c;
        numChoices++;
    }

    return numChoices;
}

int main() {
    FILE* fp = fopen(FILE_NAME, "r");
    FILE* fout = fopen("revenue_pd_out.txt", "w");

    char choices[10];
    int money[10];
    int numChoices = readFromFile(choices, money, fp);

    for (int i = 0; i < numChoices; i++) {
        int day = i + 1;
        fprintf(fout, "Day %d: ", day);

        if (choices[i] == 'n') {
            fprintf(fout, "None");
        } else if (choices[i] == 'c') {
            fprintf(fout, "Construction");
        } else if (choices[i] == 'r') {
            fprintf(fout, "Repairs");
        }

        fprintf(fout, "\n");
    }

    fclose(fp);
    fclose(fout);
    return 0;
}