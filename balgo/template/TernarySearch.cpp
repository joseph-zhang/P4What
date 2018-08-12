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
*    对于映射 y = f(x),三分法可用于寻找 x:[A,B] 区间内的极值(或说单峰函数最值)。
*    以极大值为例,对于[A,B]上两点 m1, m2: 
*        (1)若 f(m1) < f(m2),则极大值必位于区间 (m1,B]内；
*        (2)若 f(m1) > f(m2),则极大值必位于区间 [A,m2)内;
*        (3)若 f(m1) = f(m2),则极大值必位于区间 [m1,m2]内;
*    同理可对寻找极小值的情况做分析。
*    下面编写的程式是以整数函数(映射)为基础的,若是浮点数,需要设置阈值.
*/

int findMin(int* data,int sz){
	int left = 0;int right = sz-1;
	int m1 = left,m2 = right;
	while(left < right){
		m1 = left + (right - left)/3;
		m2 = right - (right-left)/3;
		int y1 = data[m1],y2 = data[m2];
		if(y1 > y2) left = m1+1;
		else if(y1 < y2) right = m2-1;
		else{
			left = m1;right = m2;
			if(left == right-1) break;
		}
	}
	return left;
}

int findMax(int* data,int sz){
	int left = 0,right = sz-1;
	int m1 = left,m2 = right;
	while(left < right){
		m1 = left+ (right-left)/3;
		m2 = right - (right-left)/3;
		int y1 = data[m1],y2 = data[m2];
		if(y1 > y2) right = m2-1;
		else if(y1 < y2) left = m1+1;
		else{
			left = m1;right = m2;
			if(left = right-1)break;
		}
	}
	return left;
}
int main(){

	printf("How many dots in your function(map-table)? ");
	int n;cin >> n;
	printf("Now you should give me your mapping table.\n");
	int data[n+2];
	for(int i = 0;i < n;i++)cin >> data[i];
	int p1 = findMax(data,n);
	int p2 = findMin(data,n);
	printf("the max value located at %d,the value is %d\n",p1,data[p1]);
	printf("the min value located at %d,the value is %d",p2,data[p2]);
	return 0;
}
