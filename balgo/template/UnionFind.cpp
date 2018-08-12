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
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/**
*    并查集(UnionFind)可以高效的管理元素的分组情况.
*    总体来说结构是森林,森林中的每一棵树都是一个组别,并且每一组都有一个BOSS作为根.
*    开始时所有的元素都是自己组的BOSS(老大). Union,可以想象成组内两成员进行交涉然后合并.
*    最有效的地方在于查询(Find)操作时随手做的路径压缩,大大提高了效率,同时避免了树的退化.
*/

const int N = 10;
int cntGroup = 0;//统计有多少个分组
int p[N+2]; //记录所在组的BOSS是谁

//初始化,每个元素都是自己组的BOSS
inline void initSet(){
	for(int i = 0;i < N;i++)p[i] = i;
	cntGroup = N;
}
inline int Find(int x){ //To find x's Boss.
	return x == p[x]?x:(p[x] = Find(p[x]));
}
/*void Union(int x,int y){
	p[Find(x)] = Find(y);
}*/
void Union(int x,int y){
	int px = Find(x),py = Find(y);
	if(px == py)return;
	p[px] = py;
	cntGroup--;
}
int main(){
	int a,b,c;cin >> a >> b >> c;
	printf("Now give number to original set,10 numbers.\n");
	for(int i = 0;i < N;i++)scanf("%d",&p[i]);
	initSet();
	printf("Now we have totally %d groups.\n",cntGroup);
	printf("find %d times.\n",a);
	while(a--){
		int m;cin >> m;
		printf("the Boos of %d: ",m);
		cout << Find(m) << endl;
	}
	cout << endl;
	printf("Union %d times.\n",b);
	while(b--){
		int m,n;cin >> m >> n;
		Union(m,n);
		printf("union %d and %d successfully.\n",m ,n);
	}
	cout << endl;
	printf("Now we have totally %d groups.\n",cntGroup);
	printf("Now find again,%d times.\n",c);
	while(c--){
		int m;cin >> m;
		printf("the Boos of %d: ",m);
		cout << Find(m) << endl;		
	}
	cout << endl;
	cout << "##Proccessing Is Over##" << endl;
	return 0;
}



