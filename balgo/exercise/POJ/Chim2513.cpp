#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm> 
#include<cstdlib>
#include<stack>
#define INF 0x7fffffff
#define LL long long 
#define sys std::ios::sync_with_stdio(false);
using namespace std;
int Trie[540002][26],index[540002];
int dsj[540002],degree[540002];
int n = 0,r = 0;
int insert(char* s){
	int j = 0;
	for(;*s;s++){
		int p = *s-'a';
		if(Trie[j][p]) j = Trie[j][p];
		else j = Trie[j][p] = ++r;
	}
	if(!index[j]) index[j] = ++n;
	return index[j];
}
int Find(int x){
	return dsj[x] == x? x:(dsj[x] = Find(dsj[x]));
}
int main(){
	char color1[12];
	char color2[12];
	for(int i = 0;i < 540002;i++) dsj[i] = i;
	memset(degree,0,sizeof(degree));
	memset(Trie,0,sizeof(Trie));
	memset(index,0,sizeof(index));
	while(scanf("%s%s",color1,color2) != EOF){
		//if(color1[0] == '0' && color2[0] == '0')break;
		int ind1 = insert(color1);
		int ind2 = insert(color2);
		degree[ind1]++;degree[ind2]++;
		int p1 = Find(ind1);
		int p2 = Find(ind2);
		if(p1 != p2) dsj[p2] = p1;
	}
	int count = 0;
	bool flag = false;
	for(int i = 1;i <= n;i++){
		if(i == Find(i)) count++;
		if(count > 1){flag = true;break;}
	}
	count = 0;
	for(int i = 1;i <= n;i++)
		if(degree[i]%2) count++;
	if(count!=0 && count!=2) flag = true;
	if(flag) cout << "Impossible" << endl;
	else cout << "Possible" << endl;
	return 0;
}
