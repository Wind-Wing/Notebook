#include<iostream>
using namespace std;

struct node
{
    int f;
    int m;
    char sex;
    bool mark;
    node()
    {
        f = -1;
        m = -1;
        mark = false;
    }
};

struct node nodes[100005];

void mark(struct node* nodes, int i, int depth)
{
    nodes[i].mark = !nodes[i].mark;
    if(--depth > 0)
    {
        if(nodes[i].f != -1)mark(nodes, nodes[i].f, depth);
        if(nodes[i].m != -1)mark(nodes, nodes[i].m, depth);
    }
}

bool check(struct node* nodes, int i, int depth)
{
    bool res1=true;
    bool res2=true;
    if(!depth)return true;
    if(nodes[i].mark == 1)return false;
    depth --;
    if(nodes[i].f != -1)res1 = check(nodes, nodes[i].f, depth);
    if(nodes[i].m != -1)res2 = check(nodes, nodes[i].m, depth);
    return res1 && res2;
}

int main(void)
{
    int n;
    cin >> n;
    while(n--)
    {
        int id;
        char sex;
        int f;
        int m;
        cin >> id >> sex >> f >> m;
        nodes[id].sex = sex;
        nodes[id].f = f;
        nodes[id].m = m;

        nodes[f].sex = 'M';
        nodes[m].sex = 'F';
    }
    cin >> n;
    while(n--)
    {
        int f;
        int m;
        cin >> f>>m;
        if(nodes[f].sex == nodes[m].sex)cout<<"Never Mind"<<endl;
        else
        {
            mark(nodes, f, 5);
            bool res = check(nodes, m, 5);
            mark(nodes, f, 5);
            if(!res)cout<<"No"<<endl;
            else cout<<"Yes"<<endl;
        }
    }
    return 0;
}
