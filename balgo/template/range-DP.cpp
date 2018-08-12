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
*    区间DP,就是在区间上进行的DP.
*    其最一般的过程是:枚举区间,进行划分,合并.
*    这一类DP往往关键的是对区间状态的定义,需要注意的是区间含有两个端点.
*    理解思想后,重要的是进行训练,见识各种变形.无论如何变形其主要思想都是这样子的.
*    下面的程式是UVa10003 的解,这是区间DP最为基础的例子了.
*/

/**
*    切木棍(UVa10003):木棍长度为L(L<1000),上面有n(n<50)个切点.
*    按顺序给出,记为a[i]: 切点编号->切点在木棍上的位置
*    现在要将木棍切成n+1段,求最小费用.(切割费用:被切段的长度)
*    状态及指标: 切割木棍段[i,j]的最小费用,i<j;
*    转移方程: d(i,j) = min{d(i,k),d(k,j)}+a[j]-a[i], k是切点i和切点j之间的切点.
*    边界: d(i,i+1) = 0;
*    实现时倒着枚举区间递推就可以了.
*/
int L,N;
int pole[52]; //各切点位置
int d[52][52];
int main(){
	while(cin >> L){
		if(!L)break;
		cin >> N;
		for(int i = 1;i <= N;i++)scanf("%d",&pole[i]);
		pole[0] = 0;pole[N+1] = L;
		memset(d,0,sizeof(d));
		for(int i = N;i >= 0;i--){
			for(int j = i+1;j <= N+1;j++){
				d[i][j] = INF;
				if(j == i+1){d[i][j] = 0;continue;}
				int costs = pole[j] - pole[i];
				for(int k = i + 1;k < j;k++)
					d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
				d[i][j] += costs;
			}	
		}
		printf("The minimum cutting is %d.\n",d[0][N+1]);
	}
	return 0;
}
