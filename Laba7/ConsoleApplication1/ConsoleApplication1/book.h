#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

const int max_str_length = 25;
const int radix = 10;

struct Book
{
    char author[max_str_length];
    char name[max_str_length];
    char requisites[max_str_length];
    int books_amount;
    int cost_in;
    int cost_out;
    Book* next, * prev;
};
struct ListBook
{
    Book* head, * tail;
    int size;
};

int file_size(FILE* file);
void delete_book_list(ListBook* lst);
void add_to_book_list(ListBook* lst, Book* book);
Book* load_book_from_file(FILE* file);
void load_book_to_file(Book* book, int flag, int count);
void books_file_rewrite(ListBook* lst);
Book* add_book();
void print_info(ListBook* lst);
void print_books(ListBook* lst);
ListBook* read_books(int flag);