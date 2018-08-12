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
*    ����Щʱ��,DP��״̬�Ƚϸ���,�������ü�������ʾ��һȺλ����Ϣ,����������һ��λ��.
*    ���������ֲ����ܿ�����ʮά����������ʾ״̬(������),���ʱ��Ҫ����������������ʾ״̬.
*    ���λ�������Ƚ�Сʱ,���Կ���״̬ѹ��,��λ������ʾ״̬.
*    ʹ��״̬ѹ���ֶε�DP����״ѹDP.
*    ʹ�������ֶ���Ҫ�Ƚ�ǿ��λ������.
*    ��һ��������˵����˼��.
*/

/**
*    ����:��N*M��(0-1)Grid������,0��������,1��������.
*    Ϊ��֤���߳���,ÿ������Χ�������������������ڲ�����.
*    ��һ��Grid��������ֶ�����.
*    ˼·:
*    ÿһ����ѡ����λ��������,�������λ����Ϣ,��λ����ʾ.
*    ״̬s(r,i,j): ��r�е�����״̬i�͵�r-1�е�����״̬j��
*    ָ��dp(r,i,j): ����s(r,i,j),1~r �е�Grid������ֶ�����.
*    ת�Ʒ���: dp(r,i,j) = max(dp(r-1,j,k))+cnt(i) ,ÿһ��r�����п��ܵ�i��j,k.
*    ��������һ�м�������λ�ö��ɷ�,���ڲ���ͻ�ķŷ���ps��,�����Ǵ���pres[]��,�����ŷ����˶���������cnt[];
*/
const int maxn = 20,maxm = 8;
int N,M;
int ps = 0;
int grid[maxn]; //��GridҲ��λ������
int dp[maxn][1<<maxm][1<<maxm];
//Ԥ����,���pres[]��cnt[]
void init(){
	for(int i = 0;i < (1 << M);i++){
		if( (i&(i<<1)) || (i&(i<<2)) ) continue;//���ڳ�ͻ�Ͳ���
		pres[ps++] = i;
		int tmp = i;
		for(;tmp;tmp&=(tmp-1)) cnt[ps-1] += 1; //��ѭ������tmp���ж��ٸ�1
	}
}
int dp(){
	memset(dp,0,sizeof(dp));
	//dp����
	for(int r = 1;r <= N;i++){
		for(int i = 0;i < ps;i++){
			if(pres[i]&grid[r]) continue; //��grid��ͻ�Ͳ���
			for(int j = 0;j < ps;j++){
				for(int k = 0;k < ps;k++){
					if( pres[i]&pres[j] || pres[i]&pres[k] )continue;//r�к������ж����ܳ�ͻ.
					dp[r][i][j] = max(dp[r][i][j],dp[r-1][j][k]+cnt[i]);
				}
			}
		}
	}
	int res = 0;
	for(int i = 0;i < ps;i++)
		for(int j = 0;j < ps;j++)
			res = max(res,dp[N][pres[i]][pres[j]]);
	return res;
}

