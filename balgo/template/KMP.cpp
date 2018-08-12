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
*    KMP演算法是AC自动机的铺垫,用于字符串匹配。
*    朴素的算法复杂度为O(m(n-1)),尽管对于随机数据表现很好,但很多情况下很慢。
*    (尤其是对于特别设计过的数据,OJ)
*    一般来说MP(Morris-Pratt)已经足够,下面就此给出程式。
*    KMP利用"失配"进行状态转移,有状态机的意味.
*    先用"失配函数"处理模板串,再进行匹配过程.
*/

/*处理模板串P,思想是用自己匹配自己*/
/*f是递推数组,记录失配了该怎么转移*/
void failure(char* P,int* f){
	int m = strlen(P);
	f[0] = 0;f[1] = 0; //递推边界
	for(int i = 1;i < m;i++){
		int j = f[i];
		while(j && P[i]!=P[j]) j = f[j]; //沿失配边不断往回走
		f[i+1] = (P[i] == P[j])?(j+1):0;
	}
}
/*主程,返回匹配的起始位置*/
int matching(char* T,char* P,int* f){
	int n = strlen(T),m = strlen(P);
	failure(P,f);
	int j = 0; //模板串指示器
	for(int i = 0;i < n;i++){
		while(j && P[j]!=T[i]) j = f[j];
		if(P[j] == T[i]) j++;
		if(j == m) return i-m+1;
	}
	return -1;
}

int main(){
	char T[20],P[20];
	int f[22];
	while(cin >> T){
		cin >> P;
		cout << matching(T,P,f) << endl;
		for(int i = 0;i < strlen(P)+1;i++)cout << f[i] << " ";
		printf("\n\n");
	}
	return 0;
}


