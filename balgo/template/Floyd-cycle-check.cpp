#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#include<sstream>
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/**
*    该方法以Floyd命名,可用于判别一条迹上是否有圈,有的话可以找出连接点位置.
*    这个演算法有个形象的名字:龟兔赛跑法,具体思想如下:
*    设置两个标记变量放置在起点处,一个每次前进1步(龟),另一个每次前进两步(兔).
*    若在前进过程中两变量相撞,则说明有圈.
*    若想进一步确定圈的连接点在哪里,将龟重新放在起点,兔还在相撞处.
*    这一次设置龟和兔的速度相同,再次开始前进,当他们再次相遇时的位置就是连接点.
*    程式不再给出,掌握思想即可,非常简单的方法.
*/

    \\
     \\_
  .---(')                                                  
o( )_-\_             

    \\
     \\_
  .---(')
o( )_-\_

