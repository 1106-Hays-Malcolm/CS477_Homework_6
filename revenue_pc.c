// Name: Malcolm Hays
// Due Date: 04/23/2025
// Assignment: Homework 6

#include <stdio.h>
#define DAYS 4
#define FILE_NAME "revenue_pc_out.txt"

int max(int i1, int i2) {
    (i1 > i2) ? i1 : i2;
}

int findMaximumRevenue(int* repairs, int* construction, int i, int days, int* revenue_table, char* choice_table, _Bool* solvedSubproblems) {
    int a = i - 1;
    int maxRevenue = 0;
    char choice;
    int repairRevenue, constructionRevenue, constructionRevenueToday;
    _Bool repairsChosen = 0;

    // This is so we don't solve the same subproblem more than once
    if (solvedSubproblems[a]) {
        printf("Day %d: already solved!\n", i);
        return revenue_table[a];
    }
    printf("Day %d: not solved!\n", i);

    if (i == 1) {
        repairRevenue = repairs[a] + findMaximumRevenue(repairs, construction, i + 1, days, revenue_table, choice_table, solvedSubproblems);
        constructionRevenue = ((i < days) ? construction[a + 1] : 0) + findMaximumRevenue(repairs, construction, i + 2, days, revenue_table, choice_table, solvedSubproblems);
        constructionRevenueToday = construction[a] + findMaximumRevenue(repairs, construction, i + 1, days, revenue_table, choice_table, solvedSubproblems);

        if (repairRevenue > constructionRevenue && repairRevenue > constructionRevenue) {
            maxRevenue = repairRevenue;
            choice = 'r';

        } else if (constructionRevenue > repairRevenue && constructionRevenue > constructionRevenueToday) {
            maxRevenue = constructionRevenue;
            revenue_table[a + 1] = maxRevenue;
            choice_table[a + 1] = 'c';
            solvedSubproblems[a + 1] = 1;
            choice = 'n';

        } else {
            maxRevenue = constructionRevenueToday;
            choice = 'c';
        }
        

    } else if (i > 1 && i <= days) {
        repairRevenue = repairs[a] + findMaximumRevenue(repairs, construction, i + 1, days, revenue_table, choice_table, solvedSubproblems);
        constructionRevenue = ((i < days) ? construction[a + 1] : 0) + findMaximumRevenue(repairs, construction, i + 2, days, revenue_table, choice_table, solvedSubproblems);

        if (repairRevenue > constructionRevenue) {
            maxRevenue = repairRevenue;
            choice = 'r';

        } else {
            maxRevenue = constructionRevenue;
            revenue_table[a + 1] = maxRevenue;
            choice_table[a + 1] = 'c';
            solvedSubproblems[a + 1] = 1;
            choice = 'r';
        }

    } else if (i > days) {
        return 0;
    }

    revenue_table[a] = maxRevenue;
    choice_table[a] = choice;
    solvedSubproblems[a] = 1;
    return maxRevenue;
}

void storeTableInt(FILE* fp, int* table, int numItems) {
    for (int i = 0; i < numItems; i++) {
        fprintf(fp, "%d,", table[i]);
    }
}

void storeTableChar(FILE* fp, char* table, int numItems) {
    for (int i = 0; i < numItems; i++) {
        fprintf(fp, "%c,", table[i]);
    }
}

int main() {

    int repairs[DAYS] = {1000, 100, 1000, 1000};
    int construction[DAYS] = {500, 5000, 500, 100};

    _Bool solvedSubproblems[DAYS];

    for (int i = 0; i < DAYS; i++) {
        solvedSubproblems[i] = 0;
    }

    int revenue_table[DAYS];
    char choice_table[DAYS];

    FILE* fp = fopen(FILE_NAME, "w");

    int maxRevenue = findMaximumRevenue(repairs, construction, 1, DAYS, revenue_table, choice_table, solvedSubproblems);
    storeTableInt(fp, revenue_table, DAYS);
    fprintf(fp, "\n");
    storeTableChar(fp, choice_table, DAYS);
    fprintf(fp, "\n%d", maxRevenue);

    fclose(fp);
    return 0;
}