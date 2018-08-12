#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
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
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
int V,E,T;
vector<int> adj[1002];
bool vis[1002];

int dfs(int p){
	int oddNum = 0;
	oddNum += adj[p].size()%2;
	vis[p] = true;
	for(int i = 0;i < adj[p].size();i++){
		int v = adj[p][i];
		if(!vis[v])
			oddNum += dfs(v); 
	}
	return oddNum;
} 
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout); 
	int time = 0;
	while(cin >> V){
		cin >> E >> T;
		if(!(V||E||T))break;
		for(int i = 0;i <= V;i++)
			adj[i].clear();
		memset(vis,false,sizeof(vis));
		for(int i = 0;i < E;i++){
			int a,b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		int ans = 0;
		for(int i = 1;i <= V;i++){
			if(!vis[i] && adj[i].size())
				ans += max(dfs(i),2);
		}
		printf("Case %d: ",++time);
		cout << (max(ans/2-1,0) + E)*T << endl;
	}
	return 0;
}	
