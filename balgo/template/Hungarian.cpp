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
*    匈牙利(Hungarian)演算法由 Edmonds 基于 Hall 定理提出.
*    可由该演算法求得二分图的最大(基数)匹配(即匹配边数最大).
*	 (注:最大二分匹配也可由网络流方法来求出)
*    当完美匹配存在时就可达成完美匹配.
*    具体的方法由 Berge 定理奠定基础.
*    下面的程式以无权二分图为基础简单的实现了Hungarian.(设节点从1开始标记)
*/
bool adj[502][502];  //精简的邻接矩阵结构
int mx[502],my[502]; //匹配结构
bool vis[502];
int nx,ny,m; //nx+ny个点,m条边
//由DFS建立交错树
 bool DFS(int x){
	for(int y = 1;y <= ny;y++){
		if(adj[x][y] && (!vis[y])){
			vis[y] = true;
			if(my[y]==-1 || DFS(my[y])){
				my[y] = x;
				mx[x] = y;
				return true;
			}
		}	
	}
	return false;
}
int hungarian(){
	memset(mx,-1,sizeof(mx));
	memset(my,-1,sizeof(my));	
	int cnt = 0;
	for(int i = 1;i <= nx;i++){
		memset(vis,false,sizeof(vis));
		if(DFS(i)) cnt++;
	}
	return cnt;
}
int main(){
	while(cin >> nx >> ny >> m){
		memset(adj,false,sizeof(adj));
		for(int i = 0;i < m;i++){
			int x,y;
			cin >> x >> y;
			adj[x][y] = true;
		}
		cout << hungarian() << endl;
		for(int i = 1;i <= nx;i++) cout << mx[i] << " ";
		cout << endl;
		for(int i = 1;i <= ny;i++) cout << my[i] << " ";
	}
	return 0;
}

/**
*    有用的定理:
*        (1) 最大 匹配边数=最大独立集数
*        (2) 最大 匹配边数=最小覆盖(点覆盖)数
*        (3) 最小 边覆盖数=顶点数目n - 最大匹配边数
*/