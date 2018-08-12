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

/**
*    LCP(最长公共前缀),可以利用SA数组得到.
*    定义height[i]数组为Suffix(SA[i-1])与Suffix(SA[i])的最长公共前缀长度.
*    得到height后,任意两后缀的LCP相当于一次RMQ(min)查询:
*        LCP(suffix(j),suffix(k)) = RMQ(height,Rank[j]+1,Rank[k]). Rank[j] < Rank[k]
*    定义辅助数组h[i] = height[Rank[i]],则一定有 h[i] >= h[i-1] + 1;
*    h[i]: suffix(i)与排在它前一个的后缀之间的LCP长度.
*    可以利用这个性质递推出height数组的值.
*    注：height[0],height[1] 一定都是0.
*/

string s;
int sa[maxn],Rank[maxn],height[maxn];  //SA数组
int d[maxn][maxn]; //RMQ的dp数组
int t[maxn],t2[maxn]; //辅助数组
int c[maxm];    //基数排序用数组
int n;

void DA(int m){
	int i,*x = t,*y = t2;
	for(i = 0;i < m;i++)c[i] = 0;
	for(i = 0;i < n;i++)c[x[i] = s[i]]++;
	for(i = 1;i < m;i++)c[i] += c[i-1];
	for(i = n-1;i >= 0;i--)sa[--c[x[i]]] = i;
	for(int k = 1;k <= n;k <<= 1){
		int p = 0; //位置分配器
		for(i = n-k;i < n;i++)y[p++] = i;
		for(i = 0;i < n;i++)if(sa[i] >= k ) y[p++] = sa[i]-k; //遍历排名
		for(i = 0;i < m;i++)c[i] = 0;
		for(i = 0;i < n;i++)c[x[y[i]]]++;
		for(i = 0;i < m;i++)c[i] += c[i-1];
		for(i = n-1;i >= 0;i--)sa[--c[x[y[i]]]] = y[i];  
		swap(x,y);p = 1;x[sa[0]] = 0;
		for(i = 1;i < n;i++)
			x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if(p>=n)break;
		m = p;
	}
	printf("Rank: ");
	for(i = 0;i < n;i++)printf("%d ",x[i]);
	for(int i = 0;i < n;i++) Rank[i] = x[i];
	cout << endl;
}
void getHeight(){
	int i,j,k = 0;
	for(i = 0;i < n;i++){
		if(k)k--;
		j = sa[Rank[i]-1];
		while(s[i+k]==s[j+k])k++;
		height[Rank[i]] = k;
	}
}
void initRMQ(int* A,int num){
	for(int i = 0;i < num;i++)d[i][0] = A[i];
	for(int j = 1;(1 << j) <= num;j++){
		for(int i = 0;(i+(1<<j)-1) < num;i++){
			d[i][j] = min(d[i][j-1],d[i+(1<<(j-1))][j-1]); 
		}
	}
}
int RMQ(int u,int v){
	if(u > v)swap(u,v);
	int k = (int)(log(v-u+1.0)/log(2.0));
	return min(d[u][k],d[v-(1<<k)+1][k]); 
}
int QureyLCP(int u,int v){
	if(Rank[u] > Rank[v]) swap(u,v);
	return RMQ(Rank[u]+1,Rank[v]);
}
int main(){
	cin >> s;
	n = s.size()+1;//注意后面一定要多添一个0,所以长度要加1 
	DA(128);
	printf("SA: ");
	for(int i = 0;i <= s.size();i++)printf("%d ",sa[i]);
	cout << endl;
	getHeight();
	printf("Height: ");
	for(int i = 0;i < n;i++)printf("%d ",height[i]);
	cout << endl;
	
	initRMQ(height,n);
	int m,pos1,pos2;
	printf("How many times to qurey? ");
	scanf("%d",&m);
	printf("Give me your qurey as -> pos1 pos2\n");
	for(int i = 0;i < m;i++){
		cin >> pos1 >> pos2;
		printf("the length of LCP(suffix(%d),suffix(%d)) is: ",pos1,pos2);
		cout << QureyLCP(pos1,pos2) << endl;
	}
	return 0;
}

