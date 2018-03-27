#include<iostream>
#include<cmath>
#include<set>
#include<algorithm>
using namespace std;

int main(void)
{
    set<int> factor;
    int n;
    cin >> n;

    // find factors
    int range = int(sqrt(n))+1; // remember +1 because int()
    factor.insert(n);
    for(int i = 2; i <= range; i++)
    {
        if( n % i == 0)
        {
            factor.insert(i);
            if( n/i != 1)factor.insert(n/i);    // attention
        }
    }
    //DP to find max continue sub seq
    long long len = factor.size();
    long long DP[len];
    long long mul[len];
    int fact[len];

    set<int>::iterator iter = factor.begin();
    for(long long i = 0; i<len; i++)
    {
        fact[i] = *iter;
        mul[i] = *iter;
        DP[i] = 1;
        iter++;
    }
    long long start = 0;
    long long _len =0;
    long long max = 0;
    // DP
    for(long long i = 1; i< len;i++)
    {
        for(long long j = 0; j < len-i; j++)
        {
            if(DP[j] != i)continue;
            mul[j] = mul[j]*fact[j+i];
            if(n % mul[j] == 0 && mul[j] <= n && fact[j+i] == fact[j+i-1]+1)
            {
                DP[j] = DP[j] + 1;
                if(DP[j] > max)
                {
                    max = DP[j];
                    start = j;
                    _len = i;
                }
            }
        }
    }
    cout<<_len+1<<endl;
    for(long long i = start; i <= start+_len;i++)
    {
        cout<<fact[i];
        if(i != start+_len)cout<<"*";
    }
    return 0;
}
