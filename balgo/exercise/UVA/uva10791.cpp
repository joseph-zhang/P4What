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
struct node{
	int p,num;
	node(){}
	node(int p_,int n_):p(p_),num(n_){}
};
const LL maxn = 1 << 31;
vector<node> divs;
void primeDiv(int N){
	for(int d = 2;d <= (int)sqrt(N+0.5);d++){
		int tmp = 0,cnt = 0;
		if(!(N%d))tmp = d;
		else continue;
		while(!(N%d)){N /= d;++cnt;}
		divs.push_back(node(tmp,cnt));
	}
	if(N > 1)divs.push_back(node(N,1));
}
LL fastPow(int a,int n){
	LL res = 1;
	for(;n;n>>=1){
		if(n&1)res=res*a;
		a *= a;
	}
	return res;
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int kase = 0,n;
	while(cin >> n){
		if(!n)break;
		if(n == 1){printf("Case %d: 2\n",++kase);continue;}
		divs.clear();
		primeDiv(n);
		LL ans = 0;
		for(int i = 0;i < divs.size();i++){
		//	cout << divs[i].p << " " << divs[i].num << endl;
			ans += fastPow(divs[i].p,divs[i].num);
		}
		if(divs.size()==1)ans+=1;
		printf("Case %d: %ld\n",++kase,ans);
	}
	return 0;
}
