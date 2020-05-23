#pragma once

#include "Library.h"


void InitFromFile(CathLibrary* cathLibrary);

void ShowReaderInfo(Reader* reader);

void ShowReaders(ListReader* listReader);

void ShowBookInfo(NodeBook* node);

void ShowBooks(ListBook* bookList);

void ShowReaderBooks(ListDeal* dealList);

void BorrowBook(char* surname, int group, char* title, CathLibrary* lib, DealDate* dealDate);

void ReturnBook(char* surname, int group, char* title, CathLibrary* lib);

bool ReaderExists(char* surname, int group, ListReader* listReader);

bool BookExists(char* title, ListBook* listBook);

void LibReport(CathLibrary* lib);

void DeleteLibrary(CathLibrary* lib);