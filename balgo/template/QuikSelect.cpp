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

/**
*    快速选择(QuickSelcet):思想和QuickSort完全一致,属于分治范型.
*    划分(partition)阶段,随机选取轴避免平均最坏情形.
*/

int N;
inline void swap(int *arr,int i,int j){
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}
//划分过程,区间是arr:[L,R];
int partition(int *arr,int L,int R){
	int indi = L+rand()%(R-L+1);
	swap(arr,indi,L);
	int val = arr[L];
	int i = L,j = R+1;
	while(true){
		while(++i < R && arr[i] < val);
		while(--j > L && arr[j] > val);
		if(i >= j)break;
		swap(arr,i,j);
	}
	swap(arr,L,j);
	return j;
}
//找第k小的元素
int select(int *arr,int L,int R,int k){
	if(L >= R)return arr[R];
	int i = partition(arr,L,R);
	int cnt = i-L+1;//看看是第几小的
	if(cnt == k)return arr[i];
	return cnt > k?select(arr,L,i-1,k):select(arr,i+1,R,k - cnt);
}
int main(){
	int n;cin >> n;
	srand((unsigned)time(NULL));//设置种子
	while(n--){
		printf("how many numbers in your sequence?\n");
		cin >> N;
		int p[N+2];
		printf("Now give me %d numbers.\n",N);
		for(int i = 0;i < N;i++)cin >> p[i];
		int k = select(p,0,N-1,(N+1)>>1);//找出中位数
		printf("the median of your sequence is: %d\n",k);
	}
	return 0;
}
