#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 5
int f = -1, r = -1;
char str[100];
struct
{
    int OrderNum, items;
    char *name, **food;
} Q[size];

void displayOrder(int i)
{
    printf("\n                                Order Number : %d\n", Q[i].OrderNum);
    printf("\n                                Customer Name : %s\n", Q[i].name);
    printf("\n                                Food items:\n");
    for (int j = 0; j < Q[i].items; j++)
        printf("\n                                %s\n", Q[i].food[j]);
}

void display()
{
    if (f == -1)
        printf("\n                       The order queue is currently empty. Please place an order!\n");
    else
    {
        printf("\n                                Current orders in the queue:\n");
        for (int i = f;; i = (i + 1) % size)
        {
            printf("\n                                +--------------------------+\n");
            displayOrder(i);
            if (i == r)
            {
                printf("\n                                +--------------------------+\n");
                return;
            }
        }
    }
}

void place_order()
{
    if ((r + 1) % size == f)
        printf("\nSorry, we're unable to take more orders at the moment. Please wait for the current orders to be processed.\n");
    else
    {
        printf("\n                                Enter Order Details\n");
        if (f == -1)
            f = 0;
        r = (r + 1) % size;
        printf("\n                                Enter Order Number : ");
        scanf("%d", &Q[r].OrderNum);
        printf("\n                                Enter Customer Name : ");
        fflush(stdin);
        scanf("%s", str);

        Q[r].name = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(Q[r].name, str);

        printf("\n                                Enter No. of Food items : ");
        scanf("%d", &Q[r].items);
        printf("\n                                Enter Food Items :\n");

        Q[r].food = (char **)malloc(Q[r].items * sizeof(char *));
        for (int i = 0; i < Q[r].items; i++)
        {
            printf("                                ");
            scanf("%s", str);

            Q[r].food[i] = (char *)malloc((strlen(str) + 1) * sizeof(char));
            strcpy(Q[r].food[i], str);
        }
        printf("\n                                Order No - %d successfully placed!\n", Q[r].OrderNum);
    }
}

void serve_order()
{
    if (f == -1)
        printf("\n                               The queue is empty. No orders to process.\n");
    else
    {
        printf("\n                                Processed Order Details :\n");
        displayOrder(f);

        free(Q[f].name);
        for (int i = 0; i < Q[f].items; i++)
            free(Q[f].food[i]);
        free(Q[f].food);

        if (f == r)
            f = r = -1;
        else
            f = (f + 1) % size;
    }
}

void freeallorders()
{
    if (f == -1)
        return;
    for (int i = f;; i = (i + 1) % size)
    {
        free(Q[i].name);
        for (int j = 0; j < Q[i].items; j++)
            free(Q[i].food[j]);
        free(Q[i].food);
        if (i == r)
            break;
    }
}

int main()
{
    int ch;
    printf("\n                               ***Welcome To Restaurant Menu System***\n");
    while (1)
    {
        printf("\n                                +-----------------------------------+\n");
        printf("                                |           Restaurant Menu         |\n");
        printf("                                +-----------------------------------+\n");
        printf("                                |            1. Place Order         |\n");
        printf("                                |            2. Serve Order         |\n");
        printf("                                |            3. View Orders         |\n");
        printf("                                |            4. Exit                |\n");
        printf("                                +-----------------------------------+\n");
        printf("\n                                          Enter your choice :");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            place_order();
            break;
        case 2:
            serve_order();
            break;
        case 3:
            display();
            break;
        case 4:
            printf("\n                    Thank you for using the restaurant order system. Have a great day!\n\n");
            freeallorders();
            return 0;
        default:
            printf("Invalid Choice! Please try again");
        }
    }
}