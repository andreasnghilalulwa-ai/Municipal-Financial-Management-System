#include <stdio.h>
#include <string.h>

#define MAX_SUPPLIERS 5
#define MAX_LEN 100

// Helper function to remove trailing newline character from fgets
void clear_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

int main() {
    // Parallel arrays to store information for up to 5 suppliers
    char names[MAX_SUPPLIERS][MAX_LEN];
    char emails[MAX_SUPPLIERS][MAX_LEN];
    char phones[MAX_SUPPLIERS][MAX_LEN];
    char towns[MAX_SUPPLIERS][MAX_LEN];
    
    int supplier_count = 0;
    int choice;

    do {
        printf("\n================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT \n");
        printf("================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier (Task 3 / Challenge)\n");
        printf("4. Show String Lengths (Task 2)\n");
        printf("5. Copy Supplier Name (Task 4 Demo)\n");
        printf("6. Construct Description (Task 5 Demo)\n");
        printf("7. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        getchar(); // Consume newline left in input buffer by scanf

        switch (choice) {
            case 1: // Task 1 & Challenge Addition
                if (supplier_count < MAX_SUPPLIERS) {
                    printf("\n--- ADD SUPPLIER (%d/%d) ---\n", supplier_count + 1, MAX_SUPPLIERS);
                    
                    printf("Enter supplier name: ");
                    fgets(names[supplier_count], MAX_LEN, stdin);
                    clear_newline(names[supplier_count]);

                    printf("Enter email: ");
                    fgets(emails[supplier_count], MAX_LEN, stdin);
                    clear_newline(emails[supplier_count]);

                    printf("Enter phone: ");
                    fgets(phones[supplier_count], MAX_LEN, stdin);
                    clear_newline(phones[supplier_count]);

                    printf("Enter town: ");
                    fgets(towns[supplier_count], MAX_LEN, stdin);
                    clear_newline(towns[supplier_count]);

                    supplier_count++;
                    printf("Supplier added successfully!\n");
                } else {
                    printf("\nMaximum limit of %d suppliers reached.\n", MAX_SUPPLIERS);
                }
                break;

            case 2: // Display Supplier Details
                if (supplier_count == 0) {
                    printf("\nNo suppliers recorded yet.\n");
                } else {
                    for (int i = 0; i < supplier_count; i++) {
                        printf("\n--- SUPPLIER DETAILS (%d) ---\n", i + 1);
                        printf("Name : %s\n", names[i]);
                        printf("Email: %s\n", emails[i]);
                        printf("Phone: %s\n", phones[i]);
                        printf("Town : %s\n", towns[i]);
                    }
                }
                break;

            case 3: { // Task 3: Supplier Search using strcmp()
                if (supplier_count == 0) {
                    printf("\nNo suppliers available to search.\n");
                    break;
                }
                char search_term[MAX_LEN];
                printf("\nEnter supplier name to search: ");
                fgets(search_term, MAX_LEN, stdin);
                clear_newline(search_term);

                int found = 0;
                for (int i = 0; i < supplier_count; i++) {
                    if (strcmp(names[i], search_term) == 0) {
                        printf("\nSupplier found!\n");
                        printf("Name : %s\n", names[i]);
                        printf("Email: %s\n", emails[i]);
                        printf("Phone: %s\n", phones[i]);
                        printf("Town : %s\n", towns[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("\nSupplier not found.\n");
                }
                break;
            }

            case 4: { // Task 2: String Length using strlen()
                if (supplier_count == 0) {
                    printf("\nNo suppliers available.\n");
                    break;
                }
                printf("\n--- SUPPLIER STRING LENGTHS ---\n");
                for (int i = 0; i < supplier_count; i++) {
                    printf("[%s]\n", names[i]);
                    printf("  - Supplier name length: %lu\n", strlen(names[i]));
                    printf("  - Email length        : %lu\n", strlen(emails[i]));
                    printf("  - Town length         : %lu\n", strlen(towns[i]));
                }
                break;
            }

            case 5: { // Task 4: Copying Strings using strcpy()
                if (supplier_count == 0) {
                    printf("\nNo suppliers available to copy.\n");
                    break;
                }
                char backup[MAX_LEN];
                strcpy(backup, names[0]);
                
                printf("\n--- TASK 4: COPY SUPPLIER NAME ---\n");
                printf("Original (names[0]): %s\n", names[0]);
                printf("Backup   (copied)  : %s\n", backup);
                break;
            }

            case 6: { // Task 5: Concatenating Strings using strcat()
                if (supplier_count == 0) {
                    printf("\nNo suppliers available to construct description.\n");
                    break;
                }
                char description[MAX_LEN * 2] = "";
                strcat(description, names[0]);
                strcat(description, " operates in ");
                strcat(description, towns[0]);
                strcat(description, ".");

                printf("\n--- TASK 5: CONSTRUCT DESCRIPTION ---\n");
                printf("%s\n", description);
                break;
            }

            case 7:
                printf("\nExiting Municipal Financial Management System. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a number between 1 and 7.\n");
        }
    } while (choice != 7);

    return 0;
}