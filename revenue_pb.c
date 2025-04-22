// Name: Malcolm Hays
// Due Date: 04/23/2025
// Assignment: Homework 6

#include <stdio.h>
#define DAYS 4
#define FILE_NAME "revenue_pb_out.txt"

int max(int i1, int i2) {
    (i1 > i2) ? i1 : i2;
}

int findMaximumRevenue(int* repairs, int* construction, int i, int days, int* table) {
    int arrayIndex = i - 1;
    int maxRevenue = 0;
    int repairRevenue, constructionRevenue, constructionRevenueToday;
    _Bool repairsChosen = 0;

    if (i == 1) {
        repairRevenue = repairs[arrayIndex] + findMaximumRevenue(repairs, construction, i + 1, days, table);
        constructionRevenue = ((i < days) ? construction[arrayIndex + 1] : 0) + findMaximumRevenue(repairs, construction, i + 2, days, table);
        constructionRevenueToday = construction[arrayIndex] + findMaximumRevenue(repairs, construction, i + 1, days, table);

        if (repairRevenue > constructionRevenue && repairRevenue > constructionRevenue) {
            maxRevenue = repairRevenue;

        } else if (constructionRevenue > repairRevenue && constructionRevenue > constructionRevenueToday) {
            maxRevenue = constructionRevenue;
            table[arrayIndex + 1] = maxRevenue;

        } else {
            maxRevenue = constructionRevenueToday;
        }
        

    } else if (i > 1 && i <= days) {
        repairRevenue = repairs[arrayIndex] + findMaximumRevenue(repairs, construction, i + 1, days, table);
        constructionRevenue = ((i < days) ? construction[arrayIndex + 1] : 0) + findMaximumRevenue(repairs, construction, i + 2, days, table);

        if (repairRevenue > constructionRevenue) {
            maxRevenue = repairRevenue;

        } else {
            maxRevenue = constructionRevenue;
            table[arrayIndex + 1] = maxRevenue;
        }

    } else if (i > days) {
        return 0;
    }

    table[arrayIndex] = maxRevenue;
    return maxRevenue;
}

void storeTable(FILE* fp, int* table, int numItems) {
    for (int i = 0; i < numItems; i++) {
        fprintf(fp, "%d,", table[i]);
    }
}

int main() {

    int repairs[DAYS] = {1000, 100, 1000, 1000};
    int construction[DAYS] = {500, 5000, 500, 100};

    int table[DAYS];

    FILE* fp = fopen(FILE_NAME, "w");

    int maxRevenue = findMaximumRevenue(repairs, construction, 1, DAYS, table);
    storeTable(fp, table, DAYS);
    fprintf(fp, "\n%d", maxRevenue);

    fclose(fp);
    return 0;
}