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
*  通常的Hash表实现可利用STL的邻接表或是手动实现邻接表
*  在数据hash值范围不大时可用STL简易实现,当数据hash值范围比较大时,
*  还是推荐手动实现邻接表以提高效率。
*  设有不到maxn个的数据体(可能是字符串,数或其他可计算的结构体)
*  利用hash函数处理数据体得到hash值,设hash值不超过maxm。
*/
const int M = 100007;//大素数
const int maxn = 2001;
const int maxm = M+2;
//利用STL实现
vector<int> hashTable[maxm];
//手写邻接表
int head[maxm];
int hook[maxn];//若是自己的结构体,可以直接把hook(或称next)实现到里面
int reflex[maxn];

//BKDR-HASH(主要考虑)
unsigned int BKDR_Hash(char* str){
	unsigned int seed = 131; // 31,131,1313,13131...
	unsigned int hash = 0;
	while(*str)hash = (hash*seed+(*str++))%M;//每步取模避免溢出
	return (hash%M);//mod a big prime M;
}
//DJB-HASH
unsigned int DJB_Hash(char* str){
	unsigned int hash = 5381;
	while(*str)hash+=(hash<<5)+(*str++);
	return (hash%M);//mod a big prime
}
//JS-HASH
unsigned int JS_Hash(char* str){
	unsigned int hash = 1315423911;
	while(*str)hash ^= ((hash<<5)+(*str++)+(hash>>2));
	return (hash%M);//mod a big prime
}
//AP-HASH
unsigned int AP_Hash(char* str){
	unsigned int hash = 0;
	for(int i = 0;*str;i++){
		if(!(i&1))hash ^= ((hash << 7)^(*str++)^(hash >> 3));
		else hash ^= (~((hash << 11)^(*str++)^(hash >> 5)));
	}
	return (hash%M);//mod a big prime
}
/**
* 下面以BKDR-hash方法为例编写测试程序
* 使用手写的邻接表.
*/
char data[maxn][200];
bool query(char *s){
	int val = BKDR_Hash(s);
	int index = head[val];
	bool ok = false;
	while(index!=-1){
		if(!strcmp(data[reflex[index]],s))return true;//strcmp返回零说明两串相同
		index = hook[index];
	}
	return false;
}
int main(){
	int r = 1;//结点编号分配器
	memset(head,-1,sizeof(head));
	printf("How many strings? ");
	int n;cin >> n;
	printf("\nNow give me them.\n");
	for(int i = 0;i < n;i++){
		cin >> data[i];
		int val = BKDR_Hash(data[i]);
		printf("%s,hash value:%d\n",data[i],val);
		int index = head[val];
		while(index!=-1){
			if(!strcmp(data[i],data[reflex[index]]))break;
			index = hook[index];
		}
		if(index!=-1)continue;
		hook[r] = head[val];
		reflex[r] = i; //节点编号向字符串集data的位置映射
		head[val] = r++;
	}
	printf("Now implement query.How many times? ");
	cin >> n;char tmp[200];
	printf("Now give me words.\n");
	for(int i = 0;i < n;i++){
		cin >> tmp;
		if(query(tmp))printf("Find %s in table.\n",tmp);
		else printf("No %s\n",tmp);
	}
	return 0;
}
