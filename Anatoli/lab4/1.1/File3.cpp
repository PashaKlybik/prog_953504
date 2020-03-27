#include<iostream>
#include<conio.h>
#include<stdio.h>

using namespace std;

void convert11(long long int t, char s[10], int q);

int main()
{
	long long int t;
	char s[10];
	int q;

	cout<<"Enter the number: ";
	cin>>t;
	cout<<"Enter number system: ";
	cin>>q;
	convert11(t, s, q);
	getch();
	return 0;
}
 void convert11(long long int t,char s[10] , int q)
 {
	long long int tmp = 1;
	int n = 0;

	while(tmp <= t) tmp *= q;
	while(tmp > 1) {
		tmp /= q;
		if(t / tmp < 10) {
			s[n] = t / tmp + '0';
			n++;
		}
		else {
			s[n]  = 'A' + t/tmp - 10;
			n++;
		}
		t %= tmp;
	}
    for(int i = 0; i < n; i++)
	{
		cout<<s[i];
	}
	return;
 }
