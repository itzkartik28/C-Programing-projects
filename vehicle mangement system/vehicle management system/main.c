 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vehicle {
    char number[20];
    char owner[50];
    char model[30];
    char type[20];
};

void addVehicle() {
    FILE *fp = fopen("vehicles.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Vehicle v;
    printf("Enter vehicle number: ");
    scanf("%s", v.number);
    printf("Enter owner name: ");
    scanf(" %[^\n]", v.owner);
    printf("Enter model: ");
    scanf("%s", v.model);
    printf("Enter type (car/bike): ");
    scanf("%s", v.type);

    fwrite(&v, sizeof(v), 1, fp);
    fclose(fp);

    printf("Vehicle added successfully!\n");
}

void displayVehicles() {
    FILE *fp = fopen("vehicles.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    struct Vehicle v;
    printf("\n--- Vehicle Records ---\n");
    while (fread(&v, sizeof(v), 1, fp)) {
        printf("Number: %s\nOwner: %s\nModel: %s\nType: %s\n\n",
               v.number, v.owner, v.model, v.type);
    }

    fclose(fp);
}

void searchVehicle() {
    FILE *fp = fopen("vehicles.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    char target[20];
    printf("Enter vehicle number to search: ");
    scanf("%s", target);

    struct Vehicle v;
    int found = 0;

    while (fread(&v, sizeof(v), 1, fp)) {
        if (strcmp(v.number, target) == 0) {
            printf("\nRecord Found:\n");
            printf("Number: %s\nOwner: %s\nModel: %s\nType: %s\n\n",
                   v.number, v.owner, v.model, v.type);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Vehicle not found.\n");
    }

    fclose(fp);
}

void deleteVehicle() {
    FILE *fp = fopen("vehicles.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Error opening temporary file!\n");
        fclose(fp);
        return;
    }

    char target[20];
    printf("Enter vehicle number to delete: ");
    scanf("%s", target);

    struct Vehicle v;
    int deleted = 0;

    while (fread(&v, sizeof(v), 1, fp)) {
        if (strcmp(v.number, target) != 0) {
            fwrite(&v, sizeof(v), 1, temp);
        } else {
            deleted = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("vehicles.dat");
    rename("temp.dat", "vehicles.dat");

    if (deleted) {
        printf("Vehicle record deleted successfully.\n");
    } else {
        printf("Vehicle not found.\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== Vehicle Management System =====\n");
        printf("1. Add Vehicle\n");
        printf("2. Display Vehicles\n");
        printf("3. Search Vehicle\n");
        printf("4. Delete Vehicle\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addVehicle(); break;
            case 2: displayVehicles(); break;
            case 3: searchVehicle(); break;
            case 4: deleteVehicle(); break;
            case 5: printf("Exiting the program.\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
