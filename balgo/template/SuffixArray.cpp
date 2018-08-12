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
int sa[maxn];  //SA数组
int t[maxn],t2[maxn]; //辅助数组
int c[maxm];    //基数排序用数组
int n;
/**
*   Rank:从哪开始的(后缀)排第几  Rank[i] = ?
*   SA  :排第几的(后缀)从哪开始  SA[i] = ? 
*   注意在这个样例中,"哪"是从0开始的,"几"是从1开始的 
*   注意排号越小串就越小 
*/ 
/**
*    下述程式实现了DA(倍增法).主要思想:
*    对以每个字符开始的长为2^k的子串们进行排序,求出Rank值.
*    k从0开始每次增1,当2^k大于n以后每个字符串开始的2^k长的substr就相当于所有后缀了.         
*    此时一定已经比出了大小,即Rank中不再有相同的值,得出最后结果.
*    每次的排序都在上次的结果的基础上进行,先合并,再排序.相当于每次只要对二元组(序对)排序即可.
*    注意:每轮排序时要先对第二个关键字排(实际上已经由SA得到),再对第一个排,这样才是正确的排序.
*    当字符范围不大时可用基数排序O(N),一般用快排也可O(NlogN).
*/

//m是字符集参数,表示字符大小都不超过(m+1)
void DA(int m){
	int i,*x = t,*y = t2;
	//对长度为1的子串们排序得出SA初始值.
	for(i = 0;i < m;i++)c[i] = 0;
	for(i = 0;i < n;i++)c[x[i] = s[i]]++;
	for(i = 1;i < m;i++)c[i] += c[i-1];
	for(i = n-1;i >= 0;i--)sa[--c[x[i]]] = i;
	//进行lb(N)轮排序
	//每次考虑二元组的排序,算出下一次所需的SA,再算出这次的Rank.
	//每次,x(即原来的Rank值)都相当于是新串
	for(int k = 1;k <= n;k <<= 1){
		int p = 0; //位置分配器
		//先对第二个关键字排
		//y是对第二个关键字做排序的时候用的,y：排序编号->在二元组序列中的位置
		//后k个序对的第二关键字为零,直接排到前面
		for(i = n-k;i < n;i++)y[p++] = i;
		for(i = 0;i < n;i++)if(sa[i] >= k ) y[p++] = sa[i]-k; //遍历排名
		//再对第一个关键字排
		for(i = 0;i < m;i++)c[i] = 0;
		for(i = 0;i < n;i++)c[x[y[i]]]++;
		for(i = 0;i < m;i++)c[i] += c[i-1];
		for(i = n-1;i >= 0;i--)sa[--c[x[y[i]]]] = y[i];  
		//算rank,扔到y(swap之后是x)里暂存,因为此时y里的值已经没用了,所以不担心
		swap(x,y);p = 1;x[sa[0]] = 0;
		for(i = 1;i < n;i++)
			x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		if(p>=n)break;
		m = p;// 现在还有多少个不同的rank值(也就是p的值)?设置m,相当于做了压缩
	}
	printf("Rank: ");
	for(i = 0;i < n;i++)printf("%d ",x[i]);//看看最后的Rank 
	cout << endl;
}
int main(){
	cin >> s;
	n = s.size()+1;//注意后面一定要多添一个0,所以长度要加1 
	DA(128);
	printf("SA: ");
	//空串也是后缀,设其起始位置为s.size()(在s中取不到),排在第零.
	//即SA[0] = s.size(),Rank[s.size()] = 0;
	for(int i = 0;i <= s.size();i++)printf("%d ",sa[i]);
	cout << endl;
	return 0;
}
