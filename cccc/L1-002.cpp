#include<iostream>
using namespace std;
int main(void)
{
  int number;
  int level = 0;
  char symbol;
  cin >> number;
  cin >> symbol;
  while(2*level*level-1 <= number){level++;}
  level--;
  for(int i = level; i > 0; i --)
  {
    for(int j = 0; j < level - i; j ++)cout<<" ";
    for(int j = 0; j < 2*i -1 ;j++)cout<<symbol;
    //for(int j = 0; j < level - i; j ++)cout<<" ";
    cout<<endl;
  }
  for(int i = 2; i <=level; i++)
  {
    for(int j = 0; j < level - i; j ++)cout<<" ";
    for(int j = 0; j < 2*i -1 ;j++)cout<<symbol;
    //for(int j = 0; j < level - i; j ++)cout<<" ";
    cout<<endl;
  }
  cout<<number-2*level*level+1;
  return 0;
}
