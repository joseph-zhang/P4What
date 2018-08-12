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

/**
*    位集(bitset)的相关技巧在状态压缩中很有用
*    这里仅给出和集合相关的一点用法.当元素较少时用二进制表示比较方便.
*    空集: 0
*    集合{0,1,2,...,n-1}: (1<<n)-1
*    判断第i个元素是否在集合内: (Set>>i)&1 或者 Set&(1<<i)
*    向集合中加入第i个元素: Set|(1<<i)
*    从集合中删去第i个元素: Set&~(1<<i)
*    两集合的并集: Set1 | Set2
*    两集合的交集: Set1 & Set2
*/

/*按位印出集合状态,集合的位集表示是Set,共有n位*/
void print(int Set,int n){
	cout << '{';
	for (int i=n-1; i>=0;i--){
		if (Set & (1 << i)) cout << 1;
		else cout << 0;
	}
	cout << '}' << '\n';
}
/*枚举{0,1,2,...,n-1}的所有子集*/
void enumer1(int n){
	for(int i = 0;i < 1 << n;i++){
		print(i,n);
	}
}
/*
  枚举{0,1,2,...,n-1}的所有大小为k的子集
  按照字典序升序地顺序给出
*/
void enumer2(int n,int k){
	int comb = (1<<k)-1;//按照字典序的话,最小子集是(1<<k)-1
	while(comb < 1<<n){
		int x = comb & (-comb);
		int y = comb + x;
		comb = ((comb&~y)/x >> 1)|y;
	}
}
/*枚举所有子集*/
void enumrate(int Set,int n){
	for(int i = Set;i;i = (i-1)&Set)
		print(i,n);
	print(0,n);
}
/*计算有多少个1(集合计数)*/
int calc(int Set){
	int cnt = 0;
	for(;Set;Set &= (Set-1))cnt++;
	return cnt;
}

int main(){
	int n,t;
	printf("the number of bits of your bitset? ");
	scanf("%d",&n);
	printf("How many times do you want to print? ");
	scanf("%d",&t);
	printf("Now give me set presented as a number.\n");
	while(t--){
		printf("input your set: ");
		int Set;cin >> Set;
		enumrate(Set,n);
		cout << endl;
	}
	return 0;
}




