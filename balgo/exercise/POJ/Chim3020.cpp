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
using namespace std;
int h,w;
bool grid[42][12];
bool G[405][405];
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};
int cnt;
int mx[405],my[405];
bool visy[405];

bool eds(int x){
	for(int y = 1;y <= cnt;y++){
		if(G[x][y] && (!visy[y])){
			visy[y] = true;
			if(my[y] == -1 || eds(my[y])){
				mx[x] = y;
				my[y] = x;
				return true;
			}
		}	
	}
	return false;
}

int main(){
	int time;
	cin >> time;
	while(time--){
		cin >> h >> w;
		char c;
		cnt = 1;
		int div[h*w+2];
		int index[h+2][w+2];
		memset(G,0,sizeof(G));
		memset(index,0,sizeof(index));
		memset(div,0,sizeof(div));
		for(int i = 1;i <= h;i++){
			for(int j = 1;j <= w;j++){
				cin >> c;
				if(c == 'o') grid[i][j] = 0;
				if(c == '*'){
					grid[i][j] = 1;
					index[i][j] = cnt++;
				}
			}
		}
		cnt--;
		for(int i = 1;i <= h;i++){
			for(int j = 1;j <= w;j++){
				if(!grid[i][j]) continue;
				if(div[index[i][j]] == 2) continue;
				div[index[i][j]] = 1;
				for(int p = 0;p < 4;p++){
					int newx = i+dx[p];
					int newy = j+dy[p];
					if(!grid[newx][newy]) continue;
					div[index[newx][newy]] = 2;
					G[index[i][j]][index[newx][newy]] = 1;
				}
			}
		}
		int res = 0;
		fill(mx,mx+401,-1);
		fill(my,my+401,-1);
		for(int i = 1;i <= cnt;i++){
			memset(visy,0,sizeof(visy));
			if(eds(i)) res++;
		}
		memset(visy,0,sizeof(visy));
		cout << cnt-res << endl;
	}
	return 0;
}
