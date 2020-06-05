#include <stdio.h>
#include <stdlib.h>

struct Stack   //stack
{
    char sym;
  struct  Stack* Next;

}*Head;
struct Stack *Push(char a, struct Stack *head)  //input symbol in stack
{
 struct Stack *t=Head    = (struct Stack*)malloc(sizeof(struct Stack));
  t->sym=a;
  t->Next=head;
 return t;
}
struct Stack *Pop(struct Stack* head,char *out)   //take symbol out of stack
{
  struct  Stack*t= (struct Stack*)malloc(sizeof(struct Stack));
  t=head;
    *out=t->sym;
    head=head->Next;
    free(t) ;
    return head;
}

int main()
{
 Head    = (struct Stack*)malloc(sizeof(struct Stack));
 Head->Next=NULL;
 char str[100];

    gets(str);
    int i=0;
    while(i<strlen(str))//input string
    {
     if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z'))
     Head=Push(str[i],Head);
     i++;
    }
  char*s= (char*)malloc(1*sizeof(char));
  i=0;
  int yes=1;
    while(Head->Next !=NULL) //output string and check
    {

       if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z'))
       {

          Head=Pop(Head,s);
            if(*s!=str[i] && ((*s-str[i])!=32 && (-*s+str[i])!=32))yes=-1;
            i++;
       }
       else i++;
    }
    printf("%d",yes);//show 1 if true and -1 if false
    return 0;
}
