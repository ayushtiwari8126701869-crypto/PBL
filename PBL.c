#include <stdio.h>
#include <string.h>

// Structure to store bill data
struct MenuItem {
    char name[30];
    float price;
    int quantity;
};

// Function to save the bill to a text file
void saveBillToFile(struct MenuItem items[], int count, int customerID, float subtotal, float gst, float grandTotal) {
    FILE *fptr;
    fptr = fopen("restaurant_record.txt", "a"); // "a" opens file in append mode

    if (fptr == NULL) {
        printf("Error opening file!");
        return;
    }

    fprintf(fptr, "\n--- Bill for Customer #%d ---\n", customerID);
    fprintf(fptr, "Item            Qty      Price      Total\n");
    for (int i = 0; i < count; i++) {
        fprintf(fptr, "%-15s %-8d %-10.2f %-10.2f\n", items[i].name, items[i].quantity, items[i].price, items[i].price * items[i].quantity);
    }
    fprintf(fptr, "Subtotal: %.2f | GST: %.2f | Grand Total: %.2f\n", subtotal, gst, grandTotal);
    fprintf(fptr, "--------------------------------------------\n");

    fclose(fptr);
    printf("\n[Record saved to restaurant_record.txt]\n");
}

void generateBill(struct MenuItem items[], int count, int customerID, float gstRate) {
    float subtotal = 0;
    printf("\n=========================================");
    printf("\n          Three Coders Restaurant        ");
    printf("\n=========================================");
    printf("\nCustomer No: %d", customerID);
    printf("\n-----------------------------------------");
    printf("\nItem            Qty      Price      Total");
    printf("\n-----------------------------------------");

    for (int i = 0; i < count; i++) {
        float itemTotal = items[i].price * items[i].quantity;
        printf("\n%-15s %-8d %-10.2f %-10.2f", items[i].name, items[i].quantity, items[i].price, itemTotal);
        subtotal += itemTotal;
    }

    float gstAmount = (subtotal * gstRate) / 100;
    float finalTotal = subtotal + gstAmount;

    printf("\n-----------------------------------------");
    printf("\nSubtotal:                          %.2f", subtotal);
    printf("\nGST (%.1f%%):                        %.2f", gstRate, gstAmount);
    printf("\nGrand Total:                       %.2f", finalTotal);
    printf("\n=========================================\n");

    // Calling the function to save this data permanently
    saveBillToFile(items, count, customerID, subtotal, gstAmount, finalTotal);
}

int main() {
    int choice, qty, itemCount = 0;
    int totalOrders = 0;
    float gstPercent = 18.0;
    struct MenuItem order[10];

    while (1) {
        printf("\n #RESTAURANT MANAGEMENT SYSTEM#");
        printf("\n1. New Order");
        printf("\n2. View Total Orders Today");
        printf("\n3. Exit");
        printf("\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 3) break;

        switch (choice) {
            case 1:
                itemCount = 0;
                totalOrders++;
                int ordering = 1;

                while (ordering) {
                    printf("\n--- Menu ---");
                    printf("\n1. Burger   - 120\n2. Pizza    - 250\n3. Pasta    - 180\n4. Coffee   - 60\n5. Generate Bill");
                    printf("\nSelect item: ");
                    int itemChoice;
                    scanf("%d", &itemChoice);

                    if (itemChoice == 5) {
                        ordering = 0;
                        if(itemCount > 0)
                            generateBill(order, itemCount, totalOrders, gstPercent);
                        else
                            printf("No items ordered!\n");
                    } else {
                        printf("Enter Quantity: ");
                        scanf("%d", &qty);

                        switch (itemChoice) {
                            case 1: strcpy(order[itemCount].name, "Burger"); order[itemCount].price = 120; break;
                            case 2: strcpy(order[itemCount].name, "Pizza");  order[itemCount].price = 250; break;
                            case 3: strcpy(order[itemCount].name, "Pasta");  order[itemCount].price = 180; break;
                            case 4: strcpy(order[itemCount].name, "Coffee"); order[itemCount].price = 60; break;
                            default: printf("Invalid Item!\n"); continue;
                        }
                        order[itemCount].quantity = qty;
                        itemCount++;
                    }
                }
                break;

            case 2:
                printf("\n>>> Total customers served this session: %d\n", totalOrders);
                break;

            default:
                printf("Invalid selection!\n");
        }
    }

    return 0;
}
