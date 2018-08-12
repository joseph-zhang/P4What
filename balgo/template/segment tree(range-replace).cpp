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
*    线段树是处理区间信息强有力的方法,但是有时候仅有点修改并不能使我们满足.
*    我们经常会遇到要对整个区间处理的情况,依然需要动态的维护信息.
*    使我们做到这一点的主要思想是:"延迟标记".
*    当结点表示的区间完整地覆盖时,我们打上标记且不再进一步深入.
*    有两种方式,下述程式实现的是其中一个:区间值替换.
*    另外一个另行叙述.
*/
/**
*    区间修改:区间值替换
*    add(l,r,v): 将区间A[l,r]上的值同时改成v;
*    query(l,r): 查询区间[l,r]上的各种信息(元素和,最大值,最小值);
*    更新: 運用「lazy propagation」技巧，凡遭遇已改值的區間，則将标记下推。
*    查詢: 凡遭遇已改值的區間，即得答案，不必深入子孫。
*    注意下述程式在实现时假定数据从下标1开始.
*/
const int N = 10;
int arr[N+2];
int l,r,v; //将区间参数写成全局的,方便函数调用
int _sum = 0,_max = -1e6,_min = INF; //将查询返回值写成全局的
struct Node{
	int sumv,minv,maxv;
	int label;
	Node(){}
	Node(int _sumv,int _maxv,int _minv,int _label):
			sumv(_sumv),maxv(_maxv),minv(_minv),label(_label){}
}nodes[N<<1+5];


//建树 
void build(int u,int L,int R){
	int lc = u <<1; int rc = (u<<1)+1;
	int M = L + ((R-L)>>1);
	if(L == R){ //到达根结点
		nodes[u].sumv = arr[L];
		nodes[u].maxv = arr[L];
		nodes[u].minv = arr[L];
		nodes[u].label = -1;
		return;
	}
	build(lc,L,M);
	build(rc,M+1,R);
	nodes[u].sumv = nodes[lc].sumv + nodes[rc].sumv;
	nodes[u].maxv = max(nodes[lc].maxv,nodes[rc].maxv);
	nodes[u].minv = min(nodes[lc].minv,nodes[rc].minv);
	nodes[u].label = -1;
}

//维护调整结点u上的信息,其对应区间是[L,R]
void maintain(int u,int L,int R){
	int lc = u<<1; int rc = (u<<1)+1;
	if(R > L){
		nodes[u].sumv = nodes[lc].sumv + nodes[rc].sumv;
		nodes[u].maxv = max(nodes[lc].maxv, nodes[rc].maxv);
		nodes[u].minv = min(nodes[lc].minv ,nodes[rc].minv);
	}
	if(nodes[u].label >= 0){
		nodes[u].sumv = nodes[u].label*(R-L+1); 
		nodes[u].maxv = nodes[u].minv = nodes[u].label;
	}
}


//标记下推过程
void pushdown(int u){
	int lc = u<<1; int rc = (u<<1)+1;
	if(nodes[u].label >= 0){
		nodes[lc].label = nodes[rc].label = nodes[u].label; //向下传递标记
		nodes[u].label = -1; //抹去本节点标记
	}
}
//修改过程,应用延迟标记思想
//add(l,r,v)
void update(int u,int L,int R){
	int lc = u<<1; int rc = (u<<1)+1;
	if(L >= l && R <= r) nodes[u].label = v;
	else{
		pushdown(u);
		int M = L + ((R-L)>>1);
		if(M >= l)update(lc,L,M); else maintain(lc,L,M);  //注意标记下传后要更新结点信息
		if(M < r)update(rc,M+1,R); else maintain(rc,M+1,R); //注意标记下传后要更新结点信息
	}
	maintain(u,L,R);
}
void query(int u,int L,int R){
	if(nodes[u].label >= 0){ //递归边界1:一碰到标记就可以结束
		_sum += nodes[u].label * (min(R,r)-max(L,l)+1);
		_min = min(_min,nodes[u].label);
		_max = max(_max,nodes[u].label);
	}else if(L >= l && R <= r){ //递归边界2:覆盖
		_sum += nodes[u].sumv;
		_min = min(_min,nodes[u].minv);
		_max = max(_max,nodes[u].maxv);
	}else{  //统计
		int M = L + ((R-L)>>1);
		if(M >= l) query(u<<1,L,M);
		if(M < r) query((u<<1)+1,M+1,R);
	}
}

inline void retrive(){_sum = 0;_max = -1e6;_min = INF;}
int main(){
	for(int i = 1;i <= N;i++)scanf("%d",&arr[i]);
	build(1,1,N);
	int a,b,c;cin >> a >> b >> c;
	printf("Now query %d times.\n",a);
	while(a--){
		cin >> l >> r;
		retrive();
		query(1,1,N);
		printf("Get info of %d~%d:\n",l,r);
		printf("sum:%d,maximum:%d,minimum:%d\n",_sum,_max,_min);
	}
	printf("Update %d times.\n",b);
	while(b--){
		cin >> l >> r >> v;
		update(1,1,N);
		printf("Done!\n");
	}
	printf("Now query again,%d times.\n",c);
	while(c--){
		cin >> l >> r;
		retrive();
		query(1,1,N);
		printf("Get info of %d~%d:\n",l,r);
		printf("sum:%d,maximum:%d,minimum:%d\n",_sum,_max,_min);
	}
	return 0;
}
