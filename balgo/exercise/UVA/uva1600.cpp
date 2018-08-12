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
const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};
struct state{
	int x,y,num;
	state(){}
	state(int a,int b,int n):x(a),y(b),num(n){}
};
int N,M,K;
bool valid(int x,int y){
	if(x < 1 || x > N || y < 1 || y > M) return false;
	return true;
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int t;cin >> t;
	while(t--){
		cin >> N >> M;
		cin >> K;
		bool grid[N+4][M+4];
		memset(grid,false,sizeof(grid));
		for(int i = 1;i <= N;i++)
			for(int j = 1;j <= M;j++)
				scanf("%d",&grid[i][j]);
		state start = state(1,1,0);
		bool visit[N+4][M+4][K+5];
		int dist[N+4][M+4];
		memset(visit,false,sizeof(visit));
		memset(dist,0,sizeof(dist));
		visit[1][1][0] = true;
		queue<state> q;
		q.push(start);
		bool ok = false;
		while(!q.empty()){
			state s = q.front();q.pop();
			if(s.x == N && s.y == M){ ok = true;break;}
			for(int i = 0;i < 4;i++){
				int newx = s.x + dx[i];
				int newy = s.y + dy[i];
				state news;
				if(valid(newx,newy)){
					if(!grid[newx][newy])
						news = state(newx,newy,0);
					else{
						if(s.num+1 > K) continue;
						news = state(newx,newy,s.num+1);
					}
					if(!visit[news.x][news.y][news.num]){
						q.push(news);
						visit[news.x][news.y][news.num] = true;
						dist[newx][newy] = dist[s.x][s.y]+1;
					}
				}
			}
		}
		if(!ok)cout << -1 << endl;
		else cout << dist[N][M] << endl;
	}
	return 0;
}

