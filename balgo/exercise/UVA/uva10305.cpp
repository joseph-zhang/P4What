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
#define INF 0x7fffffff
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
bool adj[102][102];
int indegree[102];
vector<int> res;
int N,M;
void solve(){
	int i,cnt = 0;
	while(cnt < N){
		for(i = 1;i <= N;i++){
			if(!indegree[i]){indegree[i] = -1;break;}
		}
		res.push_back(i);
		cnt++;
		for(int j = 1;j <= N;j++){
			if(adj[i][j]){
				adj[i][j] = false;
				indegree[j]--;
			}
		}
	}
}
int main(){
	while(cin >> N >> M){
		if(!(M||N)) break;
		memset(adj,false,sizeof(adj));
		memset(indegree,0,sizeof(indegree));
		res.clear();
		int a,b;
		for(int i = 0;i < M;i++){
			cin >> a >> b;
			adj[a][b] = true;
			indegree[b]++;
		}
		solve();
		for(int i = 0;i < res.size()-1;i++)
			cout << res[i] << " ";
		cout << res[res.size()-1] << endl;
	}
	return 0;
}
