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
*    ����DP,�����������Ͻ��е�DP.
*    ����һ��Ĺ�����:ö������,���л���,�ϲ�.
*    ��һ��DP�����ؼ����Ƕ�����״̬�Ķ���,��Ҫע��������京�������˵�.
*    ���˼���,��Ҫ���ǽ���ѵ��,��ʶ���ֱ���.������α�������Ҫ˼�붼�������ӵ�.
*    ����ĳ�ʽ��UVa10003 �Ľ�,��������DP��Ϊ������������.
*/

/**
*    ��ľ��(UVa10003):ľ������ΪL(L<1000),������n(n<50)���е�.
*    ��˳�����,��Ϊa[i]: �е���->�е���ľ���ϵ�λ��
*    ����Ҫ��ľ���г�n+1��,����С����.(�и����:���жεĳ���)
*    ״̬��ָ��: �и�ľ����[i,j]����С����,i<j;
*    ת�Ʒ���: d(i,j) = min{d(i,k),d(k,j)}+a[j]-a[i], k���е�i���е�j֮����е�.
*    �߽�: d(i,i+1) = 0;
*    ʵ��ʱ����ö��������ƾͿ�����.
*/
int L,N;
int pole[52]; //���е�λ��
int d[52][52];
int main(){
	while(cin >> L){
		if(!L)break;
		cin >> N;
		for(int i = 1;i <= N;i++)scanf("%d",&pole[i]);
		pole[0] = 0;pole[N+1] = L;
		memset(d,0,sizeof(d));
		for(int i = N;i >= 0;i--){
			for(int j = i+1;j <= N+1;j++){
				d[i][j] = INF;
				if(j == i+1){d[i][j] = 0;continue;}
				int costs = pole[j] - pole[i];
				for(int k = i + 1;k < j;k++)
					d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
				d[i][j] += costs;
			}	
		}
		printf("The minimum cutting is %d.\n",d[0][N+1]);
	}
	return 0;
}
