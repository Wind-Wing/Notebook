#include<iostream>
#include<queue>
using namespace std;

struct node
{
    int num;
    node* l;
    node* r;
};

node* tree(int *behind, int *mid, int len)
{
    node* root = new node();
    root -> num = behind[len - 1];
    root -> l = NULL;
    root -> r = NULL;
    int next_len = 0;
    while(true)
    {
        if(mid[next_len]==behind[len - 1])break;
        next_len++;
    }
    if(next_len != 0)
    {
        root -> l = tree(behind, mid, next_len);
    }
    if(next_len != len-1)
    {
        root -> r = tree(behind+next_len, mid+next_len+1, len-next_len-1);
    }
    return root;
}

int main(void)
{
    int N;
    int behind[1000];
    int mid[1000];
    cin >> N;
    for(int i = 0; i < N; i ++)
    {
        cin >> behind[i];
    }
    for(int i = 0; i < N; i ++)
    {
        cin >> mid[i];
    }
    node * _tree = tree(behind, mid, N);
    queue<node *>level;
    level.push(_tree);
    int counter = 0;
    while(! level.empty())
    {
        node* current = level.front();
        level.pop();
        if(current == NULL)continue;
        level.push(current->l);
        level.push(current->r);
        cout<<current->num;
        counter++;
        if(counter != N){cout<<" ";}
    }
    return 0;
}
