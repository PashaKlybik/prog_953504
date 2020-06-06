#include "menu.h"
void Menu()
{
    printf("1. Make order\n");
    printf("2. Get new books\n");
    printf("3. Show info\n");
    printf("0. Exit\n");
    printf("Choose the number: ");
}
int check_borders(int left_border, int right_border)
{
    int ch;
    while (!scanf("%d", &ch) || ch < left_border || ch > right_border)
    {
        rewind(stdin);
        printf("Wrong input try again: ");
    }
    return ch;
}
void check_string(char* f)
{
    rewind(stdin);
    fgets(f, max_str_length, stdin);
    if (strlen(f) > max_str_length)
    {
        printf("The word is too long! Try again( < 20 characters): ");
        check_string(f);
    }
}
Book* get_book(ListBook* list, char* s)
{
    Book* temp;
    for (temp = list->head; temp != NULL; temp = temp->next)
        if (!strcmp(temp->name, s)) return temp;
    return NULL;
}
void delete_book(ListBook* list, char* s)
{
    Book* temp = NULL;
    temp = get_book(list, s);
    if (temp == NULL) exit(5);
    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    if (!temp->prev) list->head = temp->next;
    if (!temp->next) list->tail = temp->prev;

    free(temp);
    books_file_rewrite(list);
    list->size--;
}
int get_sum(ListBook* list, int fl)
{
    Book* tmp = list->head;
    int sum = 0;
    while (tmp) {

        if (fl == 1) sum += tmp->cost_in * tmp->books_amount;
        else if (fl == 2) sum += tmp->cost_out * tmp->books_amount;
        else sum += tmp->books_amount;
        tmp = tmp->next;
    }
    return sum;
}
void order_history()
{
    ListBook* order = read_books(2);
    Book* temp = order->head;
    printf("Ordered books:\n");
    while (temp) {
        printf("\n%s%s", "Author: ", temp->author);
        printf("%s%s", "Name: ", temp->name);
        printf("%s%d\n", "Amount: ", temp->books_amount);
        printf("%s%d%s\n", "The price of one book: ", temp->cost_out, " BYN");
        printf("%s%d%s\n", "Purchased for: ", temp->cost_out * temp->books_amount, " BYN");
        temp = temp->next;
    }
    int sum = 0, ord_count = 0;
    int benefit = 0, sum_in = 0;
    int purchase_amount = 0;
    temp = order->head;
    while (temp) {
        ord_count++;
        purchase_amount += temp->books_amount;
        sum += temp->cost_out * temp->books_amount;
        sum_in += temp->cost_in * temp->books_amount;
        temp = temp->next;
    }
    benefit = sum - sum_in;
    printf("\n%s%d\n", "Total amount of orders: ", ord_count);
    printf("%s%d\n", "Total amount of sold books: ", purchase_amount);
    printf("%s%d%s\n", "Total storage`s profit from sale is: ", sum, " BYN");
    printf("%s%d%s\n", "Total storage`s benefit from sale is: ", benefit, " BYN");
    printf("\n");
    delete_book_list(order);
}
void make_order(ListBook* lst)
{
    int y_or_n;
    char* string = (char*)malloc(max_str_length * sizeof(char));
    Book* temp;
    do
    {
        print_books(lst);
        printf("Choose book to order: ");
        do {
            printf("Enter book`s name: ");
            rewind(stdin);
            scanf("%s", string);
            strcat(string, "\n");
            temp = get_book(lst, string);
        } while (temp == NULL);
        printf("Enter count of chosen book to order: ");
        int count = check_borders(0, temp->books_amount);
        int price = count * temp->cost_out;
        load_book_to_file(temp, 2, count);
        printf("%s%d%s\n", "Price: ", price, " BYN");
        temp->books_amount -= count;
        if (temp->books_amount == 0) delete_book(lst, string);
        books_file_rewrite(lst);
        printf("Do you want to order more books? (1 - yes, 0 - no)\n");
        rewind(stdin);
        y_or_n = check_borders(0, 1);
    } while (y_or_n != 0);
}
void print_info(ListBook* lst)
{
    printf("\n%s%d\n", "Total number of books in storage: ", get_sum(lst, 3));
    printf("%s%d%s\n", "Total cost from purchase: ", get_sum(lst, 1), " BYN");
    printf("%s%d%s\n", "Total cost for sale: ", get_sum(lst, 2), " BYN");
    print_books(lst);
    order_history();
}