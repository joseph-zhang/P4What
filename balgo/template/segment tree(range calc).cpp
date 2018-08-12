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
*    区间修改:区间值加减
*    add(l,r,v): 将区间A[l,r]上的值同时加v;
*    query(l,r): 查询区间[l,r]上的各种信息(元素和,最大值,最小值);
*    更新: 直接在对应区间累计增減值。
*    查詢: 累加路线上的增減值。
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
		nodes[u].label = 0;
		return;
	}
	build(lc,L,M);
	build(rc,M+1,R);
	nodes[u].sumv = nodes[lc].sumv + nodes[rc].sumv;
	nodes[u].maxv = max(nodes[lc].maxv,nodes[rc].maxv);
	nodes[u].minv = min(nodes[lc].minv,nodes[rc].minv);
	nodes[u].label = 0;
}

//维护调整结点u上的信息,其对应区间是[L,R]
void maintain(int u,int L,int R){
	int lc = u<<1; int rc = (u<<1)+1;
	if(R > L){
		nodes[u].sumv = nodes[lc].sumv + nodes[rc].sumv;
		nodes[u].maxv = max(nodes[lc].maxv, nodes[rc].maxv);
		nodes[u].minv = min(nodes[lc].minv ,nodes[rc].minv);
	}
	if(nodes[u].label){
		nodes[u].sumv += nodes[u].label*(R-L+1); 
		nodes[u].maxv += nodes[u].label;
		nodes[u].minv += nodes[u].label;
	}
}

//修改过程,应用延迟标记思想
//add(l,r,v)
void update(int u,int L,int R){
	int lc = u<<1; int rc = (u<<1)+1;
	if(L >= l && R <= r)nodes[u].label += v; //加上延迟标记
	else{
		int M = L + ((R-L)>>1);
		if(M >= l)update(lc,L,M);
		if(M < r)update(rc,M+1,R);
	}
	maintain(u,L,R);//递归返回上一层时调整本结点信息
}
//查询过程,需要考虑祖先上标记的影响
//加一个参数add表示当前区间的所有祖先结点label值之和,累加路线上的标记值
//query(l,r)
void query(int u,int L,int R,int add){
	int lc = u << 1;int rc = (u<<1)+1; 
	if(L >= l && R <= r){ //递归边界,算一算
		_sum += nodes[u].sumv + add*(R-L+1);
		_min = min(_min,nodes[u].minv+add);
		_max = max(_max,nodes[u].maxv+add);
	}else{ //没被待查区间完全覆盖,继续向下走
		int M = L + ((R-L)>>1);
		if(M >= l)query(lc,L,M,nodes[u].label+add);
		if(M < r)query(rc,M+1,R,nodes[u].label+add);
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
		query(1,1,N,0);
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
		query(1,1,N,0);
		printf("Get info of %d~%d:\n",l,r);
		printf("sum:%d,maximum:%d,minimum:%d\n",_sum,_max,_min);
	}
	return 0;
}
