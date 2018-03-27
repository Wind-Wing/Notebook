#include<iostream>
#include<cmath>
#include<string>
#include<cstdio>
using namespace std;
int tree[1005];
int father(int i)
{
    return floor((i+1)/2)-1;
}
int lchild(int i)
{
    return i*2+1;
}
int rchild(int i)
{
    return i*2+2;
}
void swap(int* arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
void sink(int* arr, int i, int len)
{
    int cur = i;
    int l;
    int r;
    while(true)
    {
        l = lchild(cur);
        r = rchild(cur);

        int index = l;
        if(l < len && r < len)index = (arr[l]<arr[r])?l:r;
        if(l >= len)break;
        if(arr[index] < arr[cur])
        {
            swap(arr, cur, index);
            cur = index;
        }
    }
}
void uplift(int* arr, int i)
{
    int cur = i;
    while(true)
    {
        int f = father(cur);
        if(f < 0)break;
        if(arr[cur] < arr[f])
        {
            swap(arr, cur, f);
            cur = f;
        }
        else break;
    }
}
void build(int* arr, int len)
{
    for(int i = pow(2,int(log2(len+1))) - 2; i >= 0; i--)
    {
        sink(arr, i, len);
    }
}
int level(int i)
{
    return int(log(i+1));
}
int query(int *arr, int num, int len)
{
    for(int i = 0; i < len; i++)
    {
        if(arr[i] == num)
        {
            return i;
        }
    }
}
int main(void)
{
    int n,m;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        cin >>tree[i];
        uplift(tree, i);
        //for(int i = 0; i < n; i++)cout<<tree[i]<<" ";
        //cout<<endl;
    }
    //build(tree, n);

    getchar();
    while(m--)
    {
        int num1, num2;
        string q;
        getline(cin, q);
        if(q.find("root") != -1)
        {
            int index = q.find(' ');
            sscanf(q.substr(0,index).c_str(),"%d",&num1);
            if(num1 == tree[0])cout<<"T"<<endl;
            else cout<<"F"<<endl;

        }
        else if(q.find("siblings") != -1)
        {
            int index = q.find(' ');
            sscanf(q.substr(0,index).c_str(),"%d",&num1);
            q = q.substr(index+5,q.size()-index-5);
            index = q.find(' ');
            sscanf(q.substr(0,index).c_str(),"%d",&num2);
            if(father(query(tree, num1, n)) == father(query(tree, num2, n)))cout<<"T"<<endl;
            else cout<<"F"<<endl;
        }
        else if(q.find("parent") != -1)
        {
            int index = q.find(' ');
            sscanf(q.substr(0,index).c_str(),"%d",&num1);
            q = q.substr(index+18,q.size()-index-18);
            sscanf(q.c_str(),"%d",&num2);
            if(tree[father(query(tree, num2, n))] == num1)cout<<"T"<<endl;
            else cout<<"F"<<endl;
        }
        else if(q.find("child") != -1)
        {
            int index = q.find(' ');
            sscanf(q.substr(0,index).c_str(),"%d",&num1);
            q = q.substr(index+15,q.size()-index-15);
            sscanf(q.c_str(),"%d",&num2);
            if(tree[father(query(tree, num1, n))] == num2)cout<<"T"<<endl;
            else cout<<"F"<<endl;
        }
    }
    return 0;
}
