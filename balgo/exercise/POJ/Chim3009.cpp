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
int grid[22][22];
int row,col,sx,sy,tx,ty;
int res;
void dfs(int x,int y,int cnt){
	if(cnt>=10)return;
	int blox,bloy;
	if(grid[x-1][y]!= 1){ //up
		for(int i = x-1;i > 0;i--){
			if(grid[i][y] == 3){res = min(res,cnt+1);return;}
			if(grid[i][y] == 1){
				grid[i][y] = 0;
				dfs(i+1,y,cnt+1);
				grid[i][y] = 1;
				break;
			}
		}
	}
	if(grid[x+1][y]!=1){ //down
		for(int i = x+1;i <= row;i++){
			if(grid[i][y] == 3){res = min(res,cnt+1);return;}
			if(grid[i][y] == 1){
				grid[i][y] = 0;
				dfs(i-1,y,cnt+1);
				grid[i][y] = 1;
				break;
			}
		}
	}
	if(grid[x][y-1]!=1){ //left
		for(int j = y-1;j > 0;j--){
			if(grid[x][j] == 3){res = min(res,cnt+1);return;}
			if(grid[x][j] == 1){
				grid[x][j] = 0;
				dfs(x,j+1,cnt+1);
				grid[x][j] = 1;
				break;
			}
		}
	}
	if(grid[x][y+1]!=1){ ///right
		for(int j = x+1;j <= col;j++){
			if(grid[x][j] == 3){res = min(res,cnt+1);return;}
			if(grid[x][j] == 1){
				grid[x][j] = 0;
				dfs(x,j-1,cnt+1);
				grid[x][j] = 1;
				break;
			}
		}
	}
}
int main(){
	while(cin >> col >> row){
		if(!(row||col)) break;
		res = 20;
		for(int i = 1;i <= row;i++){
			for(int j = 1;j <= col;j++){
				int b;scanf("%d",&b);
				grid[i][j] = b;
				if(b == 2){sx = i;sy = j;}
			}
		}
		dfs(sx,sy,0);
		if(res>10)cout << -1 << endl;
		else cout << res << endl;
	}
	return 0;
}
