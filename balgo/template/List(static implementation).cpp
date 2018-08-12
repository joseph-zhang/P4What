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
*    链表是非常基本的数据结构.
*    一般设置链表头部为哑节点,便于实现各种操作.
*    下面的程式是单向链表的一个简单的静态实现.
*    假设节点编号0置为哑节点.
*/

const int maxn = 1000;
int val[maxn];//节点编号到节点值的映射
int nxt[maxn];
int last;//表尾节点编号
int nc = 0;//结点分配计数器

void Init(){
	nxt[0] = 0;//哑结点
	last = 0;
}
//在以pos为编号的结点后面插入新的结点,值为value
void inserts(int pos,int value){
	int u = ++nc;
	val[u] = value;
	nxt[u] = nxt[pos];
	nxt[pos] = u;
	if(pos == last) last = u;
}
//在尾部追加
void Add(int value){inserts(last,value);}
//在值为pval的最左侧结点后插入
void Insert(int pval,int value){
	int u;
	for(u=nxt[0];u;u=nxt[u])
		if(val[u] == pval)break;
	inserts(u,value);
}
int main(){
	printf("Now input your instructions with the function-format several times.\n");
	char str[50];
	Init();
	while(true){
		scanf("%s",str);
		int a,b;
		if(str[0]=='E')break;
		switch(str[0]){
			case 'A': {sscanf(str,"Add(%d)",&b);Add(b);break;}
			case 'I': {sscanf(str,"Insert(%d,%d)",&a,&b);Insert(a,b);break;}
			case 'i': {sscanf(str,"inserts(%d,%d)",&a,&b);inserts(a,b);break;}
		}
		for(int u = nxt[0];u;u = nxt[u]){
			if(u!=nxt[0])cout << "->";
			printf("%d(%d)",u,val[u]);
		}
		printf("\n");
	}
	return 0;
}
