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
const int dx[5] = {0,1,0,-1,0};
const int dy[5] = {1,0,-1,0,0};
int r,c,n;
int dis[200][200][200];
int G[200][5],deg[200];
int cnt = 0;
int s[3],t[3];
inline bool valid(int a,int b){
	if(a < 0 || b < 0 || a >= r || b >= c) return false;
	return true;
}
inline int state(int num1,int num2,int num3){
	return ((num1 << 16)|(num2 << 8)|num3);
}
inline bool conflict(int a,int b,int ap,int bp){
	if(ap == bp)return true;
	if(a == bp && b == ap) return true;
	return false;
}
void bfs(){
	memset(dis,-1,sizeof(dis));
	int start = state(s[0],s[1],s[2]);
	queue<int> q;
	q.push(start);
	dis[s[0]][s[1]][s[2]] = 0;
	while(!q.empty()){
		int st = q.front();q.pop();
		int st1 = (st >> 16)&0xff;
		int st2 = (st >> 8 )&0xff;
		int st3 = st&0xff;
		if(st1 == t[0] && st2 == t[1] && st3 == t[2])break;
		for(int i = 0;i < deg[st1];i++){
			int sa = G[st1][i];
			for(int j = 0;j < deg[st2];j++){
				int sb = G[st2][j];
				if(conflict(st1,st2,sa,sb))continue;
				for(int k = 0;k < deg[st3];k++){
					int sc = G[st3][k];
					if(conflict(st1,st3,sa,sc))continue;
					if(conflict(st2,st3,sb,sc))continue;
					if(dis[sa][sb][sc] == -1){
						dis[sa][sb][sc] = dis[st1][st2][st3] + 1;
						q.push(state(sa,sb,sc));
					}
				}
			}
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(scanf("%d%d%d\n", &c, &r, &n) == 3 && n){
		if(!(c||r||n))break;
		char grid[20][20];
		for(int i = 0;i < r;i++)
			fgets(grid[i],20,stdin);
		cnt = 0;
		int x[200],y[200],ID[18][18];
		memset(deg,0,sizeof(deg));
		for(int i = 0;i < r;i++){
			for(int j = 0;j < c;j++){
				if(grid[i][j] != '#'){
					x[cnt] = i;y[cnt] = j;
					ID[i][j] = cnt;
					if(islower(grid[i][j]))s[grid[i][j]-'a'] = cnt;
					else if(isupper(grid[i][j]))t[grid[i][j]-'A'] = cnt;
					cnt++;
				}
			}
		}
		for(int i = 0;i < cnt;i++){
			int newx,newy;
			for(int j = 0;j < 5;j++){
				newx = x[i] + dx[j];
				newy = y[i] + dy[j];
				if(valid(newx,newy) && grid[newx][newy]!='#')
					G[i][deg[i]++] = ID[newx][newy];
			}
		}
		if(n <= 1){deg[cnt] = 1;G[cnt][0] = cnt;s[1] = t[1] = cnt++;}
		if(n <= 2){deg[cnt] = 1;G[cnt][0] = cnt;s[2] = t[2] = cnt++;}
		bfs();
		cout << dis[t[0]][t[1]][t[2]] << endl;
	}
	return 0;
}
