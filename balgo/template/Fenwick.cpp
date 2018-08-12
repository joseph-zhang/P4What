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
const int N = 10;
int fenwick[N+2]; 
int arr[N+2];

//获取到最低位
inline int lowbit(int x){return x&(-x);}

//不断地往回走
int sum(int pos){
	int res = 0;
	while(pos){
		res += fenwick[pos];
		pos -= lowbit(pos);
	}
	return res;
}
//不断地往前走
void add(int pos,int num){
	while(pos <= N){
		fenwick[pos]+= num;
		pos += lowbit(pos);
	}
}
//更新
void update(int pos,int num){
	int old = arr[pos];
	while(pos <= N){
		fenwick[pos] -= old;
		fenwick[pos] += num;
		pos += lowbit(pos);
	}
}
//查询
int query(int L,int R){
	if(!L)return sum(R);
	else return sum(R) - sum(L-1);
}
int main(){
	memset(fenwick,0,sizeof(fenwick));
	int a,b,c;cin >> a >> b >> c;
	printf("now you should give me the sequence,10 number\n");
	for(int i = 1;i <= N;i++){
		cin >> arr[i];
		add(i,arr[i]);
	}
	printf("Now,query %d times.\n",a);
	while(a--){
		int l,r;cin >> l >> r;
		printf("get summation of %d~%d: %d\n",l,r,query(l,r));
	}
	cout << endl;
	printf("Now,modify where you want..\n");
	while(b--){
		int p,n;cin >> p >> n;
		update(p,n);
		arr[p] = n;
		printf("updating succesfully!\n");
	}
	cout << endl;
	printf("Now query again,%d times.\n",c);
	while(c--){
		int l,r;cin >> l >> r;
		printf("get summation of %d~%d: %d\n",l,r,query(l,r));
	}
	return 0;
}
