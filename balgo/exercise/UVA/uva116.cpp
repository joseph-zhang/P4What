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
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
const int maxm = 12;
const int maxn = 102;
int d[maxm][maxn];
int grid[maxm][maxn];
int Next[maxm][maxn];
int first;
int res;
int M,N;
int main(){
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while(cin >> M >> N){
		for(int i = 0;i < M;i++)
			for(int j = 0;j < N;j++)
				scanf("%d",&grid[i][j]);
		res = INF;first = 0;
		for(int j = N-1;j >= 0;j--){
			for(int i = 0;i < M;i++){
				if(j == N-1)d[i][j] = grid[i][j];
				else{
					d[i][j] = INF;
					int rows[3] = {i-1,i,i+1};
					if(i == 0)rows[0] = M-1;
					if(i == M-1)rows[2] = 0;
					sort(rows,rows+3);
					for(int k = 0;k < 3;k++){
						int temp = d[rows[k]][j+1]+grid[i][j];
						if(temp < d[i][j]){d[i][j] = temp;Next[i][j] = rows[k];}
					}
				}
				if(j == 0){
					if(res > d[i][j]){res = d[i][j];first = i;}
				}
			}
		}
		printf("%d",first+1);
		for(int i = Next[first][0],j = 1;j < N;i = Next[i][j],j++)
			printf(" %d",i+1);
		cout << endl;
		cout << res << endl;
	}
	return 0;
}
