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
*    2-Satisfiability问题.
*    2-SAT是数理逻辑上的一个问题模型(可满足性问题的一种),有很多应用.
*    有n个bool变量Xi(i=1,2,...,n),还有m个需要满足的条件m,每个条件都满足形式:
*    [(Xi为真/假) ∨ (Xj为真/假)].
*    解决问题的目标是为每个未确定的Xi赋予合适的bool值使所有条件成立.
*    解决问题的演算法:O(VE)
*    (I)-为问题建立有向图模型:
*        将每个变量Xi拆成两个结点 2i 和 2i+1,分别表示:Xi为假(2i),Xi为真(2i+1),这样方便实现.
*        例如对于"Xi为假∨Xj为假",建立有向边 (2i+1)->(2j),(2j+1)->(2i)
*        有向边"->"表示"推导出"的意思.
*    (II)-建好图之后进行如下过程:
*        逐一考虑没有被赋值的变量Xi,先假定它为假(标记节点2i),然后沿着有向边走并沿路标记结点.
*        若在标记过程中发现某变量对应的两个结点都被标记,矛盾.从头开始,以假定Xi为真(标记2i+1)开始.
*        若不管Xi以真还是假开始都有矛盾,可知无解.
*/
/**
*    除了上述演算法外,还有一个演算法:O(V+E):
*    (I)  .建立有向圖。
*    (II) .尋找所有SCC。
*    (III).收縮每個SCC，成為有向無環圖DAG。
*　　    （同一個SCC裡面的點，必須同進退;要么全選，要么全不選）
*    (IV) .尋找縮圖的Topological Ordering。
*    (V)  .在縮圖上,以Topological Ordering的反序,設定解。
*/

/*程式使用第一种演算法,变量编号从0开始*/
const int maxn = 100;
int n,m;
vector<int> G[maxn*2]; //以点的邻接表建图
bool mark[maxn*2]; //标记记录
int S[maxn*2],c; //S是记录沿路结点编号的栈,c是计数器

//从结点x开始走,沿路标记.若出现矛盾则返回false
bool dfs(int x){
	if(mark[x^1])return false;
	if(mark[x]) return true;
	mark[x] = true;
	S[c++] = x;
	for(int i = 0;i < G[x].size();i++)
		if(!dfs(G[x][i]))return false;
	return true;
}

//对形如 (x=xval ∨ y=yval) 的条件建立有向边,val值为0或1
void add_clause(int x,int xval,int y,int yval){
	x = x*2+xval;
	y = y*2+yval;
	G[x^1].push_back(y);
	G[y^1].push_back(x);
}

//主驱函数,返回True则表示给出了解,返回False则表示无解
bool solve(){
	//对每个未决定的变量做尝试
	for(int i = 0;i < n<<1;i+=2){
		if(!mark[i] && !mark[i+1]){
			c = 0;
			if(!dfs(i)){ 
				while(c) mark[S[--c]] = false;
				if(!dfs(i+1)) return false;
			}
		}
	}
	return true;
}

int main(){
	printf("How many variables and conditions? ");
	scanf("%d%d",&n,&m);
	printf("Now give me conditions like x xval y yval\n");
	//初始化
	for(int i = 0;i < n<<1;i++) G[i].clear();
	memset(mark,false,sizeof(mark));
	
	for(int i = 0;i < m;i++){
		int x,xval,y,yval;
		scanf("%d%d%d%d",&x,&xval,&y,&yval);
		add_clause(x,xval,y,yval);
	}
	cout << "Solving..."<< endl;
	cout << "result:"<< endl;
	if(!solve()){cout << "No solution!" << endl;return 0;}
	for(int i = 0;i < n<<1;i+=2)
		printf("%d: %d\n",i>>1,mark[i]^1);
	return 0;
}
