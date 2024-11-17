#include <stdio.h> // Standard Input/Output header for printf, scanf, etc.

// Define constants for initial balance and max number of transactions
#define INITIAL_BALANCE 1000
#define MAX_TRANSACTIONS 50

// Function prototype for processing transactions
void processTransactions(int transactions[], int numTransactions);

int main() {
    // Example transactions array: deposits are positive, withdrawals are negative
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    
    // Calculate the number of transactions
    int numTransactions = sizeof(transactions) / sizeof(transactions[0]);

    // Call function to process transactions
    processTransactions(transactions, numTransactions);

    return 0;  // Exit the program
}

// Function to process an array of transactions and update balance
void processTransactions(int transactions[], int numTransactions) {
    int balance = INITIAL_BALANCE;  // Set the initial balance
    int tobeprocessed[MAX_TRANSACTIONS];  // Array to store transactions that couldn't be processed
    int unprocessedCount = 0;  // Counter for the number of unprocessed transactions

    // Print the initial balance
    printf("Initial balance: %d AED\n", balance);

    // Loop through each transaction in the array
    for (int i = 0; i < numTransactions; i++) {
        int transaction = transactions[i];  // Current transaction to process

        // Print the transaction being processed
        printf("Processing transaction: %d AED\n", transaction);

        // Check if the transaction is a withdrawal (negative value)
        if (transaction < 0) {
            // If the withdrawal amount exceeds the current balance, it's invalid
            if (-transaction > balance) {
                // Print error message and store the invalid transaction
                printf("Transaction %d AED is invalid (insufficient balance).\n", transaction);
                tobeprocessed[unprocessedCount++] = transaction;  // Store unprocessed transaction
                continue;  // Skip processing this transaction
            }
        }

        // Process the valid transaction (deposit or withdrawal)
        balance += transaction;

        // Print the updated balance after processing the transaction
        printf("Transaction %d AED processed. New balance: %d AED\n", transaction, balance);

        // Check if the balance has reached 0 or gone negative
        if (balance <= 0) {
            // If balance is 0 or negative, stop processing further transactions
            printf("Balance reached 0. No further transactions will be processed.\n");
            
            // Store any remaining transactions that were not processed
            for (int j = i + 1; j < numTransactions; j++) {
                tobeprocessed[unprocessedCount++] = transactions[j];
            }
            break;  // Exit the loop since no further transactions can be processed
        }
    }

    // Print the final balance after all possible transactions
    printf("Final balance: %d AED\n", balance);

    // Print the list of unprocessed transactions (if any)
    printf("Unprocessed transactions:\n");
    for (int i = 0; i < unprocessedCount; i++) {
        printf("%d AED\n", tobeprocessed[i]);  // Print each unprocessed transaction
    }

    // Thank the user for using the banking system
    printf("Thank you for using our banking system! Have a great day!\n");
}
