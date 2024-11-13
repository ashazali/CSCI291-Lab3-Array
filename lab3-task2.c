#include <stdio.h>

void process_transactions(int transactions, int length){
int balance = 1000;
int tobeprocessed = 100;
int unprocessed_count = 0;

    for (int i = 0; i < length; i++) {
        if (transactions[i] < 0 && balance + transactions[i] < 0) {
            printf("Transaction %d is invalid. Skipping...\n", transactions[i]);
            tobeprocessed[unprocessed_count++] = transactions[i];
            continue;
        }

        balance += transactions[i];

        if (balance == 0) {
            printf("Balance reached zero. No further transactions will be processed.\n");
            tobeprocessed[unprocessed_count++] = transactions[i];
            break;
        }
    }

    printf("Final balance: %d AED\n", balance);
    printf("Unprocessed transactions:\n");
    for (int i = 0; i < unprocessed_count; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");
}

int main() {
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int length = sizeof(transactions) / sizeof(transactions[0]);
    process_transactions(transactions, length);
    return 0;
}
