#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
struct guest
{
    int depth;
    struct guest* group;
    guest()
    {
        depth =1;
        group = NULL;
    }
};

struct guest arr[102];

struct guest* query(struct guest* arr, int a)
{
    struct guest* res;
    res = &arr[a];
    while(res->group)res = res->group;
    return res;
}

bool check(struct guest* arr, int a, int b)
{
    struct guest* root_a = query(arr,a);
    struct guest* root_b = query(arr,b);
    if(root_a == root_b && root_a && root_b)return true;
    else return false;
}

void merge(struct guest* arr, int a, int b)
{
    if(check(arr, a, b))return;
    struct guest* root_a = query(arr,a);
    struct guest* root_b = query(arr,b);

    if(root_a -> depth > root_b->depth)
    {
        root_b -> group = root_a;
        root_a -> depth +=1;
    }
    else
    {
        root_a -> group = root_b;
        root_b -> depth +=1;
    }
}

int main(void)
{
    int num, n, q;
    cin >> num>>n>>q;
    int mat[num+2][num+2];
    for(int i = 0; i<=num;i++)
    {
        for(int j = 0; j <= num; j++)
        {
            mat[i][j] = 0;
        }
    }
    while(n--)
    {
        int a,b,r;
        cin >> a >> b>>r;
        mat[a][b]=r;
        mat[b][a]=r;
        if( r == 1)
        {
            merge(arr, a, b);
        }
    }
    while(q--)
    {
        int a,b;
        cin >> a>> b;
        bool _friend = check(arr, a, b);
        if(_friend)
        {
            if(mat[a][b] != -1)cout<<"No problem"<<endl;
            else cout<<"OK but..."<<endl;
        }
        else
        {
            if(mat[a][b] != -1)cout<<"OK"<<endl;
            else cout<<"No way"<<endl;
        }
    }
    return 0;
}


