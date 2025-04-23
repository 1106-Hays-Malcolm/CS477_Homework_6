// Name: Malcolm Hays
// Due Date: 04/23/2025
// Assignment: Homework 6

#include <stdio.h>
#define DAYS 4
#define FILE_NAME "revenue_pb_out.txt"

int findMaximumRevenue(int* repairs, int* construction, int i, int days, int* table, _Bool* solvedSubproblems) {
    // a is the index in the array, since the array starts at 0 and i starts at 1
    int a = i - 1;
    int maxRevenue = 0;
    int repairRevenue, constructionRevenue, constructionRevenueToday;

    // This is so we don't solve the same subproblem more than once
    if (i <= days && solvedSubproblems[a]) {
        // printf("Day %d: already solved!\n", i);
        return table[a];
    }

    if (i == 1) {
        // Since this is the first day, we need to find the revenue if we decide to make a repair vs. do construction tomorrow vs. do construction today
        repairRevenue = repairs[a] + findMaximumRevenue(repairs, construction, i + 1, days, table, solvedSubproblems);
        constructionRevenue = ((i < days) ? construction[a + 1] : 0) + findMaximumRevenue(repairs, construction, i + 2, days, table, solvedSubproblems);
        constructionRevenueToday = construction[a] + findMaximumRevenue(repairs, construction, i + 1, days, table, solvedSubproblems);

        // If repair is the best choice, we get the revenue from repair
        if (repairRevenue > constructionRevenue && repairRevenue > constructionRevenue) {
            maxRevenue = repairRevenue;

        // If construction tomorrow is the best choice, we get no revenue today and constuction revenue tomorrow
        } else if (constructionRevenue > repairRevenue && constructionRevenue > constructionRevenueToday) {
            maxRevenue = constructionRevenue;
            table[a + 1] = maxRevenue;
            // We mark the next day's subproblem as solved so we don't have to solve the same subproblem more than once
            solvedSubproblems[a + 1] = 1;

        // If construction today is the best choice, we get construction revenue today
        } else {
            maxRevenue = constructionRevenueToday;
        }
        

    } else if (i > 1 && i <= days) {
        // Since this is not the first day, we need to decide if we want to do a repair toady vs. construction tomorrow
        repairRevenue = repairs[a] + findMaximumRevenue(repairs, construction, i + 1, days, table, solvedSubproblems);
        constructionRevenue = ((i < days) ? construction[a + 1] : 0) + findMaximumRevenue(repairs, construction, i + 2, days, table, solvedSubproblems);

        if (repairRevenue > constructionRevenue) {
            maxRevenue = repairRevenue;

        } else {
            maxRevenue = constructionRevenue;
            table[a + 1] = maxRevenue;
            // We mark the next day's subproblem as solved so we don't have to solve the same subproblem more than once
            solvedSubproblems[a + 1] = 1;
        }

    // If out of bounds, we get no revenue
    } else if (i > days) {
        return 0;
    }

    // Add current day's revenue to table
    table[a] = maxRevenue;
    // Mark the current day's subproblem as solved
    solvedSubproblems[a] = 1;
    return maxRevenue;
}

// Stores the table in a file
void storeTable(FILE* fp, int* table, int numItems) {
    for (int i = 0; i < numItems; i++) {
        fprintf(fp, "%d,", table[i]);
    }
}

int main() {

    int repairs[DAYS] = {1000, 100, 1000, 1000};
    int construction[DAYS] = {500, 5000, 500, 100};
    _Bool solvedSubproblems[DAYS];

    for (int i = 0; i < DAYS; i++) {
        solvedSubproblems[i] = 0;
    }

    int table[DAYS];

    FILE* fp = fopen(FILE_NAME, "w");

    int maxRevenue = findMaximumRevenue(repairs, construction, 1, DAYS, table, solvedSubproblems);
    storeTable(fp, table, DAYS);
    fprintf(fp, "\n%d", maxRevenue);

    fclose(fp);
    return 0;
}