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

bool sieve[maxn];
//埃式筛打表(埃拉托斯特尼筛)O(NlogN)
void Erasieve(){
	sieve[0] = sieve[1] = true;
	for(int i = 2;i <= (int)sqrt(n+0.5);i++)if(!sieve[i]){
		for(int j = i*i;j <= n;j+=i)
			sieve[j] = true;
	}
}
//线性筛打表O(N)
void linearSieve(){ 
	sieve[0] = sieve[1] = true;
	vector<int> primes;
	for(int i = 2;i < N;i++){
		if(!sieve[i])primes.push_back(i);
		for(int j = 0;i*primes[j] < N;j++){
			sieve[i*primes[j]] = true;
			if(!(i%primes[j]))break;
		}
	}
}

//欧几里得演算法 O(logN)
int gcd(int a,int b){  
	return b == 0?a:gcd(b,a%b);
}

//尼考曼彻斯演算法
//(很慢,实作价值很低,掌握思想即可)
//(而且一般写成非递归的,不然数比较大的时候会栈溢出)
int gcd(int a,int b){
	if(a==b)return a;
	return (a>b)?gcd(a-b,b):gcd(a,b-a);
}

//最小公倍数
int lcm(int a,int b){
	return a/gcd(a,b)*b;
}
//扩展欧几里得: 求gcd(a,b)组合表示,ax+by=gcd(a,b)
//整个过程相当于欧几里得演算法正反各走一遍,正着走求出gcd,回来时不断代换展开.
//注意返回时每次x和y轮流被代换展开,所以要每次交换
void exEuclid(int a,int b,int& d,int& x,int& y){
	if(!b){d = a;x = 1;y = 0;}
	else{
		exEuclid(b,a%b,d,y,x);
		y -= x*(a/b);
	}
}
//质因数分解
void primeDiv(int n){
	for(int d = 2;d <= (int)sqrt(n+0.5);d++){
		while(!(n%d)){
			n/=d;
			//cout << d << endl;
		}
	}
	if(n > 1)cout << n << endl;//n is a Prime
}
//快速幂(可扩展为矩阵快速幂)
LL fastPow(int a,int n){
	LL res = 1;
	for(;n;n >>= 1){
		if(n&1)res = (res*a);
		a = a*a;
	}	
	return res;
} 
//快速积取模(逐次倍增法)
LL mulm(LL a,LL b,LL m){ //O(logN)
	LL res = 0;
	a = a%m;
	for(;b;b>>=1){
		if(b&1)res = (res+a)%m;
		a = (a+a)%m;
	}
	return res;
}
//快速幂取模(逐次平方法)
LL powm(LL a,LL b,LL m){ //O(logN)
	LL res = 1;
	a = a%m;
	for(;b;b >>= 1){
		if(b&1)res = res*a%m;
		a = a*a%m;
	}
	return res;
}
//a的幂次b超过longlong，非常大的时候的幂取模
LL superPowm(LL a,vector<int>& b,LL m){
	int sz = b.size();
	LL ans = 1;
	for(int i = sz-1;i>=0;i--){
		ans = ans*powm(a,b[i],m)%m;
		a = powm(a,10,m);
	}
	return ans;
}
//欧拉函数-Phi 
int eulerPhi(int n){
	//if(!sieve[n])return n-1;n已经是素数
	int ans = n;
	//这里实际上做的是质(素)因数分解
	for(int i = 2;i<=(int)sqrt(n+0.5);i++){
		if(!(n%i)){ 
			ans = ans/i*(i-1); //先做除法防溢出
			while(!(n%i))n/=i;
		}
	}
	if(n>1)ans = ans/n*(n-1);//若n为素数
	return ans;
}
//打phi值表
int phi[maxn];
void phiTable(int n){ 
	memset(phi,0,sizeof(phi));
	phi[1] = 1;
	//方法和埃氏筛类似
	for(int i = 2;i <= n;i++)if(!phi[i]){//i没被筛掉,是素数
		for(int j = i;j <= n;j+=i){//这个素数i是哪些数的素因子(包括自己)
			if(!phi[j])phi[j] = j;
			phi[j] = phi[j]/i*(i-1);
		}
	}
}
//模逆元
LL inv(LL a,LL n){
	LL d,x,y;
	exEuclid(a,n,d,x,y);
	return d == 1?(x+n)%n:-1;//gcd(a,n)不是一就无解
}
//中国剩余定理(孙子定理)
LL china(int n,int* a,int* m){
	LL M = 1,y,res = 0;
	for(int i = 0;i < n;i++)M*=m[i];
	for(int i = 0;i < n;i++){
		LL Mi = M/m[i];
		LL ti = inv(Mi,m[i]);
		res = (res+ti*Mi*a[i])%M;
	}
	return (res+M)%M;
}

//O(n)组合数公式C(n,k) = n!/(k!*(n-k)!)
long long comb(int n, int k) {
  if(k < n-k) k = n-k;
  long long ans = 1;
  for(int i = k+1; i <= n; i++) ans *= i;
  for(int i = 1; i <= n-k; i++) ans /= i;
  return ans;
}
int combtable[maxn][maxn];
//O(n^2)组合数打表求出整个n阶pascal三角:递推式 C(n,k) = C(n-1,k) + C(n-1,k-1)
void comb(int n){
	memset(combtable,0,sizeof(combtable));
	for(int i = 0;i <= n;i++){
		combtable[i][0] = 1;
		for(int j = 1;j <= i;j++)
			combtable[i][j] = combtable[i-1][j] + combtable[i-1][j-1];
	}
}
//O(n)组合数打表求出pascal三角的第n行:递推式 C(n,k) = (n-k+1)/k * C(n,k-1)
void comb(int n){
	memset(combtable,0,sizeof(combtable));
	combtable[n][0] = 1;
	for(int i = 1;i <= n;i++) 
		combtable[n][i] = (n-i+1) * combtable[n][i-1] / i;
}
