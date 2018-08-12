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
LL ssum(int a1,int d,int num){
	return (long long)(a1+a1-num*d)*(num+1)/2;
} 
int main(){
	int k,n;
	while(cin >> n >> k){
		LL res = 0;
		int i = 1;
		while(i <= n){
			int q = k%i,p = k/i;
			int cnt = n-i;
			if(p>0)cnt = min(cnt,q/p);
			res+=ssum(q,p,cnt);
			i+=cnt+1;
		}
		printf("%ld\n",res);
	}	
	return 0;
}
