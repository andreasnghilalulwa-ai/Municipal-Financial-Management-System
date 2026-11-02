#include <stdio.h>
#include <string.h>

// Function prototypes for each section
void runEmployeeSystem();
void runBudgetSystem();
void runVehicleSystem();
void runAssessmentQuestions();

int main() {
    int mainChoice;

    do {
        printf("\n====================================================\n");
        printf("         MASTER C ASSIGNMENT & CHALLENGE MENU       \n");
        printf("====================================================\n");
        printf("1. Part A & Integrated Challenge: Employee Salaries\n");
        printf("2. Part B: Department Budgets\n");
        printf("3. Part C: Vehicle Registration Numbers\n");
        printf("4. Assessment Questions (Q1 - Q7 Demos)\n");
        printf("5. Exit Program\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                runEmployeeSystem();
                break;
            case 2:
                runBudgetSystem();
                break;
            case 3:
                runVehicleSystem();
                break;
            case 4:
                runAssessmentQuestions();
                break;
            case 5:
                printf("\nExiting program. Thank you!\n");
                break;
            default:
                printf("\n[!] Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (mainChoice != 5);

    return 0;
}

// ====================================================
// SECTION 1: EMPLOYEE SALARIES & INTEGRATED CHALLENGE
// ====================================================
void runEmployeeSystem() {
    float salaries[50];
    int choice;
    int captured = 0;

    do {
        printf("\n--- Employee Salary Management System (50 Employees) ---\n");
        printf("1. Capture salaries for 50 employees\n");
        printf("2. Display all salaries\n");
        printf("3. Calculate total salary expenditure\n");
        printf("4. Calculate average salary\n");
        printf("5. Find highest salary\n");
        printf("6. Find lowest salary\n");
        printf("7. Search for a particular salary\n");
        printf("8. Sort salaries from lowest to highest\n");
        printf("9. Display sorted salaries\n");
        printf("10. Return to Main Menu\n");
        printf("Enter choice (1-10): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter salaries for 50 employees:\n");
                for (int i = 0; i < 50; i++) {
                    printf("Employee %d: ", i + 1);
                    scanf("%f", &salaries[i]);
                }
                captured = 1;
                printf("[+] 50 Salaries captured successfully!\n");
                break;
            case 2:
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                printf("\n--- All Employee Salaries ---\n");
                for (int i = 0; i < 50; i++) {
                    printf("Employee %d: $%.2f\n", i + 1, salaries[i]);
                }
                break;
            case 3: {
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                float total = 0;
                for (int i = 0; i < 50; i++) total += salaries[i];
                printf("\nTotal Salary Expenditure: $%.2f\n", total);
                break;
            }
            case 4: {
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                float total = 0;
                for (int i = 0; i < 50; i++) total += salaries[i];
                printf("\nAverage Salary: $%.2f\n", total / 50);
                break;
            }
            case 5: {
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                float highest = salaries[0];
                for (int i = 1; i < 50; i++) {
                    if (salaries[i] > highest) highest = salaries[i];
                }
                printf("\nHighest Salary: $%.2f\n", highest);
                break;
            }
            case 6: {
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                float lowest = salaries[0];
                for (int i = 1; i < 50; i++) {
                    if (salaries[i] < lowest) lowest = salaries[i];
                }
                printf("\nLowest Salary: $%.2f\n", lowest);
                break;
            }
            case 7: {
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                float target;
                int found = 0;
                printf("\nEnter salary to search: ");
                scanf("%f", &target);
                for (int i = 0; i < 50; i++) {
                    if (salaries[i] == target) {
                        printf("[+] Salary $%.2f found at Employee position %d\n", target, i + 1);
                        found = 1;
                    }
                }
                if (!found) printf("[-] Salary $%.2f not found.\n", target);
                break;
            }
            case 8: {
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                float temp;
                for (int i = 0; i < 49; i++) {
                    for (int j = 0; j < 49 - i; j++) {
                        if (salaries[j] > salaries[j + 1]) {
                            temp = salaries[j];
                            salaries[j] = salaries[j + 1];
                            salaries[j + 1] = temp;
                        }
                    }
                }
                printf("\n[+] Salaries successfully sorted in ascending order!\n");
                break;
            }
            case 9:
                if (!captured) { printf("[!] Please capture salaries first (Option 1).\n"); break; }
                printf("\n--- Sorted Salaries (Lowest to Highest) ---\n");
                for (int i = 0; i < 50; i++) {
                    printf("Employee %d: $%.2f\n", i + 1, salaries[i]);
                }
                break;
            case 10:
                return;
            default:
                printf("[!] Invalid choice. Enter 1-10.\n");
        }
    } while (choice != 10);
}

// ====================================================
// SECTION 2: DEPARTMENT BUDGETS
// ====================================================
void runBudgetSystem() {
    float budgets[10];
    float total = 0, temp;

    printf("\n--- Department Budgets Management (10 Budgets) ---\n");
    printf("Enter budgets for 10 departments:\n");
    for (int i = 0; i < 10; i++) {
        printf("Department %d: ", i + 1);
        scanf("%f", &budgets[i]);
        total += budgets[i];
    }

    printf("\n--- Department Budgets Summary ---\n");
    for (int i = 0; i < 10; i++) {
        printf("Dept %d: $%.2f\n", i + 1, budgets[i]);
    }
    printf("\nTotal Budget: $%.2f", total);
    printf("\nAverage Budget: $%.2f\n", total / 10);

    // Sort budgets from lowest to highest
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9 - i; j++) {
            if (budgets[j] > budgets[j + 1]) {
                temp = budgets[j];
                budgets[j] = budgets[j + 1];
                budgets[j + 1] = temp;
            }
        }
    }

    printf("\n--- Budgets Sorted (Lowest to Highest) ---\n");
    for (int i = 0; i < 10; i++) {
        printf("$%.2f\n", budgets[i]);
    }
}

// ====================================================
// SECTION 3: VEHICLE REGISTRATION NUMBERS
// ====================================================
void runVehicleSystem() {
    char registrations[20][20];
    char searchTarget[20];
    int found = 0;

    printf("\n--- Vehicle Registration Management (20 Vehicles) ---\n");
    printf("Enter 20 vehicle registration numbers:\n");
    for (int i = 0; i < 20; i++) {
        printf("Vehicle %d: ", i + 1);
        scanf("%s", registrations[i]);
    }

    printf("\n--- Vehicle Registration List ---\n");
    for (int i = 0; i < 20; i++) {
        printf("%d. %s\n", i + 1, registrations[i]);
    }

    printf("\nEnter registration number to search: ");
    scanf("%s", searchTarget);

    for (int i = 0; i < 20; i++) {
        if (strcmp(registrations[i], searchTarget) == 0) {
            printf("[+] Registration '%s' found at Vehicle index %d (Vehicle %d)\n", searchTarget, i, i + 1);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[-] Registration '%s' not found.\n", searchTarget);
    }
}

// ====================================================
// SECTION 4: ASSESSMENT QUESTIONS (Q1 - Q7)
// ====================================================
void runAssessmentQuestions() {
    int qChoice;

    do {
        printf("\n--- Assessment Questions Menu (Q1 - Q7) ---\n");
        printf("1. Q1: For Loop (Numbers 1 to 100)\n");
        printf("2. Q2: While Loop (Validate Positive Salary)\n");
        printf("3. Q3: Do While Loop (Interactive Menu)\n");
        printf("4. Q4: Break and Continue (Process 20 Salaries)\n");
        printf("5. Q5: Arrays (Capture 50 Salaries)\n");
        printf("6. Q6: Searching (Search an array of 20 salaries)\n");
        printf("7. Q7: Sorting (Sort 10 Department Budgets)\n");
        printf("8. Return to Main Menu\n");
        printf("Choose question (1-8): ");
        scanf("%d", &qChoice);

        switch (qChoice) {
            case 1: {
                printf("\n--- Q1: Numbers 1 to 100 ---\n");
                for (int i = 1; i <= 100; i++) {
                    printf("%d ", i);
                }
                printf("\n");
                break;
            }
            case 2: {
                printf("\n--- Q2: Validate Positive Salary ---\n");
                float salary = -1;
                while (salary <= 0) {
                    printf("Enter a positive salary: ");
                    scanf("%f", &salary);
                    if (salary <= 0) {
                        printf("Invalid. Salary must be > 0.\n");
                    }
                }
                printf("Valid salary captured: $%.2f\n", salary);
                break;
            }
            case 3: {
                printf("\n--- Q3: Menu Do-While Loop ---\n");
                int menuOpt;
                do {
                    printf("\n1. View salaries\n2. Add salary\n3. Search salary\n4. Exit\nChoose: ");
                    scanf("%d", &menuOpt);
                    if (menuOpt >= 1 && menuOpt <= 3) printf("Action %d performed.\n", menuOpt);
                    else if (menuOpt != 4) printf("Invalid option.\n");
                } while (menuOpt != 4);
                break;
            }
            case 4: {
                printf("\n--- Q4: Break & Continue (20 Salaries) ---\n");
                float sal;
                for (int i = 1; i <= 20; i++) {
                    printf("Enter salary %d (0 to stop): ", i);
                    scanf("%f", &sal);
                    if (sal == 0) {
                        printf("Stop signal received (0). Exiting loop.\n");
                        break;
                    }
                    if (sal < 0) {
                        printf("Negative salary ignored.\n");
                        continue;
                    }
                    printf("Processed salary: $%.2f\n", sal);
                }
                break;
            }
            case 5: {
                printf("\n--- Q5: Arrays (50 Salaries Loop) ---\n");
                float q5Salaries[50];
                printf("Entering quick capture for 50 salaries:\n");
                for (int i = 0; i < 50; i++) {
                    printf("Sal %d: ", i + 1);
                    scanf("%f", &q5Salaries[i]);
                }
                printf("50 salaries successfully captured in array!\n");
                break;
            }
            case 6: {
                printf("\n--- Q6: Searching 20 Salaries ---\n");
                float sampleSalaries[20] = {1000, 2000, 3000, 4000, 5000, 1500, 2500, 3500, 4500, 5500,
                                            1200, 2200, 3200, 4200, 5200, 1800, 2800, 3800, 4800, 5800};
                float target;
                int found = 0;
                printf("Enter salary to search in preset array: ");
                scanf("%f", &target);
                for (int i = 0; i < 20; i++) {
                    if (sampleSalaries[i] == target) {
                        printf("Found $%.2f at index %d\n", target, i);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Salary not found.\n");
                break;
            }
            case 7: {
                printf("\n--- Q7: Sorting 10 Department Budgets ---\n");
                float sampleBudgets[10] = {45000, 12000, 89000, 33000, 67000, 21000, 54000, 15000, 92000, 41000};
                float temp;
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9 - i; j++) {
                        if (sampleBudgets[j] > sampleBudgets[j + 1]) {
                            temp = sampleBudgets[j];
                            sampleBudgets[j] = sampleBudgets[j + 1];
                            sampleBudgets[j + 1] = temp;
                        }
                    }
                }
                printf("Sorted Budgets (Ascending):\n");
                for (int i = 0; i < 10; i++) {
                    printf("$%.2f\n", sampleBudgets[i]);
                }
                break;
            }
            case 8:
                return;
            default:
                printf("Invalid selection (1-8).\n");
        }
    } while (qChoice != 8);
}