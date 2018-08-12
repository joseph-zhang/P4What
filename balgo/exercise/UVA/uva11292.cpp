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
int N,M;
int head[20020],knight[20020];
int main(){
	while(cin >> N >> M){
		if(!(N||M)) break;
		for(int i = 0;i < N;i++)scanf("%d",&head[i]);
		for(int j = 0;j < M;j++)scanf("%d",&knight[j]);
		sort(head,head+N);
		sort(knight,knight+M);
		int p = 0,res = 0;;
		for(int i = 0;i < N;i++){
			if(p >= M){res = -1;break;}
			while(knight[p] < head[i])p++;
			res += knight[p++];
		}
		if(res==-1) cout << "Loowater is doomed!" << endl;
		else cout << res << endl;
	}	
	return 0;
} 
