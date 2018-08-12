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
char str1[5005],str2[5005];
int s1[28],e1[28],s2[28],e2[28];
int d[2][5005],c[2][5005];
void init(int n,int m){
	fill(s1,s1+27,INF);
	memset(e1,0,sizeof(e1));
	fill(s2,s2+27,INF);
	memset(e2,0,sizeof(e2));
	for(int i = 1;i <= n;i++){
		int cha = str1[i]-'A';
		s1[cha] = min(s1[cha],i);
		e1[cha] = i;
	}
	for(int i = 1;i <= m;i++){
		int cha = str2[i]-'A';
		s2[cha] = min(s2[cha],i);
		e2[cha] = i;
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int t;cin >> t;
	while(t--){
		scanf("%s",str1+1);
		scanf("%s",str2+1);
		int n = strlen(str1+1);
		int m = strlen(str2+1);
		init(n,m);
		memset(d,0,sizeof(d));
		memset(c,0,sizeof(c));
		int trove = 0;
		for(int i = 0;i <= n;i++){
			for(int j = 0;j <= m;j++){
				if(!i && !j)continue;
				int v1 = INF,v2 = INF;
				if(i)v1 = c[trove^1][j] + d[trove^1][j];//通过从p里移转移到d(i,j)
				if(j)v2 = c[trove][j-1] + d[trove][j-1];//通过从q里移转移到d(i,j)
				d[trove][j] = min(v1,v2);
				if(i){
					c[trove][j] = c[trove^1][j];
					int cha = str1[i] - 'A';
					if(s1[cha]==i && s2[cha] > j)c[trove][j]++;
					if(e1[cha]==i && e2[cha] <= j)c[trove][j]--;
				}else if(j){
					c[trove][j] = c[trove][j-1];
					int cha = str2[j] - 'A';
					if(s2[cha]==j && s1[cha] > i)c[trove][j]++;
					if(e2[cha]==j && e1[cha] <= i)c[trove][j]--;
				}
			}
			trove ^= 1;
		}
		cout << d[trove^1][m] << endl;
	}
	return 0;
}
