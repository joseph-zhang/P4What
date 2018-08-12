#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib> 
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
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

const int maxn = 1e5;
const int maxm = 1e4;
int seq[maxn+2];
bool deci[maxn+2];
char drop[20];
int n,m;
int t;
int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	scanf("%d",&t);
	while(t--){
		gets(drop);
		cin >> n >> m;
		int cnt = 0;
		for(int i = 0;i < n;i++)cin >> seq[i];
		for(int i = 0;i < n;i++)deci[i] = false;
		sort(seq,seq+n);
		for(int i = 0;i < n;i++){
			if(deci[i])continue;
			int p = n-1;
			while(deci[p]||seq[p]+seq[i]>m){p--;if(p==i)break;}
			deci[i] = deci[p] = true;
			cnt++;
		}
		cout << cnt << endl;
		if(t)printf("\n");
	}
	return 0;
}
