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
#define ULL unsigned LL
using namespace std;
const LL M = 10001;
const LL maxn = 205;
LL T,arr[maxn];
void exEuclid(LL a,LL b,LL& d,LL& x,LL& y){
	if(!b){d = a;x = 1;y = 0;}
	else{
		exEuclid(b,a%b,d,y,x);
		y-=x*(a/b);
	}
}
void solve(){
	for(int a = 0;a < M;a++){
		LL A1 = arr[3]-a*a*arr[1];
		LL A2 = (a+1);
		LL g,x,y;
		exEuclid(A2,M,g,x,y);
		if(A1%g)continue;
		LL b = x*A1/g;
		bool done = true;
		for(int i = 2;i <= (T<<1);i+=2){
			arr[i] = (arr[i-1]*a+b)%M;
			if(i+1 <= T<<1 && arr[i+1]!=(arr[i]*a+b)%M){
				done = false;
				break;
			}
		}
		if(done)return;
	}
}
int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	while(cin >> T){
		for(LL i = 1;i <= (T<<1)-1;i+=2)scanf("%d",&arr[i]);
		if(T>1)solve();
		else{printf("0\n");continue;}
		for(int i = 2;i <=T<<1;i+=2)printf("%d\n",arr[i]);
	}
	return 0;
}

