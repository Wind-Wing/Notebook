#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main(void)
{
  string a;
  getline(cin, a);
  int len = a.size();
  int cur = 0;
  int center = 0;
  string m="$#";
  for(int i = 0; i< len; i ++)
  {
    m+=a[i];
    m+="#";
  }
  len = m.size();
  int mx[len];
  for(int i = 0; i< len; i++)
  {
    mx[i] = (i>cur)?min(mx[center*2-i],cur-i):1;
    while(m[i-mx[i]]==m[i+mx[i]])mx[i]++;
    if(i+mx[i]>cur)
    {
      cur = i+mx[i];
      center = i;
    }

  }
  int res = 0;
  for(int i = 0; i <len; i++)
  {
    res = (res>mx[i])?res:mx[i];
  }
  cout<<res-1;
  return 0;
}
