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
int L,N;
int pole[1005];
int d[1005][1005];
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	while(cin >> L){
		if(!L)break;
		cin >> N;
		for(int i = 1;i <= N;i++)scanf("%d",&pole[i]);
		pole[0] = 0;pole[N+1] = L;
		memset(d,0,sizeof(d));
		for(int i = N;i >= 0;i--){
			for(int j = i+1;j <= N+1;j++){
				d[i][j] = INF;
				if(j == i+1){d[i][j] = 0;continue;}
				int costs = pole[j] - pole[i];
				for(int k = i + 1;k < j;k++)
					d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
				d[i][j] += costs;
			}	
		}
		printf("The minimum cutting is %d.\n",d[0][N+1]);
	}
	return 0;
}
