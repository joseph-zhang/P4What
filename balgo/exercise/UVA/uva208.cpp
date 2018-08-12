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
#define Uint unsigned int
using namespace std;
bool G[22][22];
int N,K;
bool able[22];
vector<int> res; 
void bfs(int s){
	queue<int> q;
	bool vis[22];
	memset(vis,false,sizeof(vis));
	q.push(s);
	vis[s] = true;
	bool ok = false;
	while(!q.empty()){
		int x = q.front();q.pop();
		for(int i = 1;i <= N;i++){
			if(G[x][i] && !vis[i]){
				vis[i] = true;
				if(able[i]){ok = true;break;}
				q.push(i);
			}
		}
		if(vis[K] || ok){ok = true;break;}
	}
	if(ok)able[s] = true;
}
bool visit[22];
int cnt = 0;
void dfs(int s){
	//if(!able[s])return;
	res.push_back(s);visit[s] = true;
	if(s == K){
		cnt++;
		cout << res[0];
		for(int i = 1;i < res.size();i++)
			cout << " " << res[i];
		cout << endl;
		return;
	}
	for(int i = 2;i <= N;i++){
		if(G[s][i] && !visit[i]){
			dfs(i);
			visit[i] = false;
			res.pop_back();
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int time = 0;
	while(cin >> K){
		int a = K,b = K;
		N = 0;
		memset(able,false,sizeof(able));
		memset(G,false,sizeof(G));
		memset(visit,false,sizeof(visit));
		res.clear();
		while((a||b)){
			cin >> a >> b;
			N = max(N,max(a,b));
			G[a][b] = G[b][a] = true;
		}
		able[K] = true;
//		for(int i = 1;i <= N;i++){
//			if(i == K)continue;
//			bfs(i);
//		}
		bfs(1);
		cnt = 0;
		cout << "CASE " << ++time << ":" << endl;
		if(!able[1]) {printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,K);continue;}
		dfs(1);
		printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,K);
	}
	return 0;
}
