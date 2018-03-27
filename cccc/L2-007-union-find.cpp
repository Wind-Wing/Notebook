#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;

struct person
{
    int h;
    double a;
    int depth;
    bool valid;
    int peo;
    int min;
    struct person* group;
    person()
    {
        group = NULL;
        depth = 0;
        valid = false;
        peo = 1;
        min = 10000;
        h = 0;
        a = 0;
    }
};
struct person arr[10005];

bool cmp(struct person* a,struct person* b)
{
    double _a = a->a / double(a->peo);
    double _b = b->a / double(b->peo);
    if(_a == _b)return a->min < b->min;
    return _a > _b;
}

struct person* query(struct person* arr, int a)
{
    struct person* cur;
    cur = &arr[a];
    while(cur->group)cur = cur->group;
    return cur;
}

bool check(struct person* arr, int a, int b)
{
    struct person* _a = query(arr, a);
    struct person* _b = query(arr,b);
    if(_a == _b && _a)return true;
    else return false;
}

void unit(struct person* arr, int a, int b)
{
    if(check(arr, a, b))return;
    struct person* _a;
    _a = query(arr, a);
    struct person* _b;
    _b = query(arr, b);
    if( _a -> depth > _b -> depth)
    {
        _b -> group = _a;
    }
    else if(_a -> depth < _b -> depth)
    {
        _a -> group = _b;
    }
    else
    {
        _b -> group = _a;
        _a->depth += 1;
    }
}

int main(void)
{
    int n;
    cin >> n;
    for(int i = 0; i< n; i++)
    {
        int id;
        int f;
        int m;
        int num;
        int chi;
        int h;
        int a;
        cin >> id >> f >> m;
        arr[id].valid = true;
        if(f != -1)
        {
            unit(arr, id, f);
            arr[f].valid = true;
        }
        if(m != -1)
        {
            unit(arr, id, m);
            arr[m].valid = true;
        }
        cin >> num;
        while(num--)
        {
            cin >> chi;
            unit(arr, id, chi);
            arr[chi].valid =true;
        }
        cin >> h;
        cin >> a;
        arr[id].h = h;
        arr[id].a = a;
    }
    vector<struct person*> fam;
    struct person* root;
    for(int i = 0; i<10005; i++)
    {

        if(arr[i].valid)
        {
            root = query(arr, i);
            if(root != arr+i)
            {
                root->peo += 1;
                root->h += arr[i].h;
                root->a += arr[i].a;
            }
            else
            {
                fam.push_back(&arr[i]);
            }
            if(root->min > i)root->min = i;
        }
    }
    sort(fam.begin(), fam.end(),cmp);
    vector<struct person*>::iterator iter;
    cout<<fam.size()<<endl;
    for(iter = fam.begin(); iter!= fam.end(); iter++)
    {
        cout<<setfill('0')<<setw(4)<<(*iter)->min<<" ";
        cout<<(*iter)->peo<<" ";
        cout<<fixed<<setprecision(3)<<1.0*(*iter)->h/(*iter)->peo<<" ";
        cout<<fixed<<setprecision(3)<<1.0*(*iter)->a/(*iter)->peo<<endl;
    }
    return 0;
}


