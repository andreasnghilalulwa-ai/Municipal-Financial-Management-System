#include <stdio.h>

void displayWelcome();
float calculateVAT(float amount);
float calculateSalary(float basic, float housing, float transport);
float calculateBudget(float revenue, float expenses);
void displayMenu();
int searchEmployee(int id, int ids[], int size);

int main() {
    int choice;
    int employeeIDs[] = {101, 102, 103, 104, 105};
    int size = 5;


    displayWelcome();
    printf("\n");

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: { 
                float amount;
                printf("Enter amount: ");
                scanf("%f", &amount);
                float vat = calculateVAT(amount);
                printf("VAT: %.2f\n\n", vat);
                break;
            }
            case 2: { 
                float basic, housing, transport;
                printf("Basic salary: ");
                scanf("%f", &basic);
                printf("Housing allowance: ");
                scanf("%f", &housing);
                printf("Transport allowance: ");
                scanf("%f", &transport);
                
                float gross = calculateSalary(basic, housing, transport);
                printf("Gross salary: %.2f\n\n", gross);
                break;
            }
            case 3: { // Budget Calculation (Task 4)
                float revenue, expenses;
                printf("Enter revenue: ");
                scanf("%f", &revenue);
                printf("Enter expenses: ");
                scanf("%f", &expenses);
                
                calculateBudget(revenue, expenses);
                printf("\n");
                break;
            }
            case 4: {
                int searchID;
                printf("Enter employee ID: ");
                scanf("%d", &searchID);
                
                int position = searchEmployee(searchID, employeeIDs, size);
                if (position != -1) {
                    printf("Employee found at position %d.\n\n", position);
                } else {
                    printf("Employee not found.\n\n");
                }
                break;
            }
            case 5:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid choice.\n\n");
        }

    } while (choice != 5);

    return 0;
}

void displayWelcome() {
    printf("Welcome to the Municipal Financial Management System\n");
}

float calculateVAT(float amount) {
    return amount * 0.15;
}


float calculateSalary(float basic, float housing, float transport) {
    return basic + housing + transport;
}


float calculateBudget(float revenue, float expenses) {
    float result = revenue - expenses;
    
    if (result > 0) {
        printf("SURPLUS\n");
    } else if (result < 0) {
        printf("DEFICIT\n");
    } else {
        printf("BALANCED\n");
    }
    
    return result;
}

void displayMenu() {
    printf("==================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT\n");
    printf("==================================\n");
    printf("1. Calculate VAT\n");
    printf("2. Calculate Salary\n");
    printf("3. Calculate Budget\n");
    printf("4. Search Employee\n");
    printf("5. Exit\n");
    printf("\nEnter choice: ");
}

int searchEmployee(int id, int ids[], int size) {
    for (int i = 0; i < size; i++) {
        if (ids[i] == id) {
            return i; 
        }
    }
    return -1;
}