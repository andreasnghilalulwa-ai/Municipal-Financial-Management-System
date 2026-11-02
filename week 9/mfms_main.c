#include <stdio.h>
#include <string.h>

#define MAX_EMPLOYEES 50
#define MAX_NAME_LEN 50

/* --- Data Structures --- */
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    double salary;
} Employee;

/* --- Function Prototypes --- */
/* Utilities */
void clearInputBuffer(void);
int getInteger(void);
double getPositiveDouble(void);

/* Employees */
void addEmployee(Employee employees[], int *count);
void displayEmployees(const Employee employees[], int count);

/* Budget */
void inputBudgetDetails(double *revenue, double *expenses);
double calculateNetBalance(double revenue, double expenses);

/* Reports */
void generateSummaryReport(const Employee employees[], int count, double revenue, double expenses);


/* --- Main Function --- */
int main(void) {
    Employee employees[MAX_EMPLOYEES];
    int empCount = 0;
    double revenue = 0.0;
    double expenses = 0.0;
    int choice;

    do {
        printf("\n--- MUNICIPAL FINANCIAL MANAGEMENT SYSTEM (MFMS) ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Enter Budget Details\n");
        printf("4. Generate Summary Report\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        choice = getInteger();

        switch (choice) {
            case 1:
                addEmployee(employees, &empCount);
                break;
            case 2:
                displayEmployees(employees, empCount);
                break;
            case 3:
                inputBudgetDetails(&revenue, &expenses);
                break;
            case 4:
                generateSummaryReport(employees, empCount, revenue, expenses);
                break;
            case 5:
                printf("Exiting MFMS. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}


/* --- Utility Implementations --- */
void clearInputBuffer(void) {
    while (getchar() != '\n');
}

int getInteger(void) {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Please enter an integer: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

double getPositiveDouble(void) {
    double value;
    while (scanf("%lf", &value) != 1 || value < 0) {
        printf("Invalid input. Please enter a positive number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}


/* --- Employee Implementations --- */
void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Employee list is full!\n");
        return;
    }
    
    printf("Enter Employee ID: ");
    employees[*count].id = getInteger();
    
    printf("Enter Employee Name: ");
    fgets(employees[*count].name, MAX_NAME_LEN, stdin);
    employees[*count].name[strcspn(employees[*count].name, "\n")] = '\0';
    
    printf("Enter Employee Salary: ");
    employees[*count].salary = getPositiveDouble();
    
    (*count)++;
    printf("Employee added successfully!\n");
}

void displayEmployees(const Employee employees[], int count) {
    if (count == 0) {
        printf("No employee records found.\n");
        return;
    }
    
    printf("\n--- EMPLOYEE LIST ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Salary: $%.2f\n", 
               employees[i].id, employees[i].name, employees[i].salary);
    }
}


/* --- Budget Implementations --- */
void inputBudgetDetails(double *revenue, double *expenses) {
    printf("Enter total municipal revenue: ");
    *revenue = getPositiveDouble();
    
    printf("Enter total municipal expenses: ");
    *expenses = getPositiveDouble();
}

double calculateNetBalance(double revenue, double expenses) {
    return revenue - expenses;
}


/* --- Report Implementations --- */
void generateSummaryReport(const Employee employees[], int count, double revenue, double expenses) {
    double net = calculateNetBalance(revenue, expenses);
    
    printf("\n========================================\n");
    printf("       MFMS FINANCIAL & STAFF REPORT    \n");
    printf("========================================\n");
    printf("Total Registered Employees: %d\n", count);
    printf("Total Revenue:  $%.2f\n", revenue);
    printf("Total Expenses: $%.2f\n", expenses);
    printf("Net Balance:    $%.2f\n", net);
    printf("========================================\n");
    
    /* Optional: preview employee records inside report */
    if (count > 0) {
        printf("\nStaff Summary:\n");
        for (int i = 0; i < count; i++) {
            printf("- %s (ID: %d): $%.2f\n", employees[i].name, employees[i].id, employees[i].salary);
        }
        printf("========================================\n");
    }
}