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
*    背包问题大致分类: 部分背包,0/1背包,完全背包,多重背包。
*	 许多背包问题属于序列DP,具体的实现可以用滚动数组来加速.
*    还有几种背包的扩展问题。
*/

/*部分背包,利用贪心即可不再说*/
/**
*    0/1背包：几种物品,每种只有一个,不可分割。
*    状态及指标: c(i,j) 前i个物品和背包的限重j状态下可装的最大价值
*    转移方程: c(i,j) = max( c(i-1,j), c(i-1,j-weight[i])+val[i])
*    若c[]的初始化是全零,可以找到最优解
*    若想让背包达到载重上限,则设置c[0] = 0,c[1...W] = -INF.
*/
void knapsack01(){
	int c[W+1];
	memset(c,0,sizeof(c));
	for(int i = 1;i <= N;i++){
		for(int j = W;j>=weight[i];j--) // 注意这里一定要倒着滚动
			c[j] = max(c[j],c[j-weight[i]]+val[i]);
	}
	cout << c[W] << endl;
}

/**
*    完全背包(unbounded knapsack): 几种物品,每种个数无限多个,不可分割。
*    可以转化为0/1背包解决,具体实现与0/1背包的有些差许别。
*/
void knapsack_complete(){
	int c[W+1];
	memset(c,0,sizeof(c));
	for(int i = 1;i <= N;i++){
		for(int j = weight[i];j <= W;j++) //注意这里一定要正着滚动
			c[j] = max(c[j],c[j-weight[i]]+val[i]);
	}
	cout << c[w] << endl;
}
/**
*	 多重背包(bounded knapsack): 几种物品,每种都有给定的数量。
*    可以使用比例法(scaling method)解决,若第i种物品有M个,以2的幂对其划分,
*    划分出的各部分分别有 1,2,4,...,2^(k-1),M-(2^k-1) 个,将各部分绑成一捆,
*    视为新的物品,这样一来就可以转化为0/1背包解决。
*/
void knapsack_multi(){
	int c[W+1];
	memset(c,0,sizeof(c));
	for(int i = 1;i <= N;i++){
		int num = min(number[i],W/weight[i]);
		for(int k = 1;num>0;k<<=1){ //k控制每捆的个数
			if(k > num) k = num;
			num -= k;
			for(j = W;j>=weight[i]*k;j--)
				c[j] = max( c[j],c[j-weight[i]*k]+val[i]*k );
		}
	}
	cout << c[W] << endl;
}
/**
*    换零钱问题: 背包问题变种.给定几种面额不同的钞票,去凑得给定的钱数。
*    换零钱I(money-changing): 每种钞票张数无穷多,问是否能凑得;
*    换零钱II(coin-changing): 每种钞票张数无穷多,问能用多少种方式凑得;
*    换零钱III(chang-making): 每种钞票张数无穷多,问最少能用几张钞票凑得;
*    转移方程:   I: c(i,j) = c(i-1,j) OR c(i-1,j-price[i]);
*               II: c(i,j) = c(i-1,j) + c(i-1,j-price[i]);
*			   III: c(i,j) = min( c(i-1,j),c(i-1,j-price[i])+1 );
*    I,II,III均等价与完全背包问题. 
*    因为它们的实现基本一致,下面仅给出 money-changing 的实现。
*/
bool money_changing(){
	bool c[W+1];
	memset(c,false,sizeof(c));
	c[0] = true;
	for(int i = 1;i <= N;i++){
		for(int j = price[j];j<=W;j++)
			c[j] = c[j]||c[j-price[i]];
	}
	return c[W];
}
