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
*    线段树(segmentTree)是区间动态信息查询的有力方法.
*    sparse-table 和 BIT 能办到的,线段树不但都能办得到,还能够做到更多,是功能最强的.
*    举个例子:对于区间最小值查询,如果我要多次更新值,如果每次都重新建立sparse-table,显然是不合适的.
*    如果采用灵活的线段树,就可以轻松完成动态的区间信息的维护了.
*	 线段树的基本结构是二叉树.
*    若根结点对应的区间长度为 2^h ,则第i层有 2^i 个结点,每个结点对应一个长度为 2^(h-i) 的区间.
*    可知建成的二叉树最大高度为 h=lb(N),总结点数是 2^(h+1)-1,略小于整个区间长度的两倍.
*    下面实现了"点修改"的线段树.
*    Update(p,w): 将A[p]修改为w; (点修改)
*    Query(l,r): 查询区间[l,r]上的信息. (区间查询)
*/
const int N = 10;
int l,r; //将区间参数写成全局的,方便函数调用
int arr[N+5];
int _sum = 0,_max = -1e6,_min = 1e6; //将查询返回值写成全局的
struct Node{
	int sumv,maxv,minv;
	//...
	//想查什么都行,只要能预先计算出来
	Node(){}
	Node(int _sumv,int _maxv,int _minv):sumv(_sumv),minv(_minv),maxv(_maxv){}
}nodes[N<<1+5];

inline int LC(int u){return u << 1;}
inline int RC(int u){return (u<<1)+1;}

//建树 
void build(int u,int L,int R){
	int lc = LC(u);int rc = RC(u);
	if(L==R){  //到达根结点
		nodes[u].sumv = nodes[u].maxv = nodes[u].minv = arr[L]; 
		return;
	}
	int M = L + ((R-L)>>1);
	build(lc,L,M);
	build(rc,M+1,R);
	nodes[u].sumv = nodes[lc].sumv + nodes[rc].sumv;
	nodes[u].maxv = max(nodes[lc].maxv,nodes[rc].maxv);
	nodes[u].minv = min(nodes[lc].minv,nodes[rc].minv);
}
//更新节点信息,点修改
//Update(p,w)
void update(int u,int L,int R,int& pos,int& val){
	int lc = LC(u); int rc = RC(u);
	if(L==R){
		nodes[u].sumv = nodes[u].maxv = nodes[u].minv = val;
		return;
	}
	int M = L + ((R-L)>>1);
	if(pos <= M) update(lc,L,M,pos,val);
	else update(rc,M+1,R,pos,val);
	nodes[u].sumv = nodes[lc].sumv + nodes[rc].sumv;
	nodes[u].maxv = max(nodes[lc].maxv,nodes[rc].maxv);
	nodes[u].minv = min(nodes[lc].minv,nodes[rc].minv);
}
//查询区间信息
//Query(l,r)
void query(int u,int L,int R){
	int lc = LC(u); int rc = RC(u);
	if(L >= l && R <= r){ //递归边界:被待查区间完全覆盖
		_sum += nodes[u].sumv;
		_max = max(_max,nodes[u].maxv);
		_min = min(_min,nodes[u].minv);
		return;
	}
	int M = L + ((R-L)>>1);
	if(M >= l)query(lc,L,M);
	if(M < r)query(rc,M+1,R);
}
inline void retrive(){_sum = 0;_max = -1e6;_min = 1e6;}

int main(){	
	for(int i = 1;i <= N;i++)scanf("%d",&arr[i]);
	build(1,1,N);
	int a,b,c;cin >> a >> b >> c;
	printf("Query %d times.\n",a);
	while(a--){
		cin >> l >> r;
		retrive();
		query(1,1,N);
		printf("Get info of %d~%d :\n",l,r);
		printf("sum: %d,minimum: %d,maximum: %d\n",_sum,_min,_max);
	}
	printf("Update %d times.\n",b);
	while(b--){
		int pos,val;
		cin >> pos >> val;
		update(1,1,N,pos,val);
		printf("arr[%d] updated-->%d\n",pos,val);
	}
	printf("Now query again,%d times.\n",c);
	while(c--){
		cin >> l >> r;
		retrive();
		query(1,1,N);
		printf("Get info of %d~%d :\n",l,r);
		printf("sum: %d,minimum: %d,maximum: %d\n",_sum,_min,_max);
	}
	return 0;
}
