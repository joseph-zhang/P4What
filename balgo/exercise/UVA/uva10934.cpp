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
#define Uint unsigned int
using namespace std;
const int maxk = 100,maxn = 63;
unsigned long long d[maxk+1][maxn+1];
unsigned long long k,n;
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	memset(d,0,sizeof(d));
	for(int i = 1;i <= maxk;i++){
		for(int j = 1;j <= maxn;j++){
			d[i][j] = d[i-1][j-1] + 1 + d[i][j-1];
		}
	}
	while(scanf("%lld%lld",&k,&n)!=EOF){
		if(!k)break;
		int ans = -1;
		for(int i = 1;i <= maxn;i++)
			if(d[k][i] >= n){ans = i;break;}
		if(ans < 0)cout << "More than 63 trials needed." << endl;
		else cout << ans << endl;
	}
	return 0;
}
