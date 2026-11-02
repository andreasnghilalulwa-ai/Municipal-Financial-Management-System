#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100 // Kept for other fixed-size records (suppliers, assets, budgets, projects)

// --- STRUCTURES ---
typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    int id;
    char name[50];
    char department[50];
    double salary;
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
    double value;
    Date acquiredDate;
} Asset;

typedef struct {
    int id;
    char category[50];
    double allocated;
    double spent;
} Budget;

typedef struct {
    int id;
    char title[50];
    Date startDate;
    Date endDate;
} Project;

// --- FUNCTION PROTOTYPES ---
// Week 13 Dynamic Employee Functions
void addEmployee(Employee **employees, int *count, int *capacity);
void displayEmployees(const Employee employees[], int count, int capacity);
void searchEmployeeById(const Employee employees[], int count);

// Other Record Functions
void addSupplier(Supplier suppliers[], int *count);
void displaySuppliers(const Supplier suppliers[], int count);
void addAsset(Asset assets[], int *count);
void displayAssets(const Asset assets[], int count);
void addBudget(Budget budgets[], int *count);
void displayBudgets(const Budget budgets[], int count);
void addProject(Project projects[], int *count);
void displayProjects(const Project projects[], int count);

// File I/O
void saveEmployees(const Employee employees[], int count, const char *filename);
void loadEmployees(Employee **employees, int *count, int *capacity, const char *filename);

int main() {
    // Week 13: Dynamic Employee Pointer, count, and capacity
    int employeeCount = 0;
    int employeeCapacity = 2; // Start small (2) to watch capacity grow (2 -> 4 -> 8 -> 16...)
    
    // TODO 1: malloc initial memory for employees heap array
    Employee *employees = malloc(employeeCapacity * sizeof(Employee));
    if (employees == NULL) {
        printf("Memory allocation failed on startup!\n");
        return 1;
    }

    // Other fixed-size arrays
    Supplier suppliers[MAX_RECORDS];
    int supplierCount = 0;

    Asset assets[MAX_RECORDS];
    int assetCount = 0;

    Budget budgets[MAX_RECORDS];
    int budgetCount = 0;

    Project projects[MAX_RECORDS];
    int projectCount = 0;

    const char *empFile = "employees.dat";

    // Load persisted data on startup
    loadEmployees(&employees, &employeeCount, &employeeCapacity, empFile);

    int choice;
    do {
        printf("\n================ MFMS RECORD MANAGEMENT (WEEK 13) ================\n");
        printf("1. Add Employee          | 7. Display Suppliers\n");
        printf("2. Add Supplier          | 8. Display Assets\n");
        printf("3. Add Asset             | 9. Display Budgets\n");
        printf("4. Add Budget            | 10. Display Projects\n");
        printf("5. Add Project           | 11. Search Employee by ID\n");
        printf("6. Display Employees     | 12. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: 
                // TODO 2 & 3: Check capacity, realloc if full, add employee
                addEmployee(&employees, &employeeCount, &employeeCapacity); 
                break;
            case 2: addSupplier(suppliers, &supplierCount); break;
            case 3: addAsset(assets, &assetCount); break;
            case 4: addBudget(budgets, &budgetCount); break;
            case 5: addProject(projects, &projectCount); break;
            case 6: 
                // TODO 4: Display employees along with count and capacity
                displayEmployees(employees, employeeCount, employeeCapacity); 
                break;
            case 7: displaySuppliers(suppliers, supplierCount); break;
            case 8: displayAssets(assets, assetCount); break;
            case 9: displayBudgets(budgets, budgetCount); break;
            case 10: displayProjects(projects, projectCount); break;
            case 11: 
                // Task 8: Search Employee by ID menu option
                searchEmployeeById(employees, employeeCount);
                break;
            case 12:
                saveEmployees(employees, employeeCount, empFile);
                // TODO 5: Free heap memory before program exits
                free(employees);
                printf("Memory freed successfully. Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 12);

    return 0;
}

// --- DYNAMIC EMPLOYEE FUNCTIONS (Week 13) ---
void addEmployee(Employee **employees, int *count, int *capacity) {
    if (*count >= *capacity) {
        int newCapacity = *capacity * 2; // Double capacity
        Employee *bigger = realloc(*employees, newCapacity * sizeof(Employee));
        if (bigger == NULL) {
            printf("Error: Memory reallocation failed!\n");
            return;
        }
        *employees = bigger;
        *capacity = newCapacity;
        printf("\n[Capacity Notice] Array full! Capacity doubled to %d.\n", *capacity);
    }

    printf("\n--- Add Employee ---\n");
    printf("Enter ID: ");
    scanf("%d", &(*employees)[*count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", (*employees)[*count].name);
    printf("Enter Department: ");
    scanf(" %[^\n]s", (*employees)[*count].department);
    printf("Enter Salary: ");
    scanf("%lf", &(*employees)[*count].salary);
    
    (*count)++;
    printf("Employee added successfully! (Current Count: %d / Capacity: %d)\n", *count, *capacity);
}

void displayEmployees(const Employee employees[], int count, int capacity) {
    if (count == 0) {
        printf("\nNo employees recorded yet. (Capacity: %d)\n", capacity);
        return;
    }
    printf("\n--- EMPLOYEE LIST (Count: %d | Capacity: %d) ---\n", count, capacity);
    printf("----------------------------------------------------\n");
    printf("%-5s | %-20s | %-15s | %-10s\n", "ID", "Name", "Department", "Salary");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | %-15s | $%-9.2f\n", 
               employees[i].id, employees[i].name, employees[i].department, employees[i].salary);
    }
    printf("----------------------------------------------------\n");
}

void searchEmployeeById(const Employee employees[], int count) {
    if (count == 0) {
        printf("\nNo employees to search.\n");
        return;
    }
    int searchId;
    printf("\nEnter Employee ID to search: ");
    scanf("%d", &searchId);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == searchId) {
            printf("\n[Match Found]\n");
            printf("ID: %d | Name: %s | Department: %s | Salary: $%.2f\n",
                   employees[i].id, employees[i].name, employees[i].department, employees[i].salary);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\n[Not Found] No employee with ID %d exists in the record.\n", searchId);
    }
}

// --- OTHER RECORD MANAGEMENT FUNCTIONS ---
void addSupplier(Supplier suppliers[], int *count) {
    if (*count >= MAX_RECORDS) { printf("Array full!\n"); return; }
    printf("\n--- Add Supplier ---\nID: ");
    scanf("%d", &suppliers[*count].id);
    printf("Company Name: "); scanf(" %[^\n]s", suppliers[*count].name);
    printf("Contact Person: "); scanf(" %[^\n]s", suppliers[*count].contactPerson);
    printf("Phone: "); scanf(" %[^\n]s", suppliers[*count].phone);
    (*count)++;
    printf("Added successfully!\n");
}

void displaySuppliers(const Supplier suppliers[], int count) {
    if (count == 0) { printf("\nNo suppliers recorded.\n"); return; }
    printf("\n%-5s | %-20s | %-20s | %-15s\n", "ID", "Company", "Contact", "Phone");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%-5d | %-20s | %-20s | %-15s\n", suppliers[i].id, suppliers[i].name, suppliers[i].contactPerson, suppliers[i].phone);
}

void addAsset(Asset assets[], int *count) {
    if (*count >= MAX_RECORDS) { printf("Array full!\n"); return; }
    printf("\n--- Add Asset ---\nID: ");
    scanf("%d", &assets[*count].id);
    printf("Asset Name: "); scanf(" %[^\n]s", assets[*count].name);
    printf("Value: "); scanf("%lf", &assets[*count].value);
    printf("Acquired Date (DD MM YYYY): ");
    scanf("%d %d %d", &assets[*count].acquiredDate.day, &assets[*count].acquiredDate.month, &assets[*count].acquiredDate.year);
    (*count)++;
    printf("Added successfully!\n");
}

void displayAssets(const Asset assets[], int count) {
    if (count == 0) { printf("\nNo assets recorded.\n"); return; }
    printf("\n%-5s | %-20s | %-10s | %-12s\n", "ID", "Asset Name", "Value", "Acquired");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%-5d | %-20s | $%-9.2f | %02d/%02d/%4d\n", assets[i].id, assets[i].name, assets[i].value, assets[i].acquiredDate.day, assets[i].acquiredDate.month, assets[i].acquiredDate.year);
}

void addBudget(Budget budgets[], int *count) {
    if (*count >= MAX_RECORDS) { printf("Array full!\n"); return; }
    printf("\n--- Add Budget ---\nID: ");
    scanf("%d", &budgets[*count].id);
    printf("Category: "); scanf(" %[^\n]s", budgets[*count].category);
    printf("Allocated: "); scanf("%lf", &budgets[*count].allocated);
    printf("Spent: "); scanf("%lf", &budgets[*count].spent);
    (*count)++;
    printf("Added successfully!\n");
}

void displayBudgets(const Budget budgets[], int count) {
    if (count == 0) { printf("\nNo budgets recorded.\n"); return; }
    printf("\n%-5s | %-18s | %-10s | %-10s | %-10s\n", "ID", "Category", "Allocated", "Spent", "Balance");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        double balance = budgets[i].allocated - budgets[i].spent;
        printf("%-5d | %-18s | $%-9.2f | $%-9.2f | $%-9.2f\n", budgets[i].id, budgets[i].category, budgets[i].allocated, budgets[i].spent, balance);
    }
}

void addProject(Project projects[], int *count) {
    if (*count >= MAX_RECORDS) { printf("Array full!\n"); return; }
    printf("\n--- Add Project ---\nID: ");
    scanf("%d", &projects[*count].id);
    printf("Title: "); scanf(" %[^\n]s", projects[*count].title);
    printf("Start Date (DD MM YYYY): ");
    scanf("%d %d %d", &projects[*count].startDate.day, &projects[*count].startDate.month, &projects[*count].startDate.year);
    printf("End Date (DD MM YYYY): ");
    scanf("%d %d %d", &projects[*count].endDate.day, &projects[*count].endDate.month, &projects[*count].endDate.year);
    (*count)++;
    printf("Added successfully!\n");
}

void displayProjects(const Project projects[], int count) {
    if (count == 0) { printf("\nNo projects recorded.\n"); return; }
    printf("\n%-5s | %-20s | %-15s | %-15s\n", "ID", "Project Title", "Start Date", "End Date");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%-5d | %-20s | %02d/%02d/%4d    | %02d/%02d/%4d\n", projects[i].id, projects[i].title, projects[i].startDate.day, projects[i].startDate.month, projects[i].startDate.year, projects[i].endDate.day, projects[i].endDate.month, projects[i].endDate.year);
}

// --- FILE I/O ---
void saveEmployees(const Employee employees[], int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return;
    fwrite(&count, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), count, file);
    fclose(file);
}

void loadEmployees(Employee **employees, int *count, int *capacity, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;
    
    fread(count, sizeof(int), 1, file);
    
    // Ensure capacity is large enough to hold loaded records
    if (*count > *capacity) {
        *capacity = *count;
        Employee *bigger = realloc(*employees, *capacity * sizeof(Employee));
        if (bigger != NULL) {
            *employees = bigger;
        }
    }
    
    fread(*employees, sizeof(Employee), *count, file);
    fclose(file);
}