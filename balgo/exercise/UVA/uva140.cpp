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
#define sys std::ios::sync_with_stdio(false);
#define LL long long
using namespace std;
char input[1000];
bool G[12][12];
int pos[12];
int seq[12];
int res[12];
int getNum[256];
char getch[10];
int N,best;
void backtracking(int cur,int band){
	if(cur == N){
		if(band < best){
			memcpy(res,seq,sizeof(seq));
			best = band;return;
		}
	}
	if(band >= best) return;
	for(int i = 1;i <= N;i++){
		int cnt = 0;
		int b = band;
		if(pos[i] == -1 ){
			seq[cur] = i;
			pos[i] = cur;
			for(int j = 1;j <= N;j++){
				if(G[i][j]){ 
					if(pos[j]!= -1)b = max(b,pos[i]-pos[j]);
					else cnt++;
				}
			}
			if(cnt >= best){pos[i] = -1;continue;}
			backtracking(cur+1,b);
			pos[i] = -1;
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	while(1){
		scanf("%s",input);
		if(input[0] == '#')break;
		N = 0;memset(G,0,sizeof(G));
		memset(pos,-1,sizeof(pos));
		memset(getNum,0,sizeof(getNum));
		for(int i = 'A';i <= 'Z';i++){
			if(strchr(input,i) != NULL){
				getNum[i] = ++N;
				getch[N] = i;
			}
		}
		int p = 0,q = 0;
		int len = strlen(input);
		while(p < len && q < len){
			while(input[p] != ':' && p < len)p++;
			while(input[q] != ';'&& q < len)q++;
			int u = getNum[input[p-1]];
			for(int i = p+1;i < q;i++){
				int v = getNum[input[i]];
				G[u][v] = G[v][u] = true;
			}
			p++;q++;
		}
//		for(int i = 1;i <= N;i++){
//			for(int j = 1;j <= N;j++)cout << G[i][j] << " ";
//			cout << endl;
//		}
		best = INF;
		backtracking(0,0);
		for(int i = 0;i < N;i++)
			printf("%c ",getch[res[i]]);
		cout << "-> " << best << endl;
	}
	return 0;
}

