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
#define LL long long 
#define sys std::ios::sync_with_stdio(false);
using namespace std;
const int dx[4] = {0,-1,0,1};
const int dy[4] = {-1,0,1,0};
char maze[42][42];
bool vis[42][42];
int sx,sy,ex,ey;
int row,col;
int leftcnt,rightcnt,shortcnt,cnt;
bool ok = false;
bool valid(int x,int y){
	if(x < 0 || x >= row || y < 0 || y >= col) return false;
	return true;
}
void dfs(int x,int y,int& xp,int& yp,int d,int& res){
	cnt++;
	if(x == xp && y == yp){
		ok = true;
		res = cnt;return;
	}
	int nd = (d+3)%4;
	for(int i = nd;i < nd+4;i++){
		int nx = x+dx[i%4];
		int ny = y+dy[i%4];
		if(valid(nx,ny) && maze[nx][ny] != '#')
			dfs(nx,ny,xp,yp,i,res);
		if(ok) return;
	}
}
void bfs(int x,int y){
	queue<int> q;
	vis[x][y] = true;
	q.push(col*x+y);
	int count[row][col];
	count[x][y] = 1;
	while(!q.empty()){
		int temp = q.front();q.pop();
		int orix = temp/col;int oriy = temp%col;
		for(int i = 0;i < 4;i++){
			int nx = orix + dx[i];
			int ny = oriy + dy[i];
			if(valid(nx,ny) && (!vis[nx][ny]) && maze[nx][ny] != '#'){
				count[nx][ny] = count[orix][oriy]+1;
				vis[nx][ny] = true;
				q.push(nx*col+ny);
			}
		}
		if(vis[ex][ey]) break;
	}
	shortcnt = count[ex][ey];
}
int main(){
	int n;cin >> n;
	while(n--){
		cin >> col >> row;
		memset(vis,false,sizeof(vis));
		char buffer[42];
		for(int i = 0;i < row;i++){
			scanf("%s",buffer);
			for(int j = 0;j < col;j++){
				maze[i][j] = buffer[j];
				if(maze[i][j] == 'S'){sx = i;sy = j;}
				if(maze[i][j] == 'E'){ex = i;ey = j;}
			}
		}
		cnt = 0;
		ok = false;
		dfs(sx,sy,ex,ey,0,leftcnt);
		cnt = 0;
		ok = false;
		dfs(ex,ey,sx,sy,0,rightcnt);
		bfs(sx,sy);
		printf("%d %d %d\n",leftcnt,rightcnt,shortcnt);
	}
	return 0;
}
