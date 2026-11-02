#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 100

// --- STRUCTURES (Task 2 & 7 & 8) ---
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    char name[50];
    char department[50];
    float salary;
} Employee;

typedef struct {
    int id;
    char name[50];
    char contactPerson[50];
    char phone[20];
} Supplier;

typedef struct {
    int id;
    char name[50];
    float value;
    Date acquiredDate;
} Asset;

typedef struct {
    int id;
    char category[50];
    float allocated;
    float spent;
} Budget;

typedef struct {
    int id;
    char title[50];
    Date startDate;
    Date endDate;
} Project;

// --- FUNCTION PROTOTYPES ---
void addEmployee(Employee employees[], int *count);
void displayEmployees(const Employee employees[], int count);

void addSupplier(Supplier suppliers[], int *count);
void displaySuppliers(const Supplier suppliers[], int count);

void addAsset(Asset assets[], int *count);
void displayAssets(const Asset assets[], int count);

void addBudget(Budget budgets[], int *count);
void displayBudgets(const Budget budgets[], int count);

void addProject(Project projects[], int *count);
void displayProjects(const Project projects[], int count);

void saveEmployees(const Employee employees[], int count, const char *filename);
void loadEmployees(Employee employees[], int *count, const char *filename);

// --- MAIN FUNCTION (Task 9) ---
int main() {
    // Task 3: Arrays and counters for each record type
    Employee employees[MAX_RECORDS];
    int employeeCount = 0;

    Supplier suppliers[MAX_RECORDS];
    int supplierCount = 0;

    Asset assets[MAX_RECORDS];
    int assetCount = 0;

    Budget budgets[MAX_RECORDS];
    int budgetCount = 0;

    Project projects[MAX_RECORDS];
    int projectCount = 0;

    const char *empFile = "employees.dat";

    // Task 10: Load data on startup using fread()
    loadEmployees(employees, &employeeCount, empFile);

    int choice;
    do {
        printf("\n================ MFMS RECORD MANAGEMENT ================\n");
        printf("1. Add Employee          | 6. Display Employees\n");
        printf("2. Add Supplier          | 7. Display Suppliers\n");
        printf("3. Add Asset             | 8. Display Assets\n");
        printf("4. Add Budget            | 9. Display Budgets\n");
        printf("5. Add Project           | 10. Display Projects\n");
        printf("11. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addEmployee(employees, &employeeCount); break;
            case 2: addSupplier(suppliers, &supplierCount); break;
            case 3: addAsset(assets, &assetCount); break;
            case 4: addBudget(budgets, &budgetCount); break;
            case 5: addProject(projects, &projectCount); break;
            case 6: displayEmployees(employees, employeeCount); break;
            case 7: displaySuppliers(suppliers, supplierCount); break;
            case 8: displayAssets(assets, assetCount); break;
            case 9: displayBudgets(budgets, budgetCount); break;
            case 10: displayProjects(projects, projectCount); break;
            case 11:
                // Task 10: Save data before exit using fwrite()
                saveEmployees(employees, employeeCount, empFile);
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 11);

    return 0;
}

// --- EMPLOYEE FUNCTIONS (Task 4 & 5) ---
void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Error: Employee array is full!\n");
        return;
    }
    printf("\n--- Add Employee ---\n");
    printf("Enter ID: ");
    scanf("%d", &employees[*count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", employees[*count].name);
    printf("Enter Department: ");
    scanf(" %[^\n]s", employees[*count].department);
    printf("Enter Salary: ");
    scanf("%f", &employees[*count].salary);
    
    (*count)++;
    printf("Employee added successfully!\n");
}

void displayEmployees(const Employee employees[], int count) {
    if (count == 0) {
        printf("\nNo employees recorded yet.\n");
        return;
    }
    printf("\n----------------------------------------------------\n");
    printf("%-5s | %-20s | %-15s | %-10s\n", "ID", "Name", "Department", "Salary");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | %-15s | $%-9.2f\n", 
               employees[i].id, employees[i].name, employees[i].department, employees[i].salary);
    }
    printf("----------------------------------------------------\n");
}

// --- SUPPLIER FUNCTIONS (Task 6) ---
void addSupplier(Supplier suppliers[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Error: Supplier array is full!\n");
        return;
    }
    printf("\n--- Add Supplier ---\n");
    printf("Enter ID: ");
    scanf("%d", &suppliers[*count].id);
    printf("Enter Supplier Name: ");
    scanf(" %[^\n]s", suppliers[*count].name);
    printf("Enter Contact Person: ");
    scanf(" %[^\n]s", suppliers[*count].contactPerson);
    printf("Enter Phone: ");
    scanf(" %[^\n]s", suppliers[*count].phone);
    
    (*count)++;
    printf("Supplier added successfully!\n");
}

void displaySuppliers(const Supplier suppliers[], int count) {
    if (count == 0) {
        printf("\nNo suppliers recorded yet.\n");
        return;
    }
    printf("\n---------------------------------------------------------------\n");
    printf("%-5s | %-20s | %-20s | %-15s\n", "ID", "Company Name", "Contact Person", "Phone");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | %-20s | %-15s\n", 
               suppliers[i].id, suppliers[i].name, suppliers[i].contactPerson, suppliers[i].phone);
    }
    printf("---------------------------------------------------------------\n");
}

// --- ASSET FUNCTIONS (Task 7) ---
void addAsset(Asset assets[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Error: Asset array is full!\n");
        return;
    }
    printf("\n--- Add Asset ---\n");
    printf("Enter ID: ");
    scanf("%d", &assets[*count].id);
    printf("Enter Asset Name: ");
    scanf(" %[^\n]s", assets[*count].name);
    printf("Enter Value: ");
    scanf("%f", &assets[*count].value);
    printf("Enter Acquired Date (DD MM YYYY): ");
    scanf("%d %d %d", &assets[*count].acquiredDate.day, 
          &assets[*count].acquiredDate.month, 
          &assets[*count].acquiredDate.year);
    
    (*count)++;
    printf("Asset added successfully!\n");
}

void displayAssets(const Asset assets[], int count) {
    if (count == 0) {
        printf("\nNo assets recorded yet.\n");
        return;
    }
    printf("\n----------------------------------------------------\n");
    printf("%-5s | %-20s | %-10s | %-12s\n", "ID", "Asset Name", "Value", "Acquired");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | $%-9.2f | %02d/%02d/%4d\n", 
               assets[i].id, assets[i].name, assets[i].value,
               assets[i].acquiredDate.day, assets[i].acquiredDate.month, assets[i].acquiredDate.year);
    }
    printf("----------------------------------------------------\n");
}

// --- BUDGET FUNCTIONS (Task 8) ---
void addBudget(Budget budgets[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Error: Budget array is full!\n");
        return;
    }
    printf("\n--- Add Budget ---\n");
    printf("Enter ID: ");
    scanf("%d", &budgets[*count].id);
    printf("Enter Category: ");
    scanf(" %[^\n]s", budgets[*count].category);
    printf("Enter Allocated Amount: ");
    scanf("%f", &budgets[*count].allocated);
    printf("Enter Spent Amount: ");
    scanf("%f", &budgets[*count].spent);
    
    (*count)++;
    printf("Budget added successfully!\n");
}

void displayBudgets(const Budget budgets[], int count) {
    if (count == 0) {
        printf("\nNo budgets recorded yet.\n");
        return;
    }
    printf("\n--------------------------------------------------------------------\n");
    printf("%-5s | %-18s | %-10s | %-10s | %-10s\n", "ID", "Category", "Allocated", "Spent", "Balance");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        float balance = budgets[i].allocated - budgets[i].spent;
        printf("%-5d | %-18s | $%-9.2f | $%-9.2f | $%-9.2f\n", 
               budgets[i].id, budgets[i].category, budgets[i].allocated, budgets[i].spent, balance);
    }
    printf("--------------------------------------------------------------------\n");
}

// --- PROJECT FUNCTIONS (Task 8) ---
void addProject(Project projects[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Error: Project array is full!\n");
        return;
    }
    printf("\n--- Add Project ---\n");
    printf("Enter ID: ");
    scanf("%d", &projects[*count].id);
    printf("Enter Project Title: ");
    scanf(" %[^\n]s", projects[*count].title);
    printf("Enter Start Date (DD MM YYYY): ");
    scanf("%d %d %d", &projects[*count].startDate.day, 
          &projects[*count].startDate.month, 
          &projects[*count].startDate.year);
    printf("Enter End Date (DD MM YYYY): ");
    scanf("%d %d %d", &projects[*count].endDate.day, 
          &projects[*count].endDate.month, 
          &projects[*count].endDate.year);
    
    (*count)++;
    printf("Project added successfully!\n");
}

void displayProjects(const Project projects[], int count) {
    if (count == 0) {
        printf("\nNo projects recorded yet.\n");
        return;
    }
    printf("\n--------------------------------------------------------------------------\n");
    printf("%-5s | %-20s | %-15s | %-15s\n", "ID", "Project Title", "Start Date", "End Date");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | %02d/%02d/%4d    | %02d/%02d/%4d\n", 
               projects[i].id, projects[i].title,
               projects[i].startDate.day, projects[i].startDate.month, projects[i].startDate.year,
               projects[i].endDate.day, projects[i].endDate.month, projects[i].endDate.year);
    }
    printf("--------------------------------------------------------------------------\n");
}

// --- FILE I/O (Task 10) ---
void saveEmployees(const Employee employees[], int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), count, file);
    fclose(file);
    printf("Employees successfully saved to %s\n", filename);
}

void loadEmployees(Employee employees[], int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("No previous save file found (%s). Starting fresh.\n", filename);
        return;
    }
    fread(count, sizeof(int), 1, file);
    fread(employees, sizeof(Employee), *count, file);
    fclose(file);
    printf("Employees successfully loaded from %s\n", filename);
}