#include <iostream>
#include <bits/stdc++.h>
#define LEN 100
using namespace std;

int i;
void E();
void A();
void B();
void C();
bool flag=true;
char str[LEN];

int main()
{
    cout<<"20169009 ÕÔº£É¼"<<endl;
    while(cin>>str)
    {
        i=0;
        E();
        if(flag)
        {
            cout<<"Right\n";
        }
        else
        {
            cout<<"Error\n";
        }
        continue;
    }
    return 0;
}

void E()
{
    if(str[i]=='e')
    {
        i++;
        B();
        if(str[i]=='a')
        {
            i++;
            A();
            flag=true;
        }
    }
    else{i++;flag=false;}
}

void A()
{
    if(str[i]=='a') i++;
    else if(str[i]=='b')
    {
        i++;
        A();
        if(str[i]=='c')
        {
            i++;
            B();
        }
    }
    else{i++;flag=false;}
}

void B()
{
    if(str[i]=='d')
    {
        i++;
        E();
        if(str[i]=='d') i++;
        else{i++;flag=false;}
    }
    else if(str[i]=='a')
    {
        i++;
        C();
    }
    else{i++;flag=false;}
}

void C()
{
    if(str[i]=='e') i++;
    else if(str[i]=='d')
    {
        i++;
        C();
    }
    else{i++;flag=false;}
}

