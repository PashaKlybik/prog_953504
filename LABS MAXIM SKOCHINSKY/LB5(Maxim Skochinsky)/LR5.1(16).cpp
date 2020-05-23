#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <iostream>
#include <conio.h>


using namespace std;
 

char strings[10][20] = { "maximum","good","main","simple","complex", "program", "car", "integral", "stack", "picture"};
// слова, которые будем реверсировать и добавлять в стек
char wordsFromLists[12][20];//всего в стеке будет 12 слов





char strBuf[20] = "";
int Count = 0;

void reverse_print(char  *sPtr )// рекурсивная функция, которая реализует поворот строки
{
   
    
    if (*sPtr != '\0') {
        reverse_print(sPtr + 1);  
        strBuf[Count] = *sPtr;
        Count++;
    }
   
}





typedef struct _Node {// Структура "Узел" для двусвязного списка 
    char str[20] = "";// пустая строка
    struct _Node* next;// указатель на следующий элемент
    struct _Node* prev;// указатель на предыдущий элемент
}_Node;



typedef struct _DblLinkedList { // структура "Двусвязный список"
    int size;// переменная, которая хранит кол-во узлов(размер списка)
    _Node* head;// Указатель на первый элемент списка
    _Node* tail;// указатель на предыдущий элемент списка
}DblLinkedList;


DblLinkedList* createList() { // создание двусвзяного списка
    DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList)); // выделение памяти
    tmp->size = 0; // присваиваем полям дефолтные значения
    tmp->head = NULL;
    tmp->tail = NULL;
    return tmp;// возврат указателя на список
}


void pushList(DblLinkedList *list) {// добавление элемента в список

    _Node* tmp = (_Node*)malloc(sizeof(_Node));// выделяем память под новый узел
    if (tmp == NULL)  exit(1);// если память не выделилась - выйти из программы
    strcpy(tmp->str, ""); // очищаем строку, хранящуюся в узле
    strcpy(tmp->str, strings[rand() % 10]);// копируем в строку любую строку из массива strings
    tmp->next = list->head; // теперь указатель на след элемент будет голова списка
    tmp->prev = NULL;

    if (list->head) list->head->prev = tmp; // если голова существовала то теперь её ук-ль prev будет указывать на только что созданный элемент

    if (list->tail == NULL) list->tail = tmp; // если "хвоста" не существовало до создания узла, то присваиваем указатель на tail - tmp

    list->head = tmp;// теперь "голова" - новый созданный элемент
    list->size++;// увеличиваем размер
 }



int counterOfWords = 0; // переменная хранит номер строки из массива strings
void printDblLinkedList(DblLinkedList* list) {// печатаем список
     printf("\n");
    _Node* tmp = list->head; //первый элемент списка
    int counter = 1;
     while (tmp) { //пока tmp != NULL, т.е. указатель существует, выписываем 
        cout << counter << ") "; // пишем номер элемента в списке
        reverse_print(tmp->str);// перворачиваем строку
        int size = strlen(tmp->str); // размер строки
        for (int i = size; i < 20; i++) {
            strBuf[i] = '\0'; 
        }//очищаем инверсированную строку от возможного мусора.
        cout << strBuf; // выписываем строку
        strcpy(wordsFromLists[counterOfWords], strBuf);// копируем её в наш массив слов по сounterOfWords номеру
        strcpy(strBuf, "");// очищаем буферную строку
        counterOfWords++;// увеличиваем номер строки
        printf("\n");
        Count = 0;
        tmp = tmp->next;// смещаем указатель на следующий элемент
        counter++;
     }
}




void sortWords(char str[12][20]) {// "пузырьковая" сортировка строк по алфавиту
    char tmp[20] = "";
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 11 - i; j++) {
            if (str[j][0] > str[j + 1][0]) {
                strcpy(tmp, str[j]);
                strcpy(str[j], str[j + 1]);
                strcpy(str[j + 1], tmp);
             }
         }
    }
}




typedef struct Node { // 
    DblLinkedList *list;// указатель на двунаправленный список 
    char str[20] = ""; // в стеке
    struct Node* next;
};

typedef struct Stack {//структура "стек"
    Node* head = NULL; // первоначально ничего нет
}Stack;



Stack* init_stack(DblLinkedList * LinkedList) {// инициализация стека
     Stack *list = (Stack*)malloc( sizeof(Stack) );
     Node* node = (Node*)malloc(sizeof(Node));
     node->list = LinkedList;
     node->next = NULL;
     list->head = node;
     return list;
 }



void push(Stack* list, char val[]) { // добавление элемента в стек
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->next = list->head;
    strcpy(tmp->str,val);
    list->head = tmp; 
}


void push(Stack* list, DblLinkedList* LinkedList) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->list = LinkedList;
    tmp->next = list->head;


    list->head = tmp;
}




void print(Stack* list) {// вывод содержимого стека
    Node* tail_current = list->head;
    
    while (tail_current != NULL) {
        printDblLinkedList(tail_current->list);
        tail_current = tail_current->next;
    }
}


void printWords(Node * list) {// вывод слов, хранящихся в самом стеке, а не в списках
    Node* tail_current = list;

    if (tail_current->next != NULL) {
        printWords(list->next);
        cout << endl;
        cout << Count + 1 << ")  " << list->str;
        Count++;
    }
    
}







int main()
{

    
    
        DblLinkedList **lists = (DblLinkedList**)malloc(sizeof(DblLinkedList*) * 4);
        
        for (int i = 0; i < 4; i++) {
            lists[i] = createList();
            pushList(lists[i]);
            pushList(lists[i]);
            pushList(lists[i]);
        }


       


        Stack *stack = init_stack(lists[0]);
        Stack* stack2 = init_stack(lists[0]);


            for (int i = 1; i < 4; i++) {
                push(stack, lists[i]);
            }

            cout << "Stack with 4 lists(3 words in each)";
        print(stack);
        cout << "\nAll the words :  " << endl;
        for (int i = 0; i < 12; i++) {
            cout << endl;
            cout << i + 1 << ") ";
            cout << wordsFromLists[i];
        
        }

        sortWords(wordsFromLists);
        cout << endl;
        for (int i = 0; i < 12; i++) {
            push(stack2, wordsFromLists[i]);
        }


        cout << "\nSorting..." << endl;
        printWords(stack2->head);
        

        _getch();

    return 0;
}