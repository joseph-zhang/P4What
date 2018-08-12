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
//假设仅对小写字母字符集进行
//只实现了查找字符串是否存在的功能，没有计数功能...
struct TrieNode{
	TrieNode(){
		for(int i = 0;i < 27;i++)l[i] = NULL;
		isEnd = false;
	}
	TrieNode* l[27];
	bool isEnd;
};
TrieNode* root;
// Adds a word into the Trie.
void addword(string& word){
	TrieNode* p = root;
	for(int i = 0;i < word.size();i++){
		int indx = word[i]-'a';
		if(!p->l[indx])p->l[indx] = new TrieNode();
		p = p->l[indx];
	}
	p->isEnd = true;
}
//寻找一个确定的单词是否在Trie中
bool query(string& word){
	TrieNode* p = root;
	for(int i = 0;i < word.size();i++){
		if(!p)return false;
		int indx = word[i]-'a';
		if(!p->l[indx])return false;
		p = p->l[indx];
	}
	return p->isEnd;
}

// Returns if the word is in the data structure. A word could
// contain the dot character '.' to represent any one letter.
bool dfs(string& word,int cur,TrieNode* p){
	if(!p)return false;
	if(word.size() == cur)return p->isEnd;
	int indx = word[cur]-'a';
	if(word[cur] == '.'){
		for(int i = 0;i < 27;i++)
			if(dfs(word,cur+1,p->l[i]))return true;
	}else{
		if(p->l[indx])return dfs(word,cur+1,p->l[indx]);
	}
	return false;
}
void release(TrieNode*& p){
	if(!p)return;
	for(int i = 0;i < 27;i++){
		if(p->l[i])release(p->l[i]);
	}
	delete(p);
	p = NULL;
}
int main(){
	root = new TrieNode();
	printf("give me some words,then I'll put them into Trie.");
	int n;string s;
	printf("How many words?");cin >> n;
	cout << endl;
	printf("Now give me them.\n");
	for(int i = 0;i < n;i++){
		cin >> s;cout <<"Adding: " << s << endl;
		addword(s);		
		printf("\n");
	}
	printf("OK\n");
	printf("Now,how many times do you want to query:?");
	scanf("%d",&n);cout << endl;
	for(int i = 0;i < n;i++){
		string words;
		printf("query:");
		cin >> words;
		if(query(words))cout << "Yes!" << endl;
		else cout << "NO." << endl;
	}
	printf("release Trie...");
	release(root);
	printf("OK\n");
	if(!root)cout << "Trie was correctly leased." << endl;
	return 0;
}

