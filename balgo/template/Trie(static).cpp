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
//以小写字母集为例，实现了插入和查询
const int maxn = 40002; //预估节点最大数
int Trie[maxn][26],r = 1;//一开始就把内存申请好,变量 r 用来分配节点
int num[maxn];//记录各单词重复次数
inline int transfer(char c){return c-'a';}

void insert(char* s){ 
	int j = 0,l = strlen(s);
	for(int i = 0;i < l;i++){
		int pos = transfer(s[i]);
		if(Trie[j][pos]) j = Trie[j][pos];
		else j = Trie[j][pos] = ++r;
	}
	num[j]++;
}
int query(char* s){
	int j = 0,l = strlen(s);
	for(int i = 0;i < l;i++){
		int pos = transfer(s[i]);
		if(Trie[j][pos]) j = Trie[j][pos];
		else return 0;
	}
	return num[j];
}

int main(){
	printf("give me some words,then I'll put them into Trie.\n");
	int n;char s[257];
	printf("How many words?");cin >> n;
	cout << endl;
	printf("Now give me them.\n");
	for(int i = 0;i < n;i++){
		cin >> s;cout << "Adding: " << s << endl;
		insert(s);		
		printf("\n");
	}
	printf("OK\n");
	printf("Now,how many times do you want to query:?");
	scanf("%d",&n);cout << endl;
	for(int i = 0;i < n;i++){
		printf("query:");
		cin >> s;
		cout << "There are " << query(s) << " "<< s << " in Trie."<<endl;
	}
	return 0;
}
