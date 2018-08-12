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
#include<sstream>
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
double coorx[1002],coory[1002];
double dist[1002][1002];
double d[1002][1002];
int vis[1002][1002];
int N,kase = 0;
void getDist(int a,int b){
	double xa = coorx[a],ya = coory[a];
	double xb = coorx[b],yb = coory[b];
	double deltx2 = (xa - xb)*(xa - xb);
	double delty2 = (ya - yb)*(ya - yb);
	dist[a][b] = dist[b][a] = sqrt(deltx2 + delty2);
}
//int dp(int i,int j){
//	if(i == N-1){dist[i][j] = dist[i][N] + dist[j][N];return dist[i][j];} 
//	if(vis[i][j] == kase)return d[i][j];
//	vis[i][j] = kase;
//	d[i][j] = min(dp(i+1,j)+dist[i][i+1],dp(i+1,i)+dist[j][i+1]);
//	return d[i][j];
//}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(cin >> N){
		++kase;
		for(int i = 1;i <= N;i++)
			scanf("%lf %lf",&coorx[i],&coory[i]);
		for(int i = 1;i <= N;i++){
			for(int j = i;j <= N;j++){
				if(i == j){dist[i][j] = dist[j][i] = 0;continue;}
				getDist(i,j);
			}
		}
		for(int i = N-1;i >= 2;i--){
			for(int j = 1;j < i;j++){
				if(i == N-1)d[i][j] = dist[i][N] + dist[j][N];
				else d[i][j] = min(d[i+1][j]+dist[i][i+1],d[i+1][i]+dist[j][i+1]);
			}
		}
		double res = dist[1][2]+d[2][1];
		printf("%.2lf\n",res);
	}
	return 0;
}

