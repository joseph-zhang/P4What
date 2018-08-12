#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<string.h>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
using namespace std;

int row,column;
char grid[20][20];
int  visit[20][20];
int ci = 0,cj = 0;
int flag = 0;
bool valid(int x,int y){
	if(x < 0 || x >= row || y < 0 || y >= column) return false;
	return true;
}
void dfs1(int x,int y,int& cnt,int& flag){
	if(!valid(x,y)) return;
	if(!visit[x][y]) visit[x][y] = 1;
	else{
		ci = x;
		cj = y;
		flag = 1;
		return;
	}
	if(grid[x][y] == 'N') {cnt++;dfs1(x-1,y,cnt,flag);}
	if(grid[x][y] == 'S') {cnt++;dfs1(x+1,y,cnt,flag);}
	if(grid[x][y] == 'W') {cnt++;dfs1(x,y-1,cnt,flag);}
	if(grid[x][y] == 'E') {cnt++;dfs1(x,y+1,cnt,flag);}
}
void dfs2(int x,int y,int& cnt){
	if(x == ci && y == cj && cnt != 0) return;
	if(grid[x][y] == 'N') {cnt++;dfs2(x-1,y,cnt);}
	if(grid[x][y] == 'S') {cnt++;dfs2(x+1,y,cnt);}
	if(grid[x][y] == 'W') {cnt++;dfs2(x,y-1,cnt);}
	if(grid[x][y] == 'E') {cnt++;dfs2(x,y+1,cnt);}	
}
int main(){
	int begin;
	while(cin >> row >> column >> begin){
		if(!(row||column||begin)) break;
		memset(visit,0,sizeof(visit));
		ci = cj = flag = 0;
		int cnt1 = 0,cnt2 = 0;
		for(int i =0;i < row;i++)
			for(int j = 0;j < column;j++)
				cin >> grid[i][j];
		dfs1(0,begin-1,cnt1,flag);
		if(!flag) cout << cnt1 << " step(s) to exit"  << endl;
		else{
			dfs2(ci,cj,cnt2);
			cout << (cnt1-cnt2) <<  " step(s) before a loop of "  << cnt2 << " step(s)" << endl;
		}	
	}
	return 0;
}
