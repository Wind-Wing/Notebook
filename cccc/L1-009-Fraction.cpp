#include<iostream>
#include<cmath>
#include<string>
#include<cstdio>
using namespace std;
class CFraction{
    static long long MCF(long long a, long long b)
    {
        long long _max = max(a,b);
        long long _min = min(a,b);
        if(_max%_min == 0)return _min;
        return MCF(_min,_max%_min);
    }

    static long long LCM(long long a, long long b)
    {
        long long c = MCF(a,b);
        return a*b/c;
    }

public:
    long long  denominator ;
    long long numerator;
    long long integer;

    CFraction(){}

    CFraction(long long in, long long nu, long long de)
    {
        integer = in;
        denominator = de;
        numerator = nu;
    }
    CFraction( CFraction& a)
    {
        integer = a.integer;
        denominator = a.denominator;
        numerator = a.numerator;
    }
    static CFraction add(CFraction& a, CFraction& b)
    {
        long long de = a.denominator * b.denominator;
        long long nu = a.denominator*b.numerator + a.numerator*b.denominator;

        long long in = a.integer + b.integer;

        CFraction tmp(in, nu, de);

        return tmp;
    }
    void reduction()
    {
        // negetive symbol reduction : keep denominator is positive
        if( denominator == 0 || numerator == 0)return ;
        if(denominator < 0)
        {
            numerator *=-1;
            denominator *=-1;
        }
        // reduction
        long long symbol = 1;
        if(numerator < 0)
        {
            numerator *= -1;
            symbol = -1;
        }

        integer += symbol*(numerator/denominator);
        numerator %= denominator;

        if(numerator != 0)
        {
            long long mcf = CFraction::MCF(numerator,denominator);
            numerator /= mcf;
            denominator /= mcf;
        }
        numerator *= symbol;
    }

    void display()
    {
        if(integer != 0 || numerator == 0)cout<<integer;
        if(integer != 0 && numerator != 0)cout<<" ";
        if(numerator != 0)cout<<numerator<<"/"<<denominator;
    }
};

int main(void)
{
    long long n;
    cin >> n;

    CFraction a,b;
    string num;
    cin >> num;
    long long d,f;
    int index = num.find('/');
    sscanf(num.substr(0,index).c_str(), "%lld", &f);
    sscanf(num.substr(index+1,num.size()-index-1).c_str(),"%lld", &d);
    a.integer = 0;
    a.denominator = d;
    a.numerator = f;

    while(--n)
    {
        cin >> num;
        long long d,f;
        int index = num.find('/');
        sscanf(num.substr(0,index).c_str(), "%lld", &f);
        sscanf(num.substr(index+1,num.size()-index-1).c_str(),"%lld", &d);
        b.integer = 0;
        b.denominator = d;
        b.numerator = f;

        //a.reduction();
        //b.reduction();
        a = CFraction::add(a,b);
    }
    a.reduction();
    a.display();
    return 0;
}

