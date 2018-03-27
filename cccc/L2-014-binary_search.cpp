#include<iostream>
#include<set>
using namespace std;

int arr[100001];

int binary_search_upper_bound(int *arr, int s, int e, int num)
{
    if(s==e)return e+1;
    if(s+1==e&&arr[e]>num)return e;
    if(s+1==e&&arr[e]<num)return e+1;

    int mid = (s+e)/2;
    if(arr[mid] < num)return binary_search_upper_bound(arr, mid, e, num);
    else return binary_search_upper_bound(arr, s, mid, num);
}

int main(void)
{
    ios::sync_with_stdio(false);
    int n;
    int tmp;
    cin >> n;
    int index = -1;
     while(n -- )
    {
        cin >> tmp;
        int _index = binary_search_upper_bound(arr, -1, index, tmp);
        if(_index > index)
        {
            index++;
        }
        arr[_index] = tmp;
    }
    cout<<index+1;

    return 0;
}
