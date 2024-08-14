#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCKS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char symbol[MAX_NAME_LENGTH];
    double price;
    int quantity;
} Stock;

void add_stock(Stock portfolio[], int *num_stocks);
void view_portfolio(Stock portfolio[], int num_stocks);
void calculate_portfolio_value(Stock portfolio[], int num_stocks);

int main() {
    Stock portfolio[MAX_STOCKS];
    int num_stocks = 0;
    int choice;

    while (1) {
        printf("\nStock Portfolio Manager\n");
        printf("------------------------\n");
        printf("1. Add Stock\n");
        printf("2. View Portfolio\n");
        printf("3. Calculate Portfolio Value\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_stock(portfolio, &num_stocks);
                break;
            case 2:
                view_portfolio(portfolio, num_stocks);
                break;
            case 3:
                calculate_portfolio_value(portfolio, num_stocks);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void add_stock(Stock portfolio[], int *num_stocks) {
    if (*num_stocks >= MAX_STOCKS) {
        printf("Portfolio is full. Cannot add more stocks.\n");
        return;
    }

    printf("Enter stock symbol: ");
    scanf("%s", portfolio[*num_stocks].symbol);
    printf("Enter stock price: ");
    scanf("%lf", &portfolio[*num_stocks].price);
    printf("Enter stock quantity: ");
    scanf("%d", &portfolio[*num_stocks].quantity);

    (*num_stocks)++;
    printf("Stock added successfully.\n");
}

void view_portfolio(Stock portfolio[], int num_stocks) {
    if (num_stocks == 0) {
        printf("Portfolio is empty.\n");
        return;
    }

    printf("\nYour Portfolio:\n");
    printf("Symbol\tPrice\tQuantity\n");
    printf("-----------------------------\n");

    for (int i = 0; i < num_stocks; i++) {
        printf("%s\t%.2f\t%d\n", portfolio[i].symbol, portfolio[i].price, portfolio[i].quantity);
    }
}

void calculate_portfolio_value(Stock portfolio[], int num_stocks) {
    if (num_stocks == 0) {
        printf("Portfolio is empty.\n");
        return;
    }

    double total_value = 0.0;
    for (int i = 0; i < num_stocks; i++) {
        total_value += portfolio[i].price * portfolio[i].quantity;
    }

    printf("Total portfolio value: $%.2f\n", total_value);
}
