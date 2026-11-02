#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 100

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
    double salary; // Updated to double for Week 12
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
// Week 12 Pointer Functions (Parts B & C)
void pointerWarmupDemo();
void swapSalaries(double *a, double *b);
void swapSalariesWrong(double a, double b);
void displaySalaries(const double salaries[], int n);
double findHighest(const double salaries[], int n);
double calculateAverage(const double salaries[], int n);
void giveRaise(double salaries[], int n, double percent);

// Week 12 Pointer Functions (Part D)
void updateSalary(Employee *e, double newSalary);
Employee *findEmployee(Employee list[], int n, int id);

// Week 11 & 12 Record Functions
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

int main() {
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

    // Load persisted data on startup
    loadEmployees(employees, &employeeCount, empFile);

    // Run pointer warm-up and array tests on startup
    pointerWarmupDemo();

    int choice;
    do {
        printf("\n================ MFMS RECORD MANAGEMENT (WEEK 11 & 12) ================\n");
        printf("1. Add Employee          | 7. Display Suppliers\n");
        printf("2. Add Supplier          | 8. Display Assets\n");
        printf("3. Add Asset             | 9. Display Budgets\n");
        printf("4. Add Budget            | 10. Display Projects\n");
        printf("5. Add Project           | 11. Update Emp Salary (Ptr)\n");
        printf("6. Display Employees     | 12. Save & Exit\n");
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
            case 11: {
                int searchId;
                double newSal;
                printf("\nEnter Employee ID to update: ");
                scanf("%d", &searchId);

                Employee *target = findEmployee(employees, employeeCount, searchId);
                if (target != NULL) {
                    printf("Found Employee: %s (Current Salary: $%.2f)\n", target->name, target->salary);
                    printf("Enter new salary: ");
                    scanf("%lf", &newSal);

                    updateSalary(target, newSal);
                    printf("\nUpdated Record Details:\n");
                    printf("ID: %d | Name: %s | Dept: %s | Salary: $%.2f\n", 
                           target->id, target->name, target->department, target->salary);
                } else {
                    printf("\n[Friendly Notice] Employee with ID %d was not found.\n", searchId);
                }
                break;
            }
            case 12:
                saveEmployees(employees, employeeCount, empFile);
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 12);

    return 0;
}

// --- POINTER DEMOS & ARRAY PROCESSING ---
void pointerWarmupDemo() {
    printf("\n--- [Part A] Pointer Warm-up ---\n");
    int val = 42;
    int *p = &val;
    printf("Value: %d | Address: %p | *p: %d\n", val, (void*)p, *p);
    *p = 100;
    printf("After pointer update -> Value: %d\n", val);

    printf("\n--- [Part B] Salary Swap ---\n");
    double sal1 = 45000.0, sal2 = 72000.0;
    printf("Before swap: sal1 = $%.2f, sal2 = $%.2f\n", sal1, sal2);
    swapSalaries(&sal1, &sal2);
    printf("After correct swap (&): sal1 = $%.2f, sal2 = $%.2f\n", sal1, sal2);
    swapSalariesWrong(sal1, sal2);
    printf("After wrong swap (value): sal1 = $%.2f, sal2 = $%.2f (unchanged)\n", sal1, sal2);

    printf("\n--- [Part C] Salary Arrays ---\n");
    double salaries[] = {50000.0, 65000.0, 80000.0};
    int n = 3;
    displaySalaries(salaries, n);
    printf("Highest: $%.2f | Average: $%.2f\n", findHighest(salaries, n), calculateAverage(salaries, n));
    giveRaise(salaries, n, 10.0);
    printf("After 10%% raise: ");
    displaySalaries(salaries, n);
    printf("---------------------------------------\n\n");
}

void swapSalaries(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void swapSalariesWrong(double a, double b) {
    double temp = a;
    a = b;
    b = temp;
}

void displaySalaries(const double salaries[], int n) {
    printf("Salaries: ");
    for (int i = 0; i < n; i++) printf("$%.2f ", salaries[i]);
    printf("\n");
}

double findHighest(const double salaries[], int n) {
    if (n <= 0) return 0.0;
    double high = salaries[0];
    for (int i = 1; i < n; i++) if (salaries[i] > high) high = salaries[i];
    return high;
}

double calculateAverage(const double salaries[], int n) {
    if (n <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += salaries[i];
    return sum / n;
}

void giveRaise(double salaries[], int n, double percent) {
    for (int i = 0; i < n; i++) salaries[i] += salaries[i] * (percent / 100.0);
}

// --- EMPLOYEE POINTER FUNCTIONS ---
void updateSalary(Employee *e, double newSalary) {
    if (e != NULL) {
        e->salary = newSalary;
    }
}

Employee *findEmployee(Employee list[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (list[i].id == id) {
            return &list[i];
        }
    }
    return NULL;
}

// --- RECORD MANAGEMENT FUNCTIONS ---
void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_RECORDS) { printf("Array full!\n"); return; }
    printf("\n--- Add Employee ---\nID: ");
    scanf("%d", &employees[*count].id);
    printf("Name: "); scanf(" %[^\n]s", employees[*count].name);
    printf("Department: "); scanf(" %[^\n]s", employees[*count].department);
    printf("Salary: "); scanf("%lf", &employees[*count].salary);
    (*count)++;
    printf("Added successfully!\n");
}

void displayEmployees(const Employee employees[], int count) {
    if (count == 0) { printf("\nNo employees recorded.\n"); return; }
    printf("\n%-5s | %-20s | %-15s | %-10s\n", "ID", "Name", "Department", "Salary");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++)
        printf("%-5d | %-20s | %-15s | $%-9.2f\n", employees[i].id, employees[i].name, employees[i].department, employees[i].salary);
}

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

void saveEmployees(const Employee employees[], int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return;
    fwrite(&count, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), count, file);
    fclose(file);
}

void loadEmployees(Employee employees[], int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;
    fread(count, sizeof(int), 1, file);
    fread(employees, sizeof(Employee), *count, file);
    fclose(file);
}