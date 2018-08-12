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
struct state{
	int x,y;
	state(){}
	state(int a,int b):x(a),y(b){}
};
char grid[16][16];
int R,C;
bool visg[16][16];
bool vis[16][16];
string ans;
const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0}; 
inline bool valid(int x,int y){
	if(x < 0 || x >= R || y < 0 || y >= C)return false;
	return true;
}
int bfs(int x,int y){
	int cnt = 0;
	queue<state> q;
	memcpy(vis,visg,sizeof(visg));
	q.push(state(x,y));
	while(!q.empty()){
		state st = q.front();q.pop();
		x = st.x;y = st.y;
		for(int i = 0;i < 4;i++){
			int newx = x + dx[i];
			int newy = y + dy[i];
			if(valid(newx,newy) && grid[newx][newy]!='#' && (!vis[newx][newy])){
				vis[newx][newy] = true;
				q.push(state(newx,newy));
				cnt++;
			}
		}
	}
	return cnt;
}
bool better(string& s){
	int sz = s.size();
	if(sz > ans.size())return true;
	else if(sz == ans.size() && s > ans)return true;
	else return false;
}
void dfs(int dep,int x,int y,string s){
	int h = bfs(x,y);
	if(dep + h < ans.size())return;
	if(dep + h == ans.size() && (s + "z") < ans)return;
	if(better(s))ans = s;
	
	for(int i = 0;i < 4;i++){
		int newx = x + dx[i];
		int newy = y + dy[i];
		if(valid(newx,newy) && !visg[newx][newy] && grid[newx][newy]!='#'){
			visg[newx][newy] = true;
			dfs(dep+1,newx,newy,s+grid[newx][newy]);
			visg[newx][newy] = false;
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(cin >> R >> C){
		if(!(R||C))break;
		ans = "";
		memset(visg,false,sizeof(visg));
		for(int i = 0;i < R;i++)scanf("%s",grid[i]);
		for(int i = 0;i < R;i++){
			for(int j = 0;j < C;j++){
				if(grid[i][j]!='#'){
					string s = "";
					s = s + grid[i][j];
					visg[i][j] = true;
					dfs(1,i,j,s);
					visg[i][j] = false;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
