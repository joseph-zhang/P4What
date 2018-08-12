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
const int maxa = 2000+5;
const int maxb = 2e6+5;
int phi[maxa];
int lookup[maxa][maxa];
void phiTable(){
	memset(phi,0,sizeof(phi));
	phi[1] = 1;
	for(int i = 2;i < maxa;i++)if(!phi[i]){
		for(int j = i;j < maxa;j+=i){
			if(!phi[j])phi[j] = j;
			phi[j] = phi[j]/i*(i-1);
		}
	}
}
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
void init(){
	for(int i = 1;i < maxa;i++){
		for(int j = i;j < maxa;j++){
			lookup[i][j] = lookup[j][i] = gcd(i,j);
		}
	}
}
int main(){
	//freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int a,b;
	phiTable();
	init();
	while(cin >> a >> b){
		if(!(a||b))break;
		if(a>b) swap(a,b);
		double res = 0;
		for(int i = 1;i <= a;i++){
			res += phi[i]*(b/i);
			for(int j = 1;j <= b%i;j++){
				if(lookup[i][j]== 1)res+=1;
			}
		}
		res=res*4+4;
		double n = (a+a+1)*(b+b+1)-1;
		printf("%.7lf\n",res/n);
	}
	return 0;
}

