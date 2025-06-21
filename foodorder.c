#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int order_id = 1000;
int count = 0;
struct foodorder {
    char name[30];
    char phone[15];
    char item[30];
    int quantity;
    int price;
    int id;
};

struct foodorder orders[100];

int menu(void);
int mainmenu(void);
void placeOrder(void);
void viewOrders(void);
void cancelOrder(void);
int adminAccess();
int getItemPrice(char[]);

int main() {
    int choice;
    while(1) {
        choice = mainmenu();
        switch(choice) {
            case 1:
                placeOrder();
                break;
            case 2:
                viewOrders();
                break;
            case 3:
                cancelOrder();
                break;
            case 4:
                printf("Exiting system. Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

int mainmenu() {
    int ch;
    printf("\n========== Online Food Delivery System ==========\n");
    printf("1. Place a new order\n");
    printf("2. View all orders (Admin only)\n");
    printf("3. Cancel an order\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);
    return ch;
}

int menu() {
    int ch;
    printf("\n================ Menu =================\n");
    printf("1. Pizza       - Rs.250\n");
    printf("2. Burger      - Rs.150\n");
    printf("3. Biryani     - Rs.180\n");
    printf("4. Fried Rice  - Rs.120\n");
    printf("Enter your food choice: ");
    scanf("%d", &ch);
    return ch;
}

int getItemPrice(char item[]) {
    if (strcmp(item, "Pizza") == 0)
        return 250;
    else if (strcmp(item, "Burger") == 0)
        return 150;
    else if (strcmp(item, "Biryani") == 0)
        return 180;
    else if (strcmp(item, "Fried Rice") == 0)
        return 120;
    else
        return 0;
}

void placeOrder() {
    int foodchoice, qty;
    char itemname[30];

    printf("\nEnter your name: ");
    scanf("%s", orders[count].name);
    printf("Enter your phone number: ");
    scanf("%s", orders[count].phone);
    foodchoice = menu();

    switch(foodchoice) {
        case 1: strcpy(itemname, "Pizza"); break;
        case 2: strcpy(itemname, "Burger"); break;
        case 3: strcpy(itemname, "Biryani"); break;
        case 4: strcpy(itemname, "Fried Rice"); break;
        default: printf("Invalid choice.\n"); return;
    }

    printf("Enter quantity: ");
    scanf("%d", &qty);

    strcpy(orders[count].item, itemname);
    orders[count].quantity = qty;
    orders[count].price = getItemPrice(itemname) * qty;
    orders[count].id = order_id;

    printf("\nOrder placed successfully!\n");
    printf("Order ID: %d\n", order_id);
    printf("Customer Name: %s\n", orders[count].name);
    printf("Item: %s | Quantity: %d | Total Price: Rs.%d\n", 
           orders[count].item, orders[count].quantity, orders[count].price);

    order_id++;
    count++;
}

void viewOrders() {
	int i=0;
    if (!adminAccess()) return;

    printf("\n======= All Orders =======\n");
    for (i = 0; i < count; i++) {
        printf("Order ID: %d | Name: %s | Item: %s | Qty: %d | Price: Rs.%d | Phone: %s\n",
            orders[i].id, orders[i].name, orders[i].item, 
            orders[i].quantity, orders[i].price, orders[i].phone);
    }
}

void cancelOrder() {
    int id, found = 0,i=0,j=0;
    printf("Enter Order ID to cancel: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++) {
        if (orders[i].id == id) {
            found = 1;
            printf("Order by %s (ID: %d) for %s is cancelled.\n", 
                   orders[i].name, orders[i].id, orders[i].item);
            for ( j = i; j < count - 1; j++) {
                orders[j] = orders[j+1];
            }
            count--;
            break;
        }
    }

    if (!found) {
        printf("Order ID not found.\n");
    }
}

int adminAccess() {
    char pass[10], correct[] = "akshay";
    printf("Enter admin password: ");
    scanf("%s", pass);
    if (strcmp(pass, correct) == 0)
        return 1;
    else {
        printf("Incorrect password.\n");
        return 0;
    }
}

