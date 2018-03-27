# CCCC in PAT
### time:2018/03/08
## L1
### 006 题目表达不清，要求在n=a1*a2*...*ak 中的连续序列，而不是所有因子中的连续序列
* 求出n的所有可能因子，O(sqrt(n))
* 根据该题目的题意，DP不存在单调性性质，只是使用了重叠子问题。两重循环
* 对于seq找最长连续子序列，DP[i] = DP[i-1]+1, if a[i] = a[i-1]+1 and m[i] = m[i-1] * a[i] <= n
* 计算m[i]的时候小心溢出问题
### 009
* 辗转相除法，证明:设a=mc>b=nc,求余数r,证明r与b关于c的系数互质。递归证明。
* 更相减损术，证明:对于辗转相除法的a%b的过程用减法展开。
* 求最大公因数时，注意对于1特判
* 注意约分前先判断分子是否为0
* 注意当分子为0，整数部分为0时，仍要打印整数部分
* 对于大数，先约分再add可以加快加法速度
* 注意分母为负的输出方式与分子分母为负的约分:保证分母为正即可
* 注意分母为0的检测
### 020
* 注意handson的人的去重
* 注意00001输出的时候之前要补零
### 025
* 小数点不能在最前面和最后面
* 数字不能以0开头
* 以第一个空格作为AB的分界
### 028
* 素数筛超时
* sqrt遍历时，注意sqrt(3)=1, sqrt(2)=1, 要特判
### 041
* 在用空格分隔字符串时，注意字符串结束符也是一个分隔符。
  for(int i = 0;i<=a.size();i++)
  {
    if(a[i]==' ' || i==a.size())a.substr(index,i-index);
  }
### 043 大坑，题目错误，建议不要做
* 同一本书在没有归还的情况下多次借阅算最后一次借的时间
* 每一天借阅记录清空，不可跨天借阅
* 平均min四舍五入
### 046
* 大数取余
  (a*b)%n = ((a%n)*(b%n))%n
  (a+b)%n = ((a%n)+(b%n))%n
* 大整数比较
  注意比较前去除数字之前的0
  注意比较时对于正负号的处理
* 大整数减法
  基于大整数比较实现
  负数转为正数计算
  转为大数减小数
  注意在剪完后借位要继续向被减数前传递
* 大整数除法
  负数转化为正数后计算
  基于大数减法和比较实现除法
  按照笔算除法的方式对于除数一位一位移动
  注意除完后对于商的末尾补零和开头去零
* 大数除小数
  一种更为简单的实现
  将大数中的片段转为int后与小数做除法
  手动控制移位和余数

## L2
### 002 坑
* cin/cout 超时，printf与scanf AC
### 004
* 先根据前序遍历按照BST假设构造二叉树
* 用中序遍历的数组是否递增来判断是否为BST
* 注意值相等的情况
### 006
* 后序遍历的最后一个是root。
* 用root可以在中序遍历中把点分为左右两部分。
* 对于每一个根，左右子树中结点的相对位置在中、后序遍历中相同。都是先出现完左子树的结点再出现右子树的结点。
* 先递归构造出链状树，在用queue层序遍历。
### 007
* 并查集
* 构造：树状结构，将深度小的挂到深度大的上面。
* 查找：查找至root，比较root是否相同。
* 优化：路径压缩。用数组下标代替关键字。
### 008
* Manacher算法，最长回文子串，O(n)
* 用#填充，使得所有字符串都是奇数个：abcd => #a#b#c#d#
* 为了避免越界需要边界检测，可以在开头加$与结尾的'/0'匹配来省略边界检测
* 核心思想：abcdefghijklmn
            ----- - -----
             ---     ---
  一旦找到了一个较长的对称字符串，对称位置的搜索可以以前面对称位置的开始。
  比较边界一直前移，比较过的部分不用再次比较。
* for(int i = 0; i< len; i++)
  {
    mx[i] = (i>cur)?min(mx[center*2-i],cur-i):1;  // 注意min，不能超出最前面的范围
    while(m[i-mx[i]]==m[i+mx[i]])mx[i]++;         // trick: 用mx[i]自身作为递增下标
    if(i+mx[i]>cur)
    {
      cur = i+mx[i];
      center = i;
    }
  }
  // mx 为填充完成后的字符串
  // cur为当前最前比较位置+1
  // center 为cur对应的对称位置

### 012 小坑
* 大顶堆
* 建立：从最后一个元素开始下沉/在输入过程中加到数组末尾，上浮。（两种方式建起的堆不同）
* 插入：加在二叉树数组的最后一位，做上浮操作
* 查找：数组下标map键值
* 删除：用二叉数组最后一位覆盖删除结点，然后做下沉操作
* 采用数组实现不利于查询，采用链状树实现不利于维持树的平衡
* 建堆时间复杂度为O(n)，证明：由根分解为递归过程，T(n)=2T(n/2)+O(lgn)
* 完全二叉树数组表示child编号：
    从1开始编号
    每一层初始集结点为2^L
    上一层多一个结点下一层多两个结点
* 坑：log()以e为底，log2()才是以2为底的
* 坑：要在输入过程中build。如果全都输入完成后build会使堆不一样。
### 013
* 并查集
* 用并查集判断是否连通以及连通子图的个数。
* 注意：在用并查集判断连通性时不可路径压缩。
* 注意：当只有一个点的连通分量被占领时，连通子图数目会减少。

### 014
* 贪心策略
* 模拟会超时
* 选择最小大于当前值的轨道插入
* 只用记录轨道最后一个元素的值
* 记录数组由于数据更新方式的原因，自排序
* 用二叉搜索树实现插入并排序，不可以用set实现。
* Dilworth定理
* 二叉搜索树搜索最小上界：
  1. (s,e]
  2. 当递归至只剩一个元素时，要注意如果这是最后一个元素，有可能任然小于num。这时候代表找不到。
  3. 为了在初始没有元素的状态满足(s,e]，初始值设置为(-1,-1]
### 016 小坑
* 树的遍历
* a标记5代后，b检查
* 注意某人的父母有可能结婚后离婚，然后再婚。所有在记录一个人的父母时也要记录性别

## L3
## Exp
1. 注意变量的名称，是否修改，作用域。

## Need to learn
1. SPFA
2. Dilworth
3. L2-013 并查集+逆序加边

## OJ
1. 浮点错误：除数或者模数为0，或者溢出导致。
2. 

## stl
### cout
0. #include<iomanip>
1. 设置保留小数位数 cout<<setprecision(2)
2. 强制补足位数   cout<<fixed
3. 有时候用cout进行格式化字符串输出会出错，ex: L001-040 
4. 不足5位补零   cout<<setw(5)<<setfill('0')<<a;
### cin
1. 其实默认的时候，cin与stdin总是保持同步的，也就是说这两种方法可以混用，而不必担心文件指针混乱，同时cout和stdout也一样，两者混用不会输出顺序错乱
  在main中写 std::ios::sync_with_stdio(false); 
### string
1. #include<string>
1.cin >> a;   
  getcha();             // after cin getline need getchar() to remove /n left by cin.
  getline(cin, string);    // read a line end with '/n's
2. string a,b;
   a.find(b[i])    // if -1 not find, else return index
3. size()
6. string substr (size_t pos = 0, size_t len = npos) const
7. string to char*  : data不附加结束符'\0'，而c_str()返回一个以‘\0’结尾的字符数组。
8. string to int    :  sscanf(str.substr(3,5).c_str(),"%d",&integer)
9. num to string    :to_string(num)
10. #include<sstream>
  string Int_to_String(int n)
  {
  ostringstream stream;
  stream<<n; //n为int类型
  return stream.str();
  }

### set
1. 树状结构，自动排序
2. 无法随机访问
3. insert()
4. find(), 返回iter
5. 反序遍历
    for(set<char>::reverse_iterator iter = arr.rbegin(); iter!=arr.rend();iter++)
6. 修改set中的元素
    _set.erase(iter)
    _set.insert(value)
6. #include<algorithm>

### vector
0. #include<vector>
1. 去重
  sort(arr.begin(),arr.end());
  vector<char>::iterator iter = unique(arr);
  arr.erase(iter, arr.end());
2. 删除
  next_iter = arr.erase(iter)
  删除后iter要重新保存，否则会丢失iter
2. 查找
  #include<algorithm>
  vector<int>::iterator s=find(array.begin(),array.end(),50);
3. push_back()

### map
1. #include<map>
2. 遍历
  map<string,int>::iterator iter;
  for(iter=M.begin(); iter!=M.end(); iter++)
    cout<<iter->first <<"->"<<iter->second<<endl;



### heap
1. #include<heap>
2. heap可以在一个数组或者容器上面做
2. void make_heap(first_pointer,end_pointer,compare_function)
3. void pop_heap(first_pointer,end_pointer,compare_function)
4. void push_heap(first_pointer,end_pointer,compare_function)
5. void sort_heap(first_pointer,end_pointer,compare_function)
6. 建堆时间复杂度为O(n) !!!!!!

### distance
1. distance(_InputIterator __first, _InputIterator __last)
### queue
0. #include<queue>
1. push()
2. pop()
3. front()
4. end()
5. empty()
### priority_queue
1. push()
2. pop()
3. top()
4. define in struct :friend bool operator< (const struct node& n1, const struct node& n2)
5. 当priority_queue中存放指针时
  struct compare {
    bool operator () (const Node* a, const Node* b) const 
    {
         return a->weight < b->weight;
    }
  };
  std::priority_queue<Node*, std::vector<Node*>, compare> q;
6. 倒序
  priority_queue<string, vector<string>, greater<string> > que;
### deque
0. #include<queue>
1. push_back()
2. pop_front()
3. pop_back()
4. empty()
5. reference front()
6. reference back()
### stack
1. push()
2. pop()
3. top()
4. empty()
### pow
1. #include<cmath>
2. pow(base, exp);
### memset
1. #include<cstring>
2. memset(arr, 0, sizeof(arr));
### printf
1. 输出% printf("%%");
2. 向右对齐,每个数站5个空格位 printf("%5d");
3. 向左对齐，每个数占5个空格位   printf("%-5d");
4. 不足5位补零 printf("%05d", n);
### getchar()
1. #include<cstdio>
3. getchar() 当用户输入\n后，getchar才会开始在缓冲区里面读取字符。每次读一个，如出错返回-1
### unique
1. unique()是C++标准库函数里面的函数
2. 其功能是去除相邻的重复元素（只保留一个），所以使用前需要对数组进行排序
3. 返回值为重复元素开头指针
3. 对于长度为n数组a，unique(a,a+n) - a返回的是去重后的数组长度
4. 它并没有将重复的元素删除，而是把重复的元素放到数组的最后面藏起来了
### INT_MAX
1. #include<climits>
### sort
1. cmp : return true means no need to change
### floor
1. #include<cmath>
### ceil
1. #include<cmath>
### binary_search
* STL中对于有序序列（vector,list等）提供了相当相当强大的二分搜索Binary search算法(要求排完序)
* binary_search：判断是否存在某个对象
* lower_bound: 返回>=对象的第一个位置，lower_bound(2)=3, lower_bound(3)=3
 目标对象存在即为目标对象的位置,不存在则为后一个位置.
* upper_bound: 返回>对象的第一个位置, upper_bound(2)=3,upper_bound(3)=4
 无论是否存在都为后一个位置.
* equal_bound: 返回由lower_bound和upper_bound返回值构成的pair,也就是所有等价元素区间。
  equal_bound有两个需要注意的地方:
 1. 如果返回的两个迭代器相同，说明查找区间为空，没有这样的值
 2. 返回迭代器间的距离与迭代器中对象数目是相等的，对于排序区间，他完成了count和find的双重任务