#include <stdio.h>
#include <string.h>
#include <ctype.h> 
struct Customer {
    int id;
    char name[50];
    char phone[15];
    float previous_reading;
    float current_reading;
    float units_consumed;
    float energy_charges;
    float fixed_charge;
    float total_bill;
};
struct Customer registerCustomer();
void calculateUnits(struct Customer *c); 
void calculateBill(struct Customer *c);
void printBill(struct Customer c);
int isValidName(char *name);
int isValidPhone(char *phone);


int main() {
    int choice;
    struct Customer cust;
    int isRegistered = 0;

    while (1) {
        printf("\n=============================================\n");
        printf("    ELECTRICITY BILL MANAGEMENT SYSTEM     \n");
        printf("=================================================\n");
        printf("1. Register Customer & Meter Readings\n");
        printf("2. Calculate Units Consumed\n");
        printf("3. Calculate Bill (Slab Rates + Fixed)\n");
        printf("4. Display Final Bill\n");
        printf("5. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                cust = registerCustomer();
                isRegistered = 1;
                printf("\n Customer registered successfully!\n");
                break;

            case 2:
                if (!isRegistered) {
                    printf("\n[ERROR] Please register a customer first (Option 1).\n");
                } else {
                    calculateUnits(&cust);
                    printf("\n[INFO] Units Consumed: %.2f units\n", cust.units_consumed);
                }
                break;

            case 3:
                if (!isRegistered) {
                    printf("\n[ERROR] Please register a customer first (Option 1).\n");
                } else {
                    calculateUnits(&cust);
                    calculateBill(&cust);
                    printf("\n[SUCCESS] Bill calculated successfully!\n");
                }
                break;

            case 4:
                if (!isRegistered) {
                    printf("\n[ERROR] Please register a customer first (Option 1).\n");
                } else {
                    calculateUnits(&cust);
                    calculateBill(&cust);
                    printBill(cust);
                }
                break;

            case 5:
                printf("\nThank you for using Electricity Bill Management System.\n");
                return 0;

            default:
                printf("\n[INVALID] Invalid choice! Please enter a number between 1 and 5.\n");
        }
    }

    return 0;
}


int isValidName(char *name) {
    if (strlen(name) == 0) return 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0; 
        }
    }
    return 1;
}


int isValidPhone(char *phone) {
    if (strlen(phone) == 0) return 0;
    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit(phone[i])) {
            return 0; 
        }
    }
    return 1;
}



struct Customer registerCustomer() {
    struct Customer c;

    printf("\n--- CUSTOMER REGISTRATION ---\n");
    

    printf("Enter Customer ID: ");
    while (scanf("%d", &c.id) != 1) {
        printf("[ERROR] Invalid ID! Please enter numbers only: ");
        while(getchar() != '\n'); 
    }
    getchar(); 


    while (1) {
        printf("Enter Customer Name (Alphabets only): ");
        fgets(c.name, sizeof(c.name), stdin);
        c.name[strcspn(c.name, "\n")] = 0; 

        if (isValidName(c.name)) {
            break;
        }
        printf("[ERROR] Name can only contain letters and spaces. No numbers or special symbols allowed!\n");
    }

  
    while (1) {
        printf("Enter Phone Number (Digits only): ");
        fgets(c.phone, sizeof(c.phone), stdin);
        c.phone[strcspn(c.phone, "\n")] = 0;

        if (isValidPhone(c.phone)) {
            break;
        }
        printf("[ERROR] Phone number can only contain numeric digits (0-9)!\n");
    }


    printf("Enter Previous Meter Reading (kWh): ");
    while (scanf("%f", &c.previous_reading) != 1 || c.previous_reading < 0) {
        printf("[ERROR] Invalid reading! Enter a positive number: ");
        while(getchar() != '\n');
    }

  
    printf("Enter Current Meter Reading (kWh): ");
    while (scanf("%f", &c.current_reading) != 1 || c.current_reading < c.previous_reading) {
        printf("[ERROR] Current reading cannot be less than previous reading or invalid! Re-enter: ");
        while(getchar() != '\n');
    }


    c.fixed_charge = 50.0;

    return c;
}


void calculateUnits(struct Customer *c) {
    (*c).units_consumed = (*c).current_reading - (*c).previous_reading;
}



void calculateBill(struct Customer *c) {
    float units = (*c).units_consumed;
    float energy_cost = 0.0;

    if (units <= 100) {
        energy_cost = units * 3.00;
    } else if (units <= 200) {
        energy_cost = (100 * 3.00) + ((units - 100) * 5.00);
    } else {
        energy_cost = (100 * 3.00) + (100 * 5.00) + ((units - 200) * 8.00);
    }

    (*c).energy_charges = energy_cost;
    (*c).total_bill = (*c).energy_charges + (*c).fixed_charge;
}


void printBill(struct Customer c) {
    printf("\n===========================================\n");
    printf("           ELECTRICITY INVOICE             \n");
    printf("===========================================\n");
    printf("Customer ID      : %d\n", c.id);
    printf("Customer Name    : %s\n", c.name);
    printf("Phone Number     : %s\n", c.phone);
    printf("-------------------------------------------\n");
    printf("Previous Reading : %.2f kWh\n", c.previous_reading);
    printf("Current Reading  : %.2f kWh\n", c.current_reading);
    printf("Units Consumed   : %.2f units\n", c.units_consumed);
    printf("-------------------------------------------\n");
    printf("Energy Charges   : Rs. %.2f\n", c.energy_charges);
    printf("Fixed Charge     : Rs. %.2f\n", c.fixed_charge);
    printf("-------------------------------------------\n");
    printf("TOTAL AMOUNT DUE : Rs. %.2f\n", c.total_bill);
    printf("===========================================\n");
}