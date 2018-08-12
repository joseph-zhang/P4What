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
*    在有些时候,DP的状态比较复杂,可能是用集合来表示的一群位置信息,而不仅仅是一个位置.
*    但是我们又不可能开出几十维的数组来表示状态(开不下),这个时候要考虑其他方法来表示状态.
*    如果位置总数比较小时,可以考虑状态压缩,用位集来表示状态.
*    使用状态压缩手段的DP就是状压DP.
*    使用这种手段需要比较强的位处理技巧.
*    用一个例子来说明其思想.
*/

/**
*    种树:在N*M的(0-1)Grid里种树,0处可以种,1处不能种.
*    为保证光线充足,每棵树周围东南西北方向两格以内不能种.
*    求一下Grid里最多能种多少树.
*    思路:
*    每一行上选几个位置来种树,包含多个位置信息,用位集表示.
*    状态s(r,i,j): 第r行的种树状态i和第r-1行的种树状态j；
*    指标dp(r,i,j): 对于s(r,i,j),1~r 行的Grid最多能种多少树.
*    转移方程: dp(r,i,j) = max(dp(r-1,j,k))+cnt(i) ,每一行r对所有可能的i和j,k.
*    单独考虑一行假设所有位置都可放,行内不冲突的放法有ps种,将他们存在pres[]中,将各放法放了多少树存在cnt[];
*/
const int maxn = 20,maxm = 8;
int N,M;
int ps = 0;
int grid[maxn]; //将Grid也按位集保存
int dp[maxn][1<<maxm][1<<maxm];
//预处理,算出pres[]和cnt[]
void init(){
	for(int i = 0;i < (1 << M);i++){
		if( (i&(i<<1)) || (i&(i<<2)) ) continue;//行内冲突就不行
		pres[ps++] = i;
		int tmp = i;
		for(;tmp;tmp&=(tmp-1)) cnt[ps-1] += 1; //该循环计算tmp中有多少个1
	}
}
int dp(){
	memset(dp,0,sizeof(dp));
	//dp过程
	for(int r = 1;r <= N;i++){
		for(int i = 0;i < ps;i++){
			if(pres[i]&grid[r]) continue; //和grid冲突就不行
			for(int j = 0;j < ps;j++){
				for(int k = 0;k < ps;k++){
					if( pres[i]&pres[j] || pres[i]&pres[k] )continue;//r行和上两行都不能冲突.
					dp[r][i][j] = max(dp[r][i][j],dp[r-1][j][k]+cnt[i]);
				}
			}
		}
	}
	int res = 0;
	for(int i = 0;i < ps;i++)
		for(int j = 0;j < ps;j++)
			res = max(res,dp[N][pres[i]][pres[j]]);
	return res;
}

