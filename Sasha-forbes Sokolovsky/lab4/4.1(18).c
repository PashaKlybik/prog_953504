#include<stdio.h>
#include<math.h>
int STOI(n,str)
{
    int i,a=0;
    for(i=0;i<20;i++)
    {
        if(str%10==1)
        {
            a=pow(2,i);
            n+=a;
        }
        str=str/10;
        return STOI(n,str);
    }
    return n;
}
int main()
{
    int n,str;
    printf("Vvedite str:");
    scanf("%d",&str);
 
    printf("%d",STOI(n,str));
}