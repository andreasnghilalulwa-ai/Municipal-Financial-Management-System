#include <stdio.h> 
 
int main() { 
 
    int employees = 750;     double revenue = 12500000.50;     double expenses = 10750000.25; 
    char category = 'A'; 
 
    double balance = revenue - expenses; 
 
    printf("MUNICIPAL FINANCIAL SUMMARY\n"); 
    printf("----------------------------\n"); 
 
    printf("Employees: %d\n", employees);     printf("Revenue: %.2f\n", revenue);     printf("Expenses: %.2f\n", expenses);     printf("Category: %c\n", category); 
    printf("Balance: %.2f\n", balance); 
 
    return 0; } 
