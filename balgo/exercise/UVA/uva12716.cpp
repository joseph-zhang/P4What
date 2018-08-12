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
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
const int maxn = 30000000+5;
const int M = 30000000;
int cnt[maxn],sum[maxn];
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
void init(){
	memset(cnt, 0, sizeof(cnt));
	for(int c = 1;c <= M;c++){
		for(int a = c+c;a <= M;a += c){
			int b = a-c;
			if(c == (a^b))cnt[a]++;
		}
	}
	sum[0] = 0;
	for(int i = 1;i <= M;i++)sum[i]=sum[i-1]+cnt[i];
}
int main(){
	int T;cin >> T;
	int kase = 0;
	init();
	while(T--){
		int n;scanf("%d",&n);
		printf("Case %d: %d\n",++kase,sum[n]);
	}
	return 0;
}

