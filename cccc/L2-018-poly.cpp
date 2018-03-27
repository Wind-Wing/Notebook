#include<iostream>
#include<cmath>
using namespace std;
struct node
{
    int e;
    int c;
    friend bool operator<(struct node &a, struct node &b)
    {
        return a.e < b.e;
    }
};

// a < b
bool cmp(struct node* a, struct node* b)
{
    return a[0] < b[0];
}



int main(void)
{
    int n,m;
    cin >> n;
    struct node a[n];
    for(int i =0; i< n; i++)
    {
        cin >>a[i].e;
        cin >>a[i].c;
    }
    cin >> m;
    struct node b[m];
    for(int i = 0; i< m; i++)
    {
        cin >> b[i].e;
        cin >> b[i].c;
    }


