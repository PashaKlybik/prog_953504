//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

struct List
{
  int shet;
  int cat;
  UnicodeString FIO;
  int vklad;
  UnicodeString Opearations;
  struct List *next;
  struct List *prev;
};





class Listt
{

public:
List *head;
List *tail;
Listt()
 {
 head=NULL;
 tail=NULL;
 }

 void Add(List *w)   //добавить клиента
 {
  List *per = (List*)calloc(1, sizeof(List));
   per->next=NULL;
   per->shet=w->shet;
   per->cat=w->cat;
   per->FIO=w->FIO;
   per->vklad=w->vklad;
   if(head!=NULL)
   {
   per->prev=tail;
   tail->next=per;
   tail=per;
   }
   else
   {
   per->prev=NULL;
   head=tail=per;
   }
   delete per;
   }

   void Show(TMemo *Memo1)      //вывод всех клиентов
   {
   List *per=head;
   while(per!=NULL)
   {
   Memo1->Lines->Add(per->FIO);
   per=per->next;
   }
   }

   void ShowClients(UnicodeString FIO, TMemo *Memo1)      //вывод всей информации о клиенте
   {
   List *per=head;
   while(per!=NULL)
   {
   if(per->FIO==FIO)
   {
   Memo1->Lines->Add(per->FIO);
   Memo1->Lines->Add(per->vklad);
   Memo1->Lines->Add(per->shet);
   Memo1->Lines->Add(per->cat);
   }
   per=per->next;
   }
   }

   void ShowALL(UnicodeString FIO, TMemo *Memo1)      //вывод всей информации
   {
   List *per=head;
   while(per!=NULL)
   {
   Memo1->Lines->Add(per->FIO);
   Memo1->Lines->Add(per->vklad);
   Memo1->Lines->Add(per->shet);
   Memo1->Lines->Add(per->cat);
   per=per->next;
   }
   }


   void ShowVklad(TMemo *Memo1)      //сумма вкладов
   {List *per=head;
   int m=0;
   while(per!=NULL)
   {
   m=m+per->vklad;
   per=per->next;
   }
   Memo1->Lines->Add(m);
   }

   void ShowCvitation(UnicodeString FIO,TMemo *Memo1)      //квитанция
   {
   List *per=head;
   while(per!=NULL)
   {
   if(per->FIO==FIO)
   {
   Memo1->Lines->Add(per->FIO);
   Memo1->Lines->Add("Квитанция");
   per->Opearations=per->Opearations+"Kvitations, ";
   }
   per=per->next;
   }
   }

   void Opera(UnicodeString FIO,TMemo *Memo1)      //операции
   {
   List *per=head;
   while(per!=NULL)
   {
   if(per->FIO==FIO)
   {
   Memo1->Lines->Add(per->Opearations);
   }
   per=per->next;
   }
   }

   void AddandLessMoney(UnicodeString FIO,int m,TMemo *Memo1)      //приём и выдача денег
   {
   List *per=head;
   while(per!=NULL)
   {
   if(per->FIO==FIO)
   {
   if(per->vklad+m>=0)
   per->vklad=per->vklad+m;
   Memo1->Lines->Add("Измемение счёта");
   per->Opearations=per->Opearations+"Change Money, ";
   }
   per=per->next;
   }
   }


	void Procent(UnicodeString FIO,int l,TMemo *Memo1)      //Процент
   {List *per=head;
   int m;
   while(per!=NULL)
   {
   if(per->FIO==FIO)
   m=l*per->cat;
	per=per->next;
   }
   Memo1->Lines->Add(m) ;
   }

	void Save(TOpenDialog *SaveDialog1,TMemo *Memo1)    //сохранение
	{
	Memo1->Clear();
	SaveDialog1->Execute();
	TStringList *SL=new TStringList;
	ShowALL("gd",Memo1);
	Memo1->Lines->SaveToFile(SaveDialog1->FileName)  ;

	}

	void Sort(TMemo *Memo1)    //сортировка
	{
	List *per=head;
	int m=0      ;
	while(per!=NULL)
	{
	m=m+1;
	per=per->next;
	}
	per=head;
	List *CL=new List[m];
	int i=0;
	while(per!=NULL)
	{
	CL[i]=*per;
	i=i+1;
	per=per->next;
	}

	for(int t=0; t<i;t++)
	for(int j=0; j<i-1;j++)
	{

	if(CL[j].vklad<CL[j+1].vklad)
	{
	List pr=CL[j];
	CL[j]=CL[j+1];
	CL[j+1]=pr;
	}
	}
	head=NULL;
	//Memo1->Clear()     ;
	//ShowALL("saf",Memo1);
	for(int t=0; t<i;t++)
	{
	Add(&CL[t]);
	}
	//Memo1->Clear();
	//ShowALL("saf",Memo1);
	}



};

List *Client=new List();
Listt Clients ;
UnicodeString FIO1,FIO2;

//--------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)     //информация из файла
{
int i=0;
OpenDialog1->Execute();
	TFileStream *tfile=new TFileStream(OpenDialog1->FileName,fmOpenRead);
	TStringList *SL=new TStringList;
    SL->LoadFromStream(tfile);
    int leng_proj=SL->Count;
	leng_proj=leng_proj/4;
	UnicodeString str;
	for (int t=0; t<leng_proj;t++)            {
	Client->FIO=SL->Strings[i];     i++;
	ComboBox1->Items->Add(Client->FIO);
	ComboBox2->Items->Add(Client->FIO);
	Client->cat=StrToInt(SL->Strings[i]);             i++;
	Client->shet=StrToInt(SL->Strings[i]);             i++;
	Client->vklad=StrToInt(SL->Strings[i]);             i++;
	Clients.Add(Client);
	}
	Clients.Show(Memo1);
delete tfile;
delete SL;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)  //Combobox1
{
Memo1->Clear();
FIO1=ComboBox1->Items->Strings[ComboBox1->ItemIndex];
Memo1->Lines->Add(FIO1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox2Change(TObject *Sender)     //Combobox1
{
Memo1->Clear();
FIO2=ComboBox2->Items->Strings[ComboBox2->ItemIndex];
Memo1->Lines->Add(FIO2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
Memo1->Clear();
int m=StrToInt(Edit1->Text);
Clients.AddandLessMoney(FIO1,m,Memo1);
Clients.ShowClients(FIO1,Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
Memo1->Clear();
Clients.ShowCvitation(FIO1, Memo1)   ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
 Memo1->Clear();
Clients.Show(Memo1)   ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
  Memo1->Clear();
Clients.ShowClients(FIO1,Memo1)   ;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button10Click(TObject *Sender)
{
Memo1->Clear();
Clients.ShowVklad(Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
 Memo1->Clear();

Clients.ShowALL(FIO1,Memo1);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Click(TObject *Sender)
{
Memo1->Clear();
int m=StrToInt(Edit2->Text);
Clients.Procent(FIO1,m,Memo1);
Clients.ShowClients(FIO1,Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
Memo1->Clear();
int m=StrToInt(Edit1->Text);
Clients.AddandLessMoney(FIO1,-m,Memo1);
Clients.AddandLessMoney(FIO2,m,Memo1);
Clients.ShowClients(FIO1,Memo1);
Clients.ShowClients(FIO2,Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
Memo1->Clear();
Clients.Opera(FIO1,Memo1)    ;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button11Click(TObject *Sender)
{
Clients.Save(SaveDialog1,Memo1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
Memo1->Clear();
Clients.Sort(Memo2);
Memo1->Clear();
Clients.ShowALL(FIO1,Memo1);
}
//---------------------------------------------------------------------------

