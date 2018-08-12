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
const int maxn = 50;
int songs[maxn+5];
int n,t;
int d[maxn*180+678+5];
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int time;cin >> time;
	int kase = 0;
	while(time--){
		scanf("%d%d",&n,&t);
		int ans = 0;
		for(int i = 0;i < n;i++)scanf("%d",&songs[i]);
		memset(d,-1,sizeof(d));
		d[0] = 0;
		for(int i = 0;i < n;i++){
			for(int j = t-1;j >= songs[i];j--){
				if(	d[j-songs[i]] >= 0)
					d[j] = max(d[j],d[j-songs[i]]+1);
				ans = max(ans,d[j]);
			}
		}
		printf("Case %d: ",++kase);
		for(int j = t-1;j >= 0;j--){
			if(d[j] == ans){
				cout << ans+1 << " " << j+678 << endl;
				break;
			}
		}
	}	
	return 0;
}

