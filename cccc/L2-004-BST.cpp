#include<iostream>
#include<vector>
using namespace std;
struct node
{
    int v;
    struct node* l;
    struct node* r;
    node()
    {
        l = NULL;
        r = NULL;
    }
};

struct node* build(int* arr, int len, bool mir)
{
    struct node *res;
    res = new struct node();
    if(len == 0)return NULL;
    if(len == 1)
    {
        res->v = arr[0];
        return res;
    }
    int index = 1;
    while((arr[0] > arr[index]) == !mir && index < len)index++;
    res->l = build(arr+1, index - 1, mir);
    res->r = build(arr+index, len - index, mir);
    res->v = arr[0];
    return res;
}

void mid(struct node* root, vector<int> &a)
{
    if(root == NULL) return ;
    mid(root->l, a);
    a.push_back(root->v);
    mid(root->r, a);
}

bool check(struct node* root,int len, bool mir)
{
    int arr[len];
    int index = 0;
    vector<int> a;
    mid(root, a);
    vector<int>::iterator iter;
    vector<int>::iterator _iter;
    _iter = a.begin();
    iter = a.begin();
    iter ++;
    for(; iter != a.end(); iter++)
    {
        if( mir && *_iter < *iter)return false;
        if( !mir && *_iter > *iter)return false;
        _iter++;
    }
    return true;
}

void behind(struct node* root, int& counter, int n)
{
    if(root == NULL)return;
    behind(root->l,counter,n);
    behind(root->r,counter,n);
    cout<<root->v;
    counter++;
    if(counter<n)cout<<" ";
}

int main(void)
{
    int n ;
    struct node* root;
    cin >> n;
    int arr[n];
    for(int i = 0 ; i < n; i++)
    {
        cin >> arr[i];
    }
    if(n ==1)cout<<"YES"<<endl<<arr[0];
    else
    {
        root = build(arr, n, arr[0]<=arr[1]);
        bool res = check(root, n, arr[0]<=arr[1]);
        if(res == false)cout<<"NO";
        else
        {
            cout<<"YES"<<endl;
            int counter = 0;
            behind(root, counter, n);
        }
    }
    return 0;
}
