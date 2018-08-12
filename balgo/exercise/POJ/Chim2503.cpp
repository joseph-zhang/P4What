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
struct bet{
	char eng[12],foe[12];
	int next;
};
bet dict[100010];
int hashIndex[100010];

unsigned int BKDR_Hash(char *str){
	unsigned int seed = 131; 
	unsigned int hash = 0;
	int sz = strlen(str);
	for(int i = 0;i < sz;i++)hash = hash*seed+str[i];
	return (hash%100007);
}
unsigned int BJD_Hash(char *str){
	unsigned int hash = 5381;
	while(*str) hash += (hash << 5) + (*str++);
	return (hash%100007);
}
void find(char *s){
	if(s[0] == '\0') return;
	int hash = BKDR_Hash(s);
	int index = hashIndex[hash];
	bool ok = false;
	while(index){
		if(!strcmp(dict[index].foe,s)){ok = true;break;}
		index = dict[index].next;
	}
	if(ok)printf("%s\n",dict[index].eng);
	else cout << "eh" << endl; 
}
int main(){
	char buffer[23];
	memset(hashIndex,0,sizeof(hashIndex));
	int k = 1; 
	while(gets(buffer)){
		if(buffer[0] == '\0') break;
		sscanf(buffer,"%s %s",dict[k].eng,dict[k].foe);
		int hash = BKDR_Hash(dict[k].foe);
		dict[k].next = hashIndex[hash];
		hashIndex[hash] = k;
		k++;
	}	
	while(gets(buffer))
		find(buffer);
	return 0;
}
