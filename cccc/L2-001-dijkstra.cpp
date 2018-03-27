#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define _MAX 0xffffff
using namespace std;

struct node
{
    int dis;
    int num;
    int peo;
    int path_num;
    struct node* pre;
    node()
    {
        pre = NULL;
        dis = _MAX;
        path_num = 0;
    }
};

struct cmp
{
    bool operator()(struct node* a,struct node* b)
    {
        if(a->dis == b->dis)
        {
            return a->peo < b->peo;
        }
        else return a->dis > b->dis;
    }
};

int matrix[501][501];
int people[501];
struct node citys[501];
int mask[501];

priority_queue<struct node*, vector<struct node*>, cmp> que;

int main(void)
{
    for(int i = 0; i < 501; i++)
    {
        for(int j = 0; j < 501; j ++)
        {
            matrix[i][j] = -1;
        }
    }
    //cout<<_MAX<<endl;
    int n, num, start, end;
    cin >> n >> num>> start>>end;
    citys[start].dis = 0;
    citys[start].path_num = 1;
    for(int i = 0; i < n; i++)
    {
        cin >> people[i];
        citys[i].peo = people[i];
        mask[i] = 0;
        citys[i].num = i;
        que.push(&citys[i]);
    }
    //cout<<que.top()->num<<" ";

    while(num --)
    {
    int s,e,l;
    cin >> s >> e >> l;
    matrix[s][e] = l;
    matrix[e][s] = l;
    }

    struct node* cur;
    // dijstra
    while(que.empty() == 0)
    {
        cur = que.top();
        que.pop();
        mask[cur->num] = 1;

        for(int i = 0; i < n; i++)
        {
            if(mask[i] == 0 && matrix[cur->num][i] != -1)
            {
                if(matrix[cur->num][i] + cur->dis < citys[i].dis)
                {
                    citys[i].dis = matrix[cur->num][i] + cur->dis;
                    citys[i].pre = cur;
                    citys[i].peo = cur->peo + people[i];
                    citys[i].path_num = cur->path_num;
                }
                else if(matrix[cur->num][i] + cur->dis == citys[i].dis)
                {
                    citys[i].path_num += cur->path_num;
                    if(cur->peo + people [i] > citys[i].peo)
                    {
                        citys[i].pre = cur;
                        citys[i].peo = cur->peo + people[i];
                    }
                }
            }
        }
    }
    stack<struct node*> sta;
    cur = &citys[end];
    while(true)
    {
        sta.push(cur);
        if(cur->pre == NULL)break;
        cur = cur->pre;
    }

    cout<<citys[end].path_num<<" "<<citys[end].peo<<endl;

    while(sta.empty() == 0)
    {
        cur = sta.top();
        sta.pop();
        cout<<cur->num;
        if(sta.size()!=0)cout<<" ";
    }
    return 0;
}
