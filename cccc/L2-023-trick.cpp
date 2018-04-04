#include<iostream>
#include<set>
using namespace std;

struct eage
{
    int a;
    int b;
};

struct eage arr[250005];

void check(struct eage* arr, int E, int* col)
{
    for(int i = 0; i < E; i ++)
    {
        if(col[arr[i].a-1] == col[arr[i].b-1])
        {
            cout<<"No"<<endl;
            return ;
        }
    }
    cout<<"Yes"<<endl;
}

int main(void)
{
    int col[505];
    int V,E,K;
    cin >> V >> E >>K;
    for(int i = 0; i < E; i ++)
    {
        cin >> arr[i].a;
        cin >> arr[i].b;
    }
    int n;
    cin >> n;
    while(n--)
    {
        set<int> se;
        for(int i = 0; i < V; i ++)
        {
            cin >> col[i];
            se.insert(col[i]);
        }
        if(se.size()==K)
        check(arr, E, col);
        else cout<<"No"<<endl;
    }
    return 0;
}

