#include <stdio.h>
#include <iostream>
 
struct Steck {
	int count = NULL;
	Steck *p_next;
	Steck *p_prev;
};
 
void push_back (Steck **top, int count) {
	Steck *newSteck;
	Steck *back;
	back = &(**top);
	newSteck = new Steck();
	newSteck->count = count;
 
	if (*top == NULL) {
		newSteck->p_next = NULL;
		newSteck->p_prev = NULL;
		*top = newSteck;
	} else {
		back->p_prev = newSteck;
		newSteck->p_next = *top;
		newSteck->p_prev = NULL;
		*top = newSteck;
	}
}
 
void S_print(Steck *top) {
	Steck *q = top;
//	while(q->p_next != nullptr) {
//		q = q->p_next;
//    }
 
	while (q) {
		printf("%d ", q->count);
		q = q->p_next;
	}
}
 
void Parse(Steck **top, int num) {
	while(true) {
		if(num / 8 != 0) {
			int val = num % 8;
			num = (num - val) / 8;
			push_back(&*top, val);
		} else {
			push_back(&*top, num);
			break;
        }
    }
}
 
//void S_Change(Steck **top, Steck **top2) {
//	Steck *steck;
//	steck = &**top;
//	Steck *cpySteck;
//	cpySteck = &**top2;
//	bool mode = false;
//
//	do {
//		if (cpySteck->p_next == NULL) {
//			mode = true;
//		}
//
//		if (!mode) {
//			cpySteck = cpySteck->p_next;
//		} else {
//			Steck *newSteck;
//			newSteck = new Steck();
//
//			newSteck->count = cpySteck->count;
//			steck->p_prev = newSteck;
//			newSteck->p_next = *top;
//			newSteck->p_prev = NULL;
//			*top = newSteck;
//			steck = newSteck;
//
//			cpySteck = cpySteck->p_prev;
//		}
//
//	}while(cpySteck);
//}
 
 
int main () {
 
	Steck *top = NULL;
	int num;
	scanf("%d", &num);
 
	Parse(&top, num);
//	push_back(&top, 1);
//	push_back(&top, 2);
//	push_back(&top, 3);
//	push_back(&top, 4);
//	push_back(&top, 5);
//
//	Steck *top2 = NULL;
//	push_back(&top2, 6);
//	push_back(&top2, 7);
//	push_back(&top2, 8);
//	push_back(&top2, 9);
 
	S_print(top);
	printf("\n");
//	S_Change(&top, &top2);
//	S_print(top);
	system("pause");
	return 0;
}