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
#define LL long long 
#define sys std::ios::sync_with_stdio(false);
using namespace std;
LL primediv[8000];
LL num[8000];
int cnt = 0;
LL A,B;
LL mulm(LL a,LL b,LL m){
	LL x = 0;
	for(;b;b >>= 1){
		if(b&1) x = (x+a)%m;
		a = (a+a)%m;
	}
	return x;
}
LL powm(LL a,LL b,LL m){
	LL x = 1;
	for(;b;b >>=1){
		if(b&1) x = mulm(x,a,m);
		a = mulm(a,a,m);
	}
	return x;
}

void getdiv(LL a){
	for(int i = 2;i*i <= a;i++){
		int count = 0;
		if(a%i) continue;
		while(a%i == 0){
			a /= i;
			count++;
		}
		primediv[cnt] = i;
		num[cnt++] = count;
	}
	if(a > 1){
		primediv[cnt] = a;
		num[cnt++] = 1;
	}
}

LL sloveone(LL p,LL n){
	return (powm(p,n*B+1,(p-1)*9901)-1)/(p-1);
}
int main(){	
	cin >> A >> B;
	getdiv(A);
	LL res = 1;
	for(int i = 0;i < cnt;i++){
		res = mulm(res,sloveone(primediv[i],num[i]),9901);	
	}
	cout << res << endl;
	return 0;
}

