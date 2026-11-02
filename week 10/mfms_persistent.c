#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Entity Structures ---
typedef struct {
    int id;
    char name[50];
    double salary;
} Employee;

typedef struct {
    int id;
    char name[50];
    char contact[30];
} Supplier;

typedef struct {
    int id;
    char description[50];
    double value;
} Asset;

typedef struct {
    int department_id;
    char category[30];
    double allocated_budget;
} Budget;

// --- Function Prototypes ---
void displayMenu(void);

// Text File Operations
void saveEmployeeText(void);
void loadEmployeesText(void);
void saveSupplierText(void);
void loadSuppliersText(void);
void saveAssetText(void);
void loadAssetsText(void);
void saveBudgetText(void);
void loadBudgetsText(void);

// Binary File Operations (Task 15)
void saveEmployeeBinary(void);
void loadEmployeesBinary(void);

// Practical Challenge Features
void searchEmployee(void);
void backupDataFile(void);

int main(void) {
    int choice;

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
            continue;
        }
        while(getchar() != '\n'); // Clear newline character from buffer

        switch (choice) {
            case 1: saveEmployeeText(); break;
            case 2: loadEmployeesText(); break;
            case 3: saveSupplierText(); break;
            case 4: loadSuppliersText(); break;
            case 5: saveAssetText(); break;
            case 6: loadAssetsText(); break;
            case 7: saveBudgetText(); break;
            case 8: loadBudgetsText(); break;
            case 9: saveEmployeeBinary(); break;
            case 10: loadEmployeesBinary(); break;
            case 11: searchEmployee(); break;
            case 12: backupDataFile(); break;
            case 13: 
                printf("Exiting MFMS. Goodbye!\n"); 
                break;
            default: 
                printf("Invalid choice. Please select between 1 and 13.\n");
        }
    } while (choice != 13);

    return 0;
}

// --- Menu Display ---
void displayMenu(void) {
    printf("\n========================================\n");
    printf("   MFMS Persistent Storage Menu (Week 10)\n");
    printf("========================================\n");
    printf(" 1. Add & Save Employee (Text)\n");
    printf(" 2. Load Employees (Text)\n");
    printf(" 3. Add & Save Supplier (Text)\n");
    printf(" 4. Load Suppliers (Text)\n");
    printf(" 5. Add & Save Asset (Text)\n");
    printf(" 6. Load Assets (Text)\n");
    printf(" 7. Add & Save Budget (Text)\n");
    printf(" 8. Load Budgets (Text)\n");
    printf(" 9. Add & Save Employee (Binary)\n");
    printf("10. Load Employees (Binary)\n");
    printf("11. Search Employee by ID\n");
    printf("12. Backup Data File\n");
    printf("13. Exit\n");
    printf("Enter your choice (1-13): ");
}

// --- 1 & 2. Employee Text Storage & Loading ---
void saveEmployeeText(void) {
    Employee e;
    printf("Enter Employee ID: ");
    scanf("%d", &e.id);
    while(getchar() != '\n');
    printf("Enter Employee Name: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = 0; // Remove newline
    printf("Enter Employee Salary: ");
    scanf("%lf", &e.salary);

    FILE *fp = fopen("data/employees.txt", "a");
    if (fp == NULL) {
        perror("Error opening data/employees.txt"); // Task 11: Error handling
        return;
    }

    fprintf(fp, "%d|%s|%.2f\n", e.id, e.name, e.salary);
    fclose(fp);
    printf("[Success] 1 employee record saved to text file.\n"); // Practical Challenge: Confirmation
}

void loadEmployeesText(void) {
    FILE *fp = fopen("data/employees.txt", "r");
    if (fp == NULL) {
        printf("[Info] Data file 'data/employees.txt' does not exist yet. No records loaded.\n"); // Missing file handling
        return;
    }

    int id, count = 0;
    char name[50];
    double salary;

    printf("\n--- Loaded Employees (Text) ---\n");
    while (fscanf(fp, "%d|%49[^|]|%lf\n", &id, name, &salary) == 3) {
        printf("ID: %d | Name: %s | Salary: $%.2f\n", id, name, salary);
        count++;
    }
    fclose(fp);
    printf("Successfully loaded %d record(s).\n", count); // Record-count report
}

// --- 3 & 4. Supplier Text Storage & Loading ---
void saveSupplierText(void) {
    Supplier s;
    printf("Enter Supplier ID: ");
    scanf("%d", &s.id);
    while(getchar() != '\n');
    printf("Enter Supplier Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Supplier Contact: ");
    fgets(s.contact, sizeof(s.contact), stdin);
    s.contact[strcspn(s.contact, "\n")] = 0;

    FILE *fp = fopen("data/suppliers.txt", "a");
    if (fp == NULL) {
        perror("data/suppliers.txt");
        return;
    }
    fprintf(fp, "%d|%s|%s\n", s.id, s.name, s.contact);
    fclose(fp);
    printf("[Success] 1 supplier record saved.\n");
}

void loadSuppliersText(void) {
    FILE *fp = fopen("data/suppliers.txt", "r");
    if (fp == NULL) {
        printf("[Info] Suppliers file does not exist yet.\n");
        return;
    }
    int id, count = 0;
    char name[50], contact[30];
    printf("\n--- Loaded Suppliers (Text) ---\n");
    while (fscanf(fp, "%d|%49[^|]|%29[^\n]\n", &id, name, contact) == 3) {
        printf("ID: %d | Name: %s | Contact: %s\n", id, name, contact);
        count++;
    }
    fclose(fp);
    printf("Successfully loaded %d record(s).\n", count);
}

// --- 5 & 6. Asset Text Storage & Loading ---
void saveAssetText(void) {
    Asset a;
    printf("Enter Asset ID: ");
    scanf("%d", &a.id);
    while(getchar() != '\n');
    printf("Enter Asset Description: ");
    fgets(a.description, sizeof(a.description), stdin);
    a.description[strcspn(a.description, "\n")] = 0;
    printf("Enter Asset Value: ");
    scanf("%lf", &a.value);

    FILE *fp = fopen("data/assets.txt", "a");
    if (fp == NULL) {
        perror("data/assets.txt");
        return;
    }
    fprintf(fp, "%d|%s|%.2f\n", a.id, a.description, a.value);
    fclose(fp);
    printf("[Success] 1 asset record saved.\n");
}

void loadAssetsText(void) {
    FILE *fp = fopen("data/assets.txt", "r");
    if (fp == NULL) {
        printf("[Info] Assets file does not exist yet.\n");
        return;
    }
    int id, count = 0;
    char desc[50];
    double value;
    printf("\n--- Loaded Assets (Text) ---\n");
    while (fscanf(fp, "%d|%49[^|]|%lf\n", &id, desc, &value) == 3) {
        printf("ID: %d | Description: %s | Value: $%.2f\n", id, desc, value);
        count++;
    }
    fclose(fp);
    printf("Successfully loaded %d record(s).\n", count);
}

// --- 7 & 8. Budget Text Storage & Loading ---
void saveBudgetText(void) {
    Budget b;
    printf("Enter Department ID: ");
    scanf("%d", &b.department_id);
    while(getchar() != '\n');
    printf("Enter Budget Category: ");
    fgets(b.category, sizeof(b.category), stdin);
    b.category[strcspn(b.category, "\n")] = 0;
    printf("Enter Allocated Budget: ");
    scanf("%lf", &b.allocated_budget);

    FILE *fp = fopen("data/budgets.txt", "a");
    if (fp == NULL) {
        perror("data/budgets.txt");
        return;
    }
    fprintf(fp, "%d|%s|%.2f\n", b.department_id, b.category, b.allocated_budget);
    fclose(fp);
    printf("[Success] 1 budget record saved.\n");
}

void loadBudgetsText(void) {
    FILE *fp = fopen("data/budgets.txt", "r");
    if (fp == NULL) {
        printf("[Info] Budgets file does not exist yet.\n");
        return;
    }
    int dept_id, count = 0;
    char category[30];
    double budget;
    printf("\n--- Loaded Budgets (Text) ---\n");
    while (fscanf(fp, "%d|%29[^|]|%lf\n", &dept_id, category, &budget) == 3) {
        printf("Dept ID: %d | Category: %s | Budget: $%.2f\n", dept_id, category, budget);
        count++;
    }
    fclose(fp);
    printf("Successfully loaded %d record(s).\n", count);
}

// --- 9 & 10. Binary Employee Storage & Loading (Task 15) ---
void saveEmployeeBinary(void) {
    Employee e;
    printf("Enter Employee ID (Binary): ");
    scanf("%d", &e.id);
    while(getchar() != '\n');
    printf("Enter Employee Name (Binary): ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = 0;
    printf("Enter Employee Salary (Binary): ");
    scanf("%lf", &e.salary);

    FILE *fp = fopen("data/employees.dat", "ab");
    if (fp == NULL) {
        perror("data/employees.dat");
        return;
    }
    fwrite(&e, sizeof(Employee), 1, fp);
    fclose(fp);
    printf("[Success] 1 employee record saved to binary file.\n");
}

void loadEmployeesBinary(void) {
    FILE *fp = fopen("data/employees.dat", "rb");
    if (fp == NULL) {
        printf("[Info] Binary employee data file does not exist yet.\n");
        return;
    }

    Employee e;
    int count = 0;
    printf("\n--- Loaded Employees (Binary) ---\n");
    while (fread(&e, sizeof(Employee), 1, fp) == 1) {
        printf("ID: %d | Name: %s | Salary: $%.2f\n", e.id, e.name, e.salary);
        count++;
    }
    fclose(fp);
    printf("Successfully loaded %d binary record(s).\n", count);
}

// --- 11. Search Employee Operation (Practical Challenge) ---
void searchEmployee(void) {
    int search_id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &search_id);

    FILE *fp = fopen("data/employees.txt", "r");
    if (fp == NULL) {
        printf("[Info] No employee text data file found to search.\n");
        return;
    }

    int id, found = 0;
    char name[50];
    double salary;

    while (fscanf(fp, "%d|%49[^|]|%lf\n", &id, name, &salary) == 3) {
        if (id == search_id) {
            printf("\n[Found Match] ID: %d | Name: %s | Salary: $%.2f\n", id, name, salary);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("[Result] Employee with ID %d was not found.\n", search_id);
    }
}

// --- 12. Backup Data File (Practical Challenge) ---
void backupDataFile(void) {
    char source_path[100], backup_path[100];
    printf("Enter filename to backup (e.g., data/employees.txt): ");
    scanf("%s", source_path);
    printf("Enter backup destination filename (e.g., data/employees_backup.txt): ");
    scanf("%s", backup_path);

    FILE *src = fopen(source_path, "rb");
    if (src == NULL) {
        perror("Error opening source file for backup");
        return;
    }

    FILE *dest = fopen(backup_path, "wb");
    if (dest == NULL) {
        perror("Error creating backup destination file");
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);
    printf("[Success] Backup successfully created from '%s' to '%s'.\n", source_path, backup_path);
}