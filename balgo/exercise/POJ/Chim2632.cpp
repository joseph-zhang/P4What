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
using namespace std;
struct Rob{
	int x,y;
	int toward;
	Rob(){}
	Rob(int i,int j,int t):x(i),y(j),toward(t){}
};
const int dx[4] = {-1,0,1,0};//N,E,S,W
const int dy[4] = {0,1,0,-1};
Rob robots[112];
int grid[120][120];
int row,col;
int N,M;

int dirc(char c){
	if(c == 'N') return 0;
	else if(c == 'E') return 1;
	else if(c == 'S') return 2;
	else if(c == 'W') return 3;
	else return -1;
}
bool valid(int x,int y){
	if(x == 0 || y == 0 || x > row || y > col) return false;
	return true;
}
void turn_left(int idx){
	int tow = robots[idx].toward;
	tow = (tow-1)<0?3:(tow-1);
	robots[idx].toward = tow;
}
void turn_right(int idx){
	int tow = robots[idx].toward;
	tow = (tow+1)==4?0:(tow+1);
	robots[idx].toward = tow;
}
int main(){
	int t;cin >> t;
	while(t--){
		memset(grid,0,sizeof(grid));
		cin >> col >> row;
		scanf("%d %d",&N,&M);
		for(int i = 1;i <= N;i++){
			int p1,ry;char f;
			scanf("%d %d %c",&ry,&p1,&f);
			int rx = row+1 - p1;
			robots[i] = Rob(rx,ry,dirc(f));
			grid[rx][ry] = i;
		}
		int restype,res1,res2;
		restype = res1 = res2 = 0;
		bool ok = false;
		for(int i = 1;i <= M;i++){
			int index,repeat;
			char f;
			scanf("%d %c %d",&index,&f,&repeat);
			if(ok)continue;
			if(f == 'L')
				for(int j = 0;j < repeat%4;j++)
					turn_left(index);
			if(f == 'R')
				for(int j = 0;j < repeat%4;j++)
					turn_right(index);
			if(f == 'F'){
				int tow = robots[index].toward;
				int newx = robots[index].x;
				int newy = robots[index].y;
				for(int j = 0;j < repeat;j++){
					newx = newx + dx[tow];
					newy = newy + dy[tow];
					if(!valid(newx,newy)){
						restype = 1;
						res1 = index;
						ok = true;break;
					}
					if(grid[newx][newy]){
						restype = 2;
						res1 = index;
						res2 = grid[newx][newy];
						ok = true;break;
					}
				}
				grid[robots[index].x][robots[index].y] = 0;
				grid[newx][newy] = index;
				robots[index].x = newx;robots[index].y = newy;
			}
		}
		if(restype == 1)
			printf("Robot %d crashes into the wall\n",res1);
		else if(restype == 2)
			printf("Robot %d crashes into robot %d\n",res1,res2);
		else 
			printf("OK\n");
	}
	return 0;
}
