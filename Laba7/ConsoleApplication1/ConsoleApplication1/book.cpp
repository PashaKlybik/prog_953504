#include "book.h"
#include "menu.h"
int file_size(FILE* f)
{
    int c = 0;
    while (!feof(f)) {
        if (fgetc(f) == '\n') {
            c++;
        }
    }
    return c;
}

void delete_book_list(ListBook* lst)
{
    Book* temp = lst->head;
    Book* pNext = nullptr;
    while (temp) {
        pNext = temp->next;
        free(temp);
        temp = pNext;
    }
    free(lst);
}
void add_to_book_list(ListBook* lst, Book* p)
{
    Book* temp = (Book*)malloc(sizeof(Book));
    if (!temp) exit(1);
    strcpy(temp->author, p->author);
    strcpy(temp->name, p->name);
    strcpy(temp->requisites, p->requisites);
    temp->books_amount = p->books_amount;
    temp->cost_in = p->cost_in;
    temp->cost_out = p->cost_out;
    temp->next = lst->head;
    temp->prev = nullptr;
    if (lst->head) lst->head->prev = temp;
    lst->head = temp;
    if (!lst->tail) lst->tail = temp;
}

ListBook* read_books(int fl)
{
    FILE* file;
    if (fl == 1) file = fopen("books.txt", "r");
    else file = fopen("order.txt", "r");
    if (!file) exit(2);
    ListBook* temp = (ListBook*)malloc(sizeof(ListBook));
    temp->size = file_size(file) / 6;
    temp->head = temp->tail = nullptr;
    rewind(file);
    int i;
    for (i = 0; i < temp->size; i++) {
        add_to_book_list(temp, load_book_from_file(file));
    }
    fclose(file);
    return temp;
}
Book* load_book_from_file(FILE* file)
{
    Book* temp = (Book*)malloc(sizeof(Book));
    if (!temp) exit(1);
    char buf[6];
    fgets(temp->author, max_str_length, file);
    fgets(temp->name, max_str_length, file);
    fgets(temp->requisites, max_str_length, file);
    fgets(buf, 6, file);
    temp->books_amount = atoi(buf);
    fgets(buf, 6, file);
    temp->cost_in = atoi(buf);
    fgets(buf, 6, file);
    temp->cost_out = atoi(buf);
    return temp;
}
Book* add_book()
{
    printf("Enter book`s data\n");
    Book* temp = (Book*)malloc(sizeof(Book));
    if (!temp) exit(1);

    printf("Enter book`s author: ");
    check_string(temp->author);
    printf("Enter book`s name: ");
    check_string(temp->name);
    printf("Enter book`s requisites: ");
    check_string(temp->requisites);
    printf("Enter book`s amount: ");
    rewind(stdin);
    scanf("%d", &temp->books_amount);
    printf("Enter book`s cost for purchase: ");
    rewind(stdin);
    scanf("%d", &temp->cost_in);
    printf("Enter book`s cost for sale: ");
    rewind(stdin);
    scanf("%d", &temp->cost_out);

    load_book_to_file(temp, 1, 0);
    return temp;
}
void load_book_to_file(Book* book, int fl, int count) // 1 - to books file, 2 - to order file
{
    FILE* file;
    if (fl == 1) file = fopen("books.txt", "a");
    else file = fopen("order.txt", "a");
    if (!file) exit(2);
    char* buf = (char*)malloc(5 * sizeof(char));
    fputs(book->author, file);
    fputs(book->name, file);
    fputs(book->requisites, file);
    if (fl == 1) _itoa(book->books_amount, buf, radix);
    else _itoa(count, buf, radix);
    strcat(buf, "\n");
    fputs(buf, file);
    _itoa(book->cost_in, buf, radix);
    strcat(buf, "\n");
    fputs(buf, file);
    _itoa(book->cost_out, buf, radix);
    strcat(buf, "\n");
    fputs(buf, file);
    free(buf);
    fclose(file);
}
void books_file_rewrite(ListBook* list)
{
    FILE* file = fopen("books.txt", "w");
    if (!file) exit(2);
    Book* temp = list->head;
    while (temp)
    {
        char* buf = (char*)malloc(5 * sizeof(char));
        fputs(temp->author, file);
        fputs(temp->name, file);
        fputs(temp->requisites, file);
        _itoa(temp->books_amount, buf, radix);
        strcat(buf, "\n");
        fputs(buf, file);
        _itoa(temp->cost_in, buf, radix);
        strcat(buf, "\n");
        fputs(buf, file);
        _itoa(temp->cost_out, buf, radix);
        strcat(buf, "\n");
        fputs(buf, file);
        free(buf);
        temp = temp->next;
    }
    fclose(file);
}

void print_books(ListBook* list)
{
    Book* temp = list->head;
    while (temp) {
        printf("\n%s%s", "Author: ", temp->author);
        printf("%s%s", "Name: ", temp->name);
        printf("%s%s", "Requisites: ", temp->requisites);
        printf("%s%d\n", "Amount: ", temp->books_amount);
        printf("%s%d\n", "Price for purchase: ", temp->cost_in);
        printf("%s%d\n", "Price for sale: ", temp->cost_out);
        temp = temp->next;
    }
    printf("\n");
}