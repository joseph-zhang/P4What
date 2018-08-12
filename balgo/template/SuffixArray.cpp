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
const int maxn = 1000;
const int maxm = 128;
//char s[maxn];
string s;
int sa[maxn];  //SA����
int t[maxn],t2[maxn]; //��������
int c[maxm];    //��������������
int n;
/**
*   Rank:���Ŀ�ʼ��(��׺)�ŵڼ�  Rank[i] = ?
*   SA  :�ŵڼ���(��׺)���Ŀ�ʼ  SA[i] = ? 
*   ע�������������,"��"�Ǵ�0��ʼ��,"��"�Ǵ�1��ʼ�� 
*   ע���ź�ԽС����ԽС 
*/ 
/**
*    ������ʽʵ����DA(������).��Ҫ˼��:
*    ����ÿ���ַ���ʼ�ĳ�Ϊ2^k���Ӵ��ǽ�������,���Rankֵ.
*    k��0��ʼÿ����1,��2^k����n�Ժ�ÿ���ַ�����ʼ��2^k����substr���൱�����к�׺��.         
*    ��ʱһ���Ѿ��ȳ��˴�С,��Rank�в�������ͬ��ֵ,�ó������.
*    ÿ�ε��������ϴεĽ���Ļ����Ͻ���,�Ⱥϲ�,������.�൱��ÿ��ֻҪ�Զ�Ԫ��(���)���򼴿�.
*    ע��:ÿ������ʱҪ�ȶԵڶ����ؼ�����(ʵ�����Ѿ���SA�õ�),�ٶԵ�һ����,����������ȷ������.
*    ���ַ���Χ����ʱ���û�������O(N),һ���ÿ���Ҳ��O(NlogN).
*/

//m���ַ�������,��ʾ�ַ���С��������(m+1)
void DA(int m){
	int i,*x = t,*y = t2;
	//�Գ���Ϊ1���Ӵ�������ó�SA��ʼֵ.
	for(i = 0;i < m;i++)c[i] = 0;
	for(i = 0;i < n;i++)c[x[i] = s[i]]++;
	for(i = 1;i < m;i++)c[i] += c[i-1];
	for(i = n-1;i >= 0;i--)sa[--c[x[i]]] = i;
	//����lb(N)������
	//ÿ�ο��Ƕ�Ԫ�������,�����һ�������SA,�������ε�Rank.
	//ÿ��,x(��ԭ����Rankֵ)���൱�����´�
	for(int k = 1;k <= n;k <<= 1){
		int p = 0; //λ�÷�����
		//�ȶԵڶ����ؼ�����
		//y�ǶԵڶ����ؼ����������ʱ���õ�,y��������->�ڶ�Ԫ�������е�λ��
		//��k����Եĵڶ��ؼ���Ϊ��,ֱ���ŵ�ǰ��
		for(i = n-k;i < n;i++)y[p++] = i;
		for(i = 0;i < n;i++)if(sa[i] >= k ) y[p++] = sa[i]-k; //��������
		//�ٶԵ�һ���ؼ�����
		for(i = 0;i < m;i++)c[i] = 0;
		for(i = 0;i < n;i++)c[x[y[i]]]++;
		for(i = 0;i < m;i++)c[i] += c[i-1];
		for(i = n-1;i >= 0;i--)sa[--c[x[y[i]]]] = y[i];  
		//��rank,�ӵ�y(swap֮����x)���ݴ�,��Ϊ��ʱy���ֵ�Ѿ�û����,���Բ�����
		swap(x,y);p = 1;x[sa[0]] = 0;
		for(i = 1;i < n;i++)
			x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if(p>=n)break;
		m = p;// ���ڻ��ж��ٸ���ͬ��rankֵ(Ҳ����p��ֵ)?����m,�൱������ѹ��
	}
	printf("Rank: ");
	for(i = 0;i < n;i++)printf("%d ",x[i]);//��������Rank 
	cout << endl;
}
int main(){
	cin >> s;
	n = s.size()+1;//ע�����һ��Ҫ����һ��0,���Գ���Ҫ��1 
	DA(128);
	printf("SA: ");
	//�մ�Ҳ�Ǻ�׺,������ʼλ��Ϊs.size()(��s��ȡ����),���ڵ���.
	//��SA[0] = s.size(),Rank[s.size()] = 0;
	for(int i = 0;i <= s.size();i++)printf("%d ",sa[i]);
	cout << endl;
	return 0;
}
