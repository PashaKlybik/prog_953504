#pragma once
#include "book.h"

void make_order(ListBook* lst);
int get_sum(ListBook* lst, int fl);
Book* get_book(ListBook* lst, char* str);
int check_borders(int l_b, int r_b);
void check_string(char* str);
void order_history();
void Menu();
void print_info(ListBook* lst);