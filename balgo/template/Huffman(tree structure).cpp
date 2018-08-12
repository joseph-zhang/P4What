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
*    Huffman树:Huffman编码的二叉树树形结构;
*    主要思想和值计算完全一致,只是将内部数据组织表现出来.
*    预先统计字符频率,并建立码表,才能顺利压缩.
*    码和码表都需要存储下来,才能顺利解压.
*    程式实现了压缩和解压过程,并达成码表长度最小.
*    下列示例程式假设最多有256种字符,因而在结点聚合时(最多)又生成256-1个新节点.
*/

int freq[256*2-1];		// 各种字符的频率(或说各节点的权重)
int parent[256*2-1];	// optimal code tree
int Left[256*2-1];		// optimal code tree
int Right[256*2-1];		// optimal code tree
int bit[256*2-1];		// optimal code tree
int cnt[256*2-1];		// 各结点涵盖的树叶数量
int length[256*2-1];	// 各结点涵盖的码长总和(树叶深度和)
int mapper[256];       //各种字符到节点编号的映射
char mapperb[256];     //各节点编号到各种字符的映射
int num;               //分配结点编号所用的计数器
vector<bool> code[256];	// 用整形表示的01碼表,但是编码首尾颠倒

//设置为:优先聚合权重最小且码长总和最小的两结点(间接排序)
struct cmp{
	bool operator()(const int& i, const int& j){
		if (freq[i] != freq[j])
			return freq[i] > freq[j];
		return length[i] > length[j];
	}
};

//显示码表(测试用)
void viewtab(){
	for(int i = 0;i < num;i++){
		char cha = mapperb[i];
		cout << cha << ": ";
		//因为是倒着存的,所以正着打印
		for(int j = code[i].size()-1;j>=0;j--)cout << code[i][j];
		cout << endl;
	}
}
void optimal(char* s){
	memset(freq,0,sizeof(freq));
	for (int i=0; s[i]; ++i){
		if(mapper[s[i]]==-1){mapper[s[i]] = num;mapperb[num++] = s[i];}
		freq[mapper[s[i]]]++;
	}
	
	priority_queue<int, vector<int>, cmp> pq;
	//初始设置,num个结点
	for (int i=0; i<num; ++i){
		cnt[i] = 1;
		length[i] = 0;
		pq.push(i);
	}
	//聚合num-1次建成Huffman树
	for (int i=num; i<num*2-1; ++i){ 
		int a = pq.top(); pq.pop();
		int b = pq.top(); pq.pop();
		freq[i] = freq[a] + freq[b];
		parent[a] = parent[b] = i;
		Left[i] = a; Right[i] = b;
		bit[a] = 0; bit[b] = 1;
		cnt[i] = cnt[a] + cnt[b];
		length[i] = length[a] + length[b] + cnt[i];
		pq.push(i);
	}

	// 從樹葉走訪至樹根，建立(倒)碼表。
	for (int i=0; i<num; ++i){
		code[i].clear();
		for (int j=i; j!=num*2-2; j=parent[j])
			code[i].push_back(bit[j]);
	}
	viewtab();
}

//简单地实现了压缩,s是原字符串
void compress(char* s){
	memset(mapper,-1,sizeof(mapper));
	memset(mapperb,-1,sizeof(mapperb));
	num = 0;
	optimal(s);//建表O(NlogN)
	for ( ; *s; s++)
		for (int i=code[mapper[*s]].size()-1; i>=0;i--)
			cout << code[mapper[*s]][i];
	cout << endl;
}
//简单地实现了解压,s是01字符串
void decompress(char* s){
	int p = num*2-2;
	for ( ; *s; s++){
		p = (*s == '0') ? Left[p] : Right[p];
		if (p < num){
			cout << (unsigned char)mapperb[p];
			p = num*2-2;
		}
	}
	cout << endl;
}

int main(){
	int n;
	printf("How many times do yo want to execute? ");
	scanf("%d",&n);
	while(n--){
		char str[257]; 
		int m;
		printf("input your original string.");
		scanf("%s",str);
		cout << " Compressing..." <<endl;
		compress(str);
		printf("How many times do you want to depress? ");
		scanf("%d",&m);
		while(m--){
			printf("input your 0-1 string.");
			scanf("%s",str);
			decompress(str);
		}
	}
	return 0;
}

