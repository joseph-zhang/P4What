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
#define LL long long
using namespace std;
LL pows[25];
int N;
void init(){
	pows[0] = 1;
	for(int i = 1;i <= 23;i++){
		pows[i] = pows[i-1]*3;
	//	cout << pows[i] << endl;
	}
}
int gcd(int a,int b){
	return b == 0?a:gcd(b,a%b);
}
int main(){
	init();
	while(cin >> N){
		if(N == 0) {cout << 0 << endl;continue;}
		if(N == -1)break;
		LL res = 0;
		for(int i = 1;i <= N;i++)
			res += pows[gcd(i,N)];
		LL b = 0;
		if(N%2) b = N*pows[(N+1)/2];
		else b = N/2 * (pows[N/2+1]+pows[N/2]);
		cout << (res+b)/2/N << endl;
	}
	return 0;
}
   
