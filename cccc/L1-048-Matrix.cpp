#include<iostream>
using namespace std;
class CMatrix
{
    public: int l;
    public: int c;
    public: int** v;
    CMatrix(int l,int c)
    {
        this->l = l;
        this->c = c;
        v = new int*[l];
        for(int i = 0;i < l;i++)
        {
            v[i] = new int[c];
        }
    }
    CMatrix(CMatrix& m)
    {
        l = m.l;
        c = m.c;
        v = new int*[l];
        for(int i = 0;i < l;i++)
        {
            v[i] = new int[c];
        }
        for(int i = 0; i < l; i++)
        {
            for(int j = 0; j < c; j++)
            {
                v[i][j] = m.v[i][j];
            }
        }
    }
    void insert(int l,int c, int v)
    {
        this->v[l][c] = v;
    }

    static CMatrix* mul(CMatrix& a, CMatrix& b)
    {
        if(a.c != b.l)return NULL;
        CMatrix* tmp;
        tmp = new CMatrix(a.l, b.c);
        for(int i = 0; i <tmp->l; i ++)
        {
            for(int j = 0; j < tmp->c; j++)
            {
                int value = 0;
                for(int k = 0; k < a.c; k++)
                {
                    value += a.v[i][k]*b.v[k][j];
                }
                tmp->insert(i,j,value);
            }
        }
        return tmp;
    }
    void display()
    {
        cout<<l<<" "<<c<<endl;
        for(int i = 0; i < l;i ++)
        {
            for(int j = 0; j < c; j++)
            {
                cout<<v[i][j];
                if( j != c-1)cout<<" ";
            }
            cout <<endl;
        }
    }
    ~CMatrix()
    {
        for(int i = 0;i < l;i++)
        {
            delete[] v[i];
        }
    }
};

int main(void)
{
    int c;
    int l;
    cin >> l >>c;
    CMatrix a(l,c);
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < c; j ++)
        {
            int num;
            cin >> num;
            a.insert(i,j,num);
        }
    }
    cin >> l >>c;
    CMatrix b(l,c);
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < c; j ++)
        {
            int num;
            cin >> num;
            b.insert(i,j,num);
        }
    }
    CMatrix* m;
    m = CMatrix::mul(a,b);
    if(m == NULL)cout<<"Error: "<<a.c<<" != "<<b.l;
    else m->display();
    if(m != NULL)delete m;
    return 0;
}







