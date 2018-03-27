#include<iostream>
using namespace std;
struct node
{
    int f;
    int depth;
    bool disable;
    int con;
    node()
    {
        depth = 0;
        f = -1;
        disable = false;
    }
};
struct node nodes[501];
int query(struct node* nodes, int i)
{
    int cur = i;
    while(true)
    {
        if(nodes[cur].f != -1 && nodes[nodes[cur].f].disable == false)cur = nodes[cur].f;
        else break;
    }
    return cur;
}
bool check(struct node* nodes, int i, int j)
{
    int a = query(nodes, i);
    int b = query(nodes, j);
    return a == b;
}
void merge(struct node* nodes, int i, int j)
{
    if(check(nodes, i, j))return;
    int a = query(nodes, i);
    int b = query(nodes, j);
    if(nodes[a].depth > nodes[b].depth)
    {
        nodes[b].f = a;
    }
    else
    {
        nodes[a].f = b;
        nodes[b].depth++;
    }
}
int main(void)
{
    int n, num;
    cin >> n>> num;
    while(num--)
    {
        int a,b;
        cin >> a>> b;
        merge(nodes, a, b);
    }

    cin >> num;
    int con = 0;
    for(int i = 0; i < n; i++)
    {
        if(query(nodes, i) == i && nodes[i].disable == false)con++;
    }
    for(int i = 0; i < num; i++)
    {
        int tmp;
        cin >> tmp;
        nodes[tmp].disable = true;
        int _con = 0;
        for(int i = 0; i < n; i++)
        {
            if(query(nodes, i) == i && nodes[i].disable == false)_con++;
        }
        if( i == n -1)cout<<"Game Over."<<endl;
        else if(con == _con)cout<<"City "<<tmp<<" is lost."<<endl;
        else cout<<"Red Alert: City "<<tmp<<" is lost!"<<endl;
        con = _con;
    }
    return 0;
}


