#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <cstdlib>

struct Comment {
	char *header;
	char *context;
	char *filename;
};

//struct SourceCode {
//	char *code;
//};

struct Article {
	char *header;
	char *content;
	char *filename;
//	SourceCode code;
};

struct All {
	Article article;
	Comment comment;
	float rating;

    All *p_right;
	All *p_left;

	All (){
		article.header = (char *) malloc(100);
		article.content = (char *) malloc(100);
		article.filename = (char *) malloc(50);
		comment.header = (char *) malloc(50);
		comment.context = (char *) malloc(100);
        comment.filename = (char *) malloc(100);
		rating = NULL;
		p_right = nullptr;
		p_left = nullptr;
	}
};

All *storage = nullptr;

void push_back(All **tree, float value, char *file, char *title) {

	All *branch;
	branch = new All();

	if(*tree == NULL) {
		branch->rating = value;
		branch->article.filename = file;
		branch->article.header = title;
		branch->p_left = NULL;
		branch->p_right = NULL;
		*tree = branch;
	} else {
		All *root;
		root = &**tree;
		while (root->p_left != NULL && root->p_right != NULL) {
			if (root->rating < value) {
				root = root->p_right;
			} else {
				root = root->p_left;
            }
		}

		if(root->rating < value) {
			branch->rating = value;
			branch->article.filename = file;
			branch->article.header = title;
			root->p_right = branch;
			branch->p_left = NULL;
			branch->p_right = NULL;
		} else {
			branch->rating = value;
			branch->article.filename = file;
			branch->article.header = title;
			root->p_left = branch;
			branch->p_left = NULL;
			branch->p_right = NULL;
        }
    }
}

struct Stack {
	char* str = (char *)malloc(100);
	Stack *p_prev = nullptr;
};

void push_back(Stack **top, char* str) {
	Stack *newStack = new Stack();
	for(int i = 0; str[i] != '\0'; i++) {
        newStack->str[i] = str[i];
    }


	if(*top == nullptr) {
		*top = newStack;
	} else {
		Stack *root = *top;

		while(root->p_prev != nullptr) {
			root = root->p_prev;
		}

		root->p_prev = newStack;
    }
}
void inOrder(All *storage, int key) {  if (storage == nullptr) return;
  inOrder(storage->p_left, key--);
  FILE *file;

  char fileName[100];

  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

  if(key == 0) {
	  SetConsoleTextAttribute(handle, 4);
  }

  int i = 0;

  for(; storage->article.filename[i] != '\n'; i++) {
	  fileName[i] = storage->article.filename[i];
  }

  fileName[i] = '\0';

  file = fopen(fileName, "r");
  char *str = (char*)malloc(100);

  fgets(str, 100, file);
  int j = 0;


  for(; str[j] != '\n' && str[j] != '\0'; j++) {
	  storage->comment.filename[j] = str[j];

  }

  fgets(str, 100, file);

  storage->comment.filename[j] = '\0';

  printf("%s  %f\n%s%s\n\n", storage->article.header, storage->rating, str, "...");

  SetConsoleTextAttribute(handle, 15);

  inOrder(storage->p_right, key--);
}
int Length(char *arr) {
	int i = 0;
	while(arr[i] != '\0') {
		i++;
	}
	return i;
}

void CommentsUpdate(int a, char* filename) {

	system("cls");
	FILE *file;
	file = fopen(filename, "r+");
	char* str = (char *)malloc(100);
	bool last = false;
	int b = a;
	Stack *top = nullptr;

	while(fgets(str, 100, file)) {
		if(str[0] == '\n' && last == true) {
			b--;
			push_back(&top, str);
		} else if(str[0] == '\n') {
			last = true;
			push_back(&top, str);
		} else {
			last = false;
			push_back(&top, str);
		}

		if(b == 1) {
			fgets(str, 100, file);
			push_back(&top, str);
            fgets(str, 100, file);
			printf("%s\n", str);
			scanf("%s", &str[0]);
			push_back(&top, str);
            b--;
        }


	}
     fclose(file);

		file = fopen(filename, "w");

		while(top != nullptr) {
			fprintf(file, "%s", top->str);
            top = top->p_prev;
	}
}

void GetArticle(All* storage, int key) {
    system("cls");
    if (storage == nullptr) return;
  GetArticle(storage->p_left, key--);

  char str[100];
  GetArticle(storage->p_right, key--);

  char *filename = (char *)malloc(50);

  if(key == -1) {
	  FILE *file;
	  char* filE = (char *)malloc(50);
	  int i = 0;

	  for(; storage->article.filename[i] != '\n';i++) {
		  filE[i] = storage->article.filename[i];
	  }

	  filE[i] = '\0';

	  file = fopen(filE, "r");
	  fgets(str, 100, file);

	  for(i = 0; str[i] != '\n'; i++) {
		  filename[i] = str[i];
	  }
      filename[i] = '\0';

	  printf("%s\n%s", storage->article.header, fgets(str, 100, file));

	  while(fgets(str, sizeof(str), file)) {
//		fgets(str, 100, file);
		printf("%s",str);
		int o = getch();
		if(o != 115) {
			return;
		}
	  }

	  fclose(file);

	  FILE *fileC;
	  char arr[100];

	  fileC = fopen(storage->comment.filename, "r");

	  file = fopen("A:\\labs\\C\\sorcecode.txt", "r");

	  printf("\n\nSource code :\n");

	  while(fgets(str, sizeof(str), file)) {
          printf("%s", str);
      }

	  printf("\n\nComments: \n");
	  while(fgets(arr, sizeof(arr), fileC)) {
		  printf("%s", arr);
	  }

	  printf("\n\n%s\n", "If you wan't return print '0'");

	  int a;
	  scanf("%d", &a);

	  if(a == 0) {
		  return;
	  }
	  CommentsUpdate(a, storage->comment.filename);

	  system("pause");
  }
}

void menu(int count) {
	int i = 1;
	int key = 0;

//	if(count == 0) {
//		printf("No Article.");
//		return;
//	}

	while(true) {

	try {
		inOrder(storage, i);
	} catch (...) {
		std::cout << "lol" << i;
	}



		key = getch();



		if (key == 72) {
			i++;
		} else if(key == 80) {
			i--;
		} else if(key == 13) {
			GetArticle(storage, i);
		}

		if(i > count) {
			i = 1;
		} else if(i < 1) {
			i = count;
		}
    system("cls");

//		for(int j = 0; true; j++) {
//
//		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fileData;
	char name[50];
	char *saveName = (char *)malloc(50);
	char *saveTitle = (char *)malloc(100);
	int count = 0;

	fileData = fopen("A:\\labs\\C\\data.txt", "r");

	for (int i = 1; fgets(name, sizeof(name), fileData); i++) {
		if(!fileData) {
			break;
		}

		if(i % 3 == 0) {
//			fgets(name, sizeof(name), fileData);
			push_back(&storage, (float) ((float)name[0] - 48) + (((float)name[2] - 48) / 10), saveName, saveTitle);
			saveName = (char*)malloc(50);
			saveTitle = (char*)malloc(100);
			count++;
			i = 0;
		} else if (i % 2 == 0) {
            for(int j = 0; name[j] != '\0'; j++) {
				saveTitle[j] = name[j];
			}
		} else {
			for(int j = 0; name[j] != '\0'; j++) {
				saveName[j] = name[j];
			}
		}
    }

//	T_Print_Bigger(storage);

	menu(count);

//	while(true) {
//		std::cout << getch() << std::endl;
//	}

	system("pause");
	return 0;
}
