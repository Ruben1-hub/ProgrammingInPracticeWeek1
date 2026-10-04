/* assets.c - Asset Management module (basic asset register) */
#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utilities.h"

#define ASSET_ID_LENGTH 10
#define ASSET_TYPE_LENGTH 20

static char assetIds[MAX_ASSETS][ASSET_ID_LENGTH];
static char assetNames[MAX_ASSETS][TEXT_LENGTH];
static char assetTypes[MAX_ASSETS][ASSET_TYPE_LENGTH];
static double assetValues[MAX_ASSETS];
static char assetDepartments[MAX_ASSETS][TEXT_LENGTH];
static char assetConditions[MAX_ASSETS][ASSET_TYPE_LENGTH];
static int assetCount = 0;

/* Lets the user pick a type from a menu so only valid types are stored. */
static void chooseAssetType(char destination[])
{
    int choice;

    printf("Asset type:\n");
    printf("  1. Vehicle    2. Computer   3. Building\n");
    printf("  4. Equipment  5. Furniture  6. Other\n");
    choice = readInt("Select type: ", 1, 6);

    switch (choice)
    {
        case 1: strcpy(destination, "Vehicle"); break;
        case 2: strcpy(destination, "Computer"); break;
        case 3: strcpy(destination, "Building"); break;
        case 4: strcpy(destination, "Equipment"); break;
        case 5: strcpy(destination, "Furniture"); break;
        default: strcpy(destination, "Other");
    }
}

static void chooseCondition(char destination[])
{
    int choice;

    printf("Condition:  1. Good   2. Fair   3. Poor   4. Damaged\n");
    choice = readInt("Select condition: ", 1, 4);

    switch (choice)
    {
        case 1: strcpy(destination, "Good"); break;
        case 2: strcpy(destination, "Fair"); break;
        case 3: strcpy(destination, "Poor"); break;
        default: strcpy(destination, "Damaged");
    }
}

static void printAssetDetails(int index)
{
    printf("\n  Asset ID  : %s\n", assetIds[index]);
    printf("  Name      : %s\n", assetNames[index]);
    printf("  Type      : %s\n", assetTypes[index]);
    printf("  Value     : N$%.2f\n", assetValues[index]);
    printf("  Department: %s\n", assetDepartments[index]);
    printf("  Condition : %s\n", assetConditions[index]);
}

void addAsset(void)
{
    printHeader("ADD ASSET");

    if (assetCount >= MAX_ASSETS)
    {
        printf("The asset register is full (%d assets).\n", MAX_ASSETS);
        return;
    }

    readString("Asset name: ", assetNames[assetCount], TEXT_LENGTH);
    chooseAssetType(assetTypes[assetCount]);
    assetValues[assetCount] = readDouble("Purchase value (N$): ", 0.01);
    readString("Department: ", assetDepartments[assetCount], TEXT_LENGTH);
    chooseCondition(assetConditions[assetCount]);

    sprintf(assetIds[assetCount], "AST%03d", assetCount + 1);
    printf("\nAsset added with ID %s.\n", assetIds[assetCount]);
    assetCount++;
}

void displayAssets(void)
{
    int i;
    double total = 0.0;

    printHeader("ASSET REGISTER");

    if (assetCount == 0)
    {
        printf("No assets have been registered yet.\n");
        return;
    }

    printf("%-7s %-20s %-10s %13s %-12s %-8s\n",
           "ID", "Name", "Type", "Value (N$)", "Department", "Cond.");
    printLine('-', 80);

    for (i = 0; i < assetCount; i++)
    {
        printf("%-7s %-20.20s %-10.10s %13.2f %-12.12s %-8.8s\n",
               assetIds[i], assetNames[i], assetTypes[i], assetValues[i],
               assetDepartments[i], assetConditions[i]);
        total += assetValues[i];
    }
    printLine('-', 80);
    printf("Total assets: %d     Total value: N$%.2f\n", assetCount, total);
}

void searchAsset(void)
{
    int option;
    int i;
    int found = 0;
    char searchText[TEXT_LENGTH];

    printHeader("SEARCH ASSET");
    printf("1. Search by asset name (full or part)\n");
    printf("2. Search by asset type\n");
    printf("3. Search by Asset ID\n");
    option = readInt("Enter choice: ", 1, 3);

    readString("Enter search text: ", searchText, TEXT_LENGTH);

    for (i = 0; i < assetCount; i++)
    {
        int match = 0;

        switch (option)
        {
            case 1: match = containsIgnoreCase(assetNames[i], searchText); break;
            case 2: match = equalsIgnoreCase(assetTypes[i], searchText); break;
            case 3: match = equalsIgnoreCase(assetIds[i], searchText); break;
            default: break;
        }

        if (match)
        {
            printAssetDetails(i);
            found++;
        }
    }

    if (found == 0)
    {
        printf("Asset not found.\n");
    }
    else
    {
        printf("\n%d asset(s) found.\n", found);
    }
}

void assetMenu(void)
{
    int choice;

    do
    {
        printHeader("ASSET MANAGEMENT");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");
        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice)
        {
            case 1: addAsset(); break;
            case 2: displayAssets(); break;
            case 3: searchAsset(); break;
            case 4: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

int getAssetCount(void)
{
    return assetCount;
}

double getAssetValue(int index)
{
    return assetValues[index];
}