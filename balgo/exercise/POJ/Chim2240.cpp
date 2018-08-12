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

double G[32][32];
char hash[40][40];
int N,M;
int times = 0;
int getIndex(char *s){
	for(int i = 1;i <= N;i++)
		if(!strcmp(s,hash[i])) return i;
}

bool floyd_detect(){
	for(int k = 1;k <= N;k++)
		for(int i = 1;i <= N;i++)
			for(int j = 1;j <= N;j++)
				if(G[i][k] * G[k][j] > G[i][j])
					G[i][j] = G[i][k]*G[k][j];
	for(int i = 1;i <= N;i++)
		if(G[i][i] > 1.0) return true;
	return false;
}

int main(){
	char a[42],b[42];
	while(cin >> N){
		if(!N) break;
		memset(G,0,sizeof(G));
		for(int i = 1;i <= N;i++)
			scanf("%s",hash[i]);
		cin >> M;
		double r;
		for(int i = 0;i < M;i++){
			scanf("%s %lf %s",a,&r,b);
			int num1 = getIndex(a);//find
			int num2 = getIndex(b);
			G[num1][num2] = r;
		}
		printf("Case %d:",++times);
		if(floyd_detect()) cout << " Yes" << endl;
		else cout << " No" << endl;
		getchar();
	}
	return 0;
}
