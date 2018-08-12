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
*    剪枝(Pruning)常用于搜索(状态空间搜寻),是一种优化思想,比较灵活.
*    剪枝的分类主要有两类:
*        (1)可行性剪枝:基础的剪枝方法,当无法通过当前状态进一步搜得解时,剪去.
*                      该种剪枝是区别于无脑穷举的最基本剪枝,避免搜索无用状态.
*                      当问题要求有可行性约束时就可以考虑使用.
*        (2)最优性剪枝:优化的剪枝技巧,主要方法是存下到当前时刻为止的最优解.
*                      与此同时,我们进行"乐观估价",如果在最"乐观"(实际上达不到,或是一般达不到)
*                      的情况下,还是出现了不那么好的解,就没必要再往深处走,可以回去.
*    剪枝的主要要求是:合理性(Validity),准确性(Accuracy),有效性(Efficiency).
*/

/**
*    迭代加深的A*(IDA*),就是加了剪枝的IDS.
*    假设深度限制是maxd,IDS如果有剪枝条件g(n)+h(n)>maxd,就成为了IDA*
*    其中g是当前层深度.h是在当前情形下的"乐观估价函数",即在最乐观情形下估计至少还要搜几层.
*    对于IDA*来说函数h是关键部分,但是不一定非要编写显式的估价函数h();
*    为了介绍该种思想,下面的程式给出了问题"编辑书稿"(uva11212)的解决.
*/

/**
*    编辑书稿(uva11212):一篇文章有n(2<=n<=9)个自然段,每个段落都有编号(从1开始).
*    给出段落编号的一个排列,希望可以用剪(cut)和贴(paste)将它们组织成1,2,3,...
*    可以cut连续的自然段,然后再paste在任意位置,但是剪贴板只有一个.
*    求一下最小的剪贴次数.
*/

int a[10];
int maxd,n;

//判定是否达成要求
bool isSorted(int *p){
	for(int i = 0;i < n-1;i++)
		if(p[i] >= p[i+1]) return false;
	return true;
}
//当前状态下后继不正确数字个数
int err(){
	int cnt = 0;
	for(int i = 0;i < n-1;i++)
		if(a[i]+1 != a[i+1])cnt++;
	if(a[n-1] != n)cnt++;
	return cnt;
}
//d是深度
bool IDAs(int d){
	if(isSorted(a))return true;
	//乐观情形下每次剪贴后,后继不正确数字个数会减3
	if(3*(maxd - d) < err())return false;
	int olda[10],b[10];//b数组用于辅助
	memcpy(olda,a,sizeof(a));
	for(int i = 0;i < n;i++){	//枚举剪的位置
		for(int j = i;j < n;j++){
			int cnt = 0;
			for(int k = 0;k < n;k++)
				if(k < i||k > j)b[cnt++] = olda[k];	
			for(int k = 0;k <= cnt;k++){    //枚举贴的位置
				int cnt1 = 0;
				for(int p = 0;p < k;p++)a[cnt1++] = b[p];
				for(int p = i;p <= j;p++)a[cnt1++] = olda[p];
				for(int p = k;p < cnt;p++)a[cnt1++] = b[p];
				if(IDAs(d+1)) return true;//剪贴一次后,向深一层进行,尝试再一次剪贴
			}
		}
	}
	return false;
}
//调用的过程,逐步放宽深度限制
int solve(){
	if(isSorted(a))return 0;
	for(maxd = 1;maxd < n;maxd++){
		if(IDAs(0))return maxd;
	}
	return n-1;
}

int main(){
	int times = 0;
	while(cin >> n){
		if(!n)break;
		for(int i = 0;i < n;i++)cin >> a[i];
		int res = solve();
		printf("Case %d: %d\n",++times,res);
	}
	return 0;
}
