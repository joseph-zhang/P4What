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
int N;
char str[2002][10];
int  G[2002][2002];

int prim(){
	bool done[N+2];
	int dis[N+2];
	int parent[N+2];
	int sum = 0;
	fill(dis,dis+N,INF);
	fill(parent,parent+N,-1);
	memset(done,false,sizeof(done));
	dis[0] = 0;
	for(int i = 0;i < N;i++){
		int a = -1,b = -1,min = INF;
		for(int j = 0;j < N;j++){
			if(!done[j] && dis[j] < min){
				a = j;
				min = dis[j];
			}
		}
		if(a == -1) break;
		done[a] = true;
		sum += dis[a];
		for(b = 0; b < N;b++){
			if(!done[b] && G[a][b] < dis[b])
				dis[b] = G[a][b];
		}
	}
	return sum;
}
int main(){
	while(cin >> N){
		if(!N) break;
		for(int i = 0;i < N;i++)
			scanf("%s",str[i]);
		for(int i = 0;i < N;i++){
			for(int j = i+1;j < N;j++){
				int count = 0;
				for(int k = 0;k < 7;k++)
					if(str[i][k] != str[j][k]) count++;
				G[i][j] = G[j][i] = count;
			}
		}
		cout << "The highest possible quality is 1/" << prim() <<"." << endl; 
	}
	return 0;
}
