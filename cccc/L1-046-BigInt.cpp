#include<iostream>
#include<string>
#include<sstream>
#include<cstdio>
using namespace std;

// view 0 only have 0, don't have -0
class CBigInt
{
    public:
    string num;
    int symbol;
    int length;

    CBigInt(string in)
    {
        if(in[0] == '-')
        {
            symbol = -1;
            num = in.substr(0,in.size() -1 );
            length = in.size()-1;
        }
        else
        {
            symbol = 1;
            num = in;
            length = in.size();
        }
    }
    CBigInt(CBigInt& a)
    {
        num = a.num;
        symbol = a.symbol;
        length = a.length;
    }
    static void _remove_zero(CBigInt& a)
    {
        int i = 0;
        for(; i< a.length; i++)
        {
            if(a.num[i] != '0')
            {
                break;
            }
        }

        a.length -= i;
        a.num = a.num.substr(i, a.length);

        if( 0 == a.length )
        {
            a.num = "0";
            a.length = 1;
            a.symbol = 1;
        }
    }
    CBigInt operator%(const CBigInt& a)
    {
        string init = "0";
        CBigInt res(this->num);
        if(symbol > 0 && a.symbol > 0)
        {
            while(res > a)
            {
                res = res - a;
                //cout<<res.num<<endl;
            }
            return res;
        }
        cout<<"negetive % undefine"<<endl;

        return res;
    }
    CBigInt operator/(const CBigInt& a)
    {
        string res = "0";
        if(symbol > 0 && a.symbol > 0)
        {
            int counter = 1;
            int tail_len = length - a.length;
            CBigInt tmp(num.substr(0,length - tail_len));
            while(true)
            {
                counter = 0;
                while((tmp<a)==0)
                {
                    tmp = tmp - a;
                    counter++;
                }
                res += (CBigInt::Int2String(counter));

                if(tail_len == 0)break;
                else
                {
                    tail_len --;
                    tmp.num += num[length - tail_len - 1];
                    tmp.length ++;
                }
            }
            for(int i = 0; i < tmp.length-1; i++)res+="0";
        }
        else cout<<"negetive / undefine"<<endl;

        CBigInt _res(res);
        CBigInt::_remove_zero(_res);
        return _res;
    }
    CBigInt operator-(const CBigInt& a)
    {
        CBigInt abs1(this->num);
        CBigInt abs2(a.num);
        string init = "0";
        CBigInt res(init);

        if( symbol != a.symbol)
        {
            res = abs1 + abs2;
            if(symbol < 0)res.symbol = -1;
            return res;
        }

        bool swp=false;
        if(abs1 < abs2)
        {
            swp = true;
            CBigInt tmp(init);
            tmp = abs1;
            abs1 = abs2;
            abs2 = tmp;
        }

        int borrow = 0;
        for(int i = 0; i<abs2.length; i++)
        {
            int index1 = abs1.length -1 -i;
            int index2 = abs2.length -1 -i;
           int a = abs1.num[index1] - '0';
           int b = abs2.num[index2] - '0';

           if(a+borrow < b)
           {
               abs1.num[index1] = (a+borrow-b) + 10 + '0';
               borrow = -1;
           }
           else
           {
               abs1.num[index1] = (a+borrow-b) + '0';
               borrow = 0;
           }
        }

        for(int i = abs2.length; borrow == -1; i++)
        {
            int index1 = abs1.length -1 -i;
            int a = abs1.num[index1] - '0';
            if(a+borrow < 0)
           {
               abs1.num[index1] = (a+borrow) + 10 + '0';
               borrow = -1;
           }
           else
           {
               abs1.num[index1] = (a+borrow) + '0';
               borrow = 0;
           }
        }

        abs1.symbol = this->symbol;
        if(swp)abs1.symbol *= -1;

        CBigInt::_remove_zero(abs1);

        return abs1;
    }

    CBigInt operator+(const CBigInt& a)
    {
        cout<<"add undefine"<<endl;
        string init = "0";
        CBigInt res(init);
        return res;
    }
    bool operator<(const CBigInt& a)
    {
        if(a.symbol != symbol)
        {
            if(a.symbol < 0)return false;
            else return true;
        }

        bool result;
        if(a.length > length)result = true;
        else if(a.length < length) result = false;
        else
        {
            result = false;
            for(int i = 0; i < length; i++)
            {
                if(a.num[i] > num[i])
                {
                    result = true;
                    break;
                }
                else if(a.num[i] < num[i])
                {
                    result = false;
                    break;
                }
            }
        }
        if(symbol > 0)return result;
        else return !result;
    }
    bool operator>(const CBigInt& a)
    {
        if(a.symbol != symbol)
        {
            if(a.symbol < 0)return true;
            else return false;
        }

        bool result;
        if(a.length > length)result = false;
        else if(a.length < length) result = true;
        else
        {
            result = false;
            for(int i = 0; i < length; i++)
            {
                if(a.num[i] > num[i])
                {
                    result = false;
                    break;
                }
                else if(a.num[i] < num[i])
                {
                    result = true;
                    break;
                }
            }
        }
        if(symbol > 0)return result;
        else return !result;
    }
    static string Int2String(int n)
    {
        ostringstream stream;
        stream<<n;
        return stream.str();
    }
    static int String2Int(string a)
    {
        int n;
        sscanf(a.c_str(),"%d",&n);
        return n;
    }
};

int main(void)
{
    int n;
    int counter = 0;
    int rest = 0;

    cin >> n;
    while(true)
    {
        counter++;
        rest = (rest*(10%n)+1)%n;
        if(rest == 0)break;
    }
    string single = "";
    for(int i = 0; i < counter; i++)
    {
        single += "1";
    }
    CBigInt a(single);
    CBigInt b(CBigInt::Int2String(n));
    cout<<(a/b).num<<" "<<counter<<endl;

    return 0;
}


