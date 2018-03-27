#include<iostream>
#include<queue>
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

struct node* build(int *mid, int *front, int len)
{
    if(len == 0 )return NULL;
    struct node* root;
    root = new struct node();
    root -> v = front[0];
    if(len == 1)return root;
    int index = 0;
    while(index < len)
    {
        if(mid[index] == front[0])break;
        index++;
    }
    root -> l = build(mid,front+1,index);
    root -> r = build(mid+index+1,front+1+index,len-index-1);
    return root;
}

void level(struct node* root, int n)
{
    queue<struct node*>que;
    int counter = 0;
    struct node* cur;
    que.push(root);
    while(counter < n)
    {
        cur = que.front();
        que.pop();
        cout<<cur->v;
        counter++;
        if(counter != n )cout<< " ";
        if(cur->r)que.push(cur->r);
        if(cur->l)que.push(cur->l);
    }
}


int main(void)
{
    int n;
    cin >> n;
    int mid[n];
    int front[n];
    for(int i = 0; i < n; i ++)
    {
        cin >> mid[i];
    }
    for(int i = 0; i < n; i++)
    {
        cin >> front[i];
    }
    struct node* root ;
    root = build(mid, front, n);
    level(root, n);
    return 0;
}

